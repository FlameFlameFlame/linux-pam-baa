#include <cstdlib>
#include <cstring>
#include <stdio.h>
#include <threads.h>

#include <security/pam_ext.h>
#include <security/pam_modules.h>

#include <curl/curl.h>

const char *BACKEND_URL_KEY = "backend_url=";
const char *SSL_VERIFY_IGNORE_KEY = "ssl_verify_ignore=";

struct MemoryStruct {
  char *memory;
  size_t size;
};

static size_t WriteMemoryCallback(void *ptr, size_t size, size_t nmemb, void *context) {
  size_t bytec = size * nmemb;
  struct MemoryStruct *mem = (struct MemoryStruct *)context;
  mem->memory = (char*)realloc(mem->memory, mem->size + bytec + 1);
  if(mem->memory == NULL) {
    printf("not enough memory (realloc returned NULL)\n");
    return 0;
  }
  memcpy(&(mem->memory[mem->size]), ptr, bytec);
  mem->size += bytec;
  mem->memory[mem->size] = 0;
  return nmemb;
}

int pam_sm_authenticate(pam_handle_t *pamh, int flags, int argc, const char **argv) {
    int retval;
    const char *user = NULL;
    const char *password = NULL;
    const char *backend_url = NULL;
    bool ssl_verify_ignore = false;

    retval = pam_get_user(pamh, &user, NULL);
    if (retval != PAM_SUCCESS) return retval;

    retval = pam_get_authtok(pamh, PAM_AUTHTOK, &password, NULL);
    if (retval != PAM_SUCCESS) return retval;

    int j;
    int backend_url_key_len = strlen(BACKEND_URL_KEY);
    int ssl_verify_ignore_key_len = strlen(SSL_VERIFY_IGNORE_KEY);
    for (int i = 0; i < argc; i++) {
        int arglen = strlen(argv[i]);

        if (arglen > backend_url_key_len) {
            for (j = 0; j < backend_url_key_len; j++)
                if (argv[i][j] != BACKEND_URL_KEY[j]) break;
            if (j == backend_url_key_len)
                backend_url = &argv[i][backend_url_key_len];
        }

        if (arglen > ssl_verify_ignore_key_len) {
            for (j = 0; j < ssl_verify_ignore_key_len; j++)
                if (argv[i][j] != SSL_VERIFY_IGNORE_KEY[j]) break;
            if (j == ssl_verify_ignore_key_len)
                if (argv[i][ssl_verify_ignore_key_len] == '1')
                    ssl_verify_ignore = true;
        }
    }

    if (!backend_url)
        return PAM_AUTHINFO_UNAVAIL;

    CURL *curl;
    CURLcode res;
    struct MemoryStruct chunk;
    chunk.memory = (char*)malloc(1);
    chunk.size = 0;
    chunk.memory[chunk.size] = 0;

    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    if(!curl)
        return PAM_CRED_INSUFFICIENT;

    curl_easy_setopt(curl, CURLOPT_URL, backend_url);
    curl_easy_setopt(curl, CURLOPT_HTTPAUTH, (long)CURLAUTH_BASIC);
    curl_easy_setopt(curl, CURLOPT_USERNAME, user);
    curl_easy_setopt(curl, CURLOPT_PASSWORD, password);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);

    if (ssl_verify_ignore)
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);

    res = curl_easy_perform(curl);
    if(res != CURLE_OK)
        return PAM_AUTH_ERR;

    long http_code = 0;
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
    if (http_code == 200) {
        return PAM_SUCCESS;
    }

    // curl_easy_cleanup(curl);
    // free(chunk.memory);
    // curl_global_cleanup();

    return PAM_PERM_DENIED;
}

int pam_sm_setcred(pam_handle_t *pamh, int flags, int argc, const char **argv) {
    return PAM_SUCCESS;
}

int pam_sm_acct_mgmt(pam_handle_t *pamh, int flags, int argc, const char **argv) {
    return PAM_SUCCESS;
}

int pam_sm_chauthtok(pam_handle_t *pamh, int flags, int argc, const char **argv) {
    return PAM_SUCCESS;
}

int pam_sm_open_session(pam_handle_t *pamh, int flags, int argc, const char **argv) {
    return PAM_SUCCESS;
}

int pam_sm_close_session(pam_handle_t *pamh, int flags, int argc, const char **argv) {
    return PAM_SUCCESS;
}

