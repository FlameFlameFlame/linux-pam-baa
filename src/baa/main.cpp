#include <cstring>
#include <stdio.h>

#include <security/pam_ext.h>
#include <security/pam_modules.h>

const char *BACKEND_URL_KEY = "backend_url=";
const char *SSL_VERIFY_IGNORE_KEY = "ssl_verify_ignore=";

int pam_sm_authenticate(pam_handle_t *pamh, int flags, int argc, const char **argv) {
    int retval;
    const char *user=NULL;
    const char *password=NULL;
    const char *backend_url=NULL;
    const char *ssl_verify_ignore=NULL;

    retval = pam_get_user(pamh, &user, NULL);
    if (retval != PAM_SUCCESS) return retval;

    retval = pam_get_authtok(pamh, PAM_AUTHTOK, &password, NULL);
    if (retval != PAM_SUCCESS) return retval;

    int j;
    int backend_url_key_len = strlen(BACKEND_URL_KEY);
    int ssl_verify_ignore_key_len = strlen(SSL_VERIFY_IGNORE_KEY);
    for (int i = 0; i < argc; i++) {
        int arglen = strlen(argv[i]);

        if ((arglen <= backend_url_key_len) &&
            (arglen <= ssl_verify_ignore_key_len)) continue;

        for (j = 0; j < backend_url_key_len; j++)
            if (argv[i][j] != BACKEND_URL_KEY[j]) break;
        if (j == backend_url_key_len)
            backend_url = &argv[i][backend_url_key_len];

        for (j = 0; j < ssl_verify_ignore_key_len; j++)
            if (argv[i][j] != SSL_VERIFY_IGNORE_KEY[j]) break;
        if (j == ssl_verify_ignore_key_len)
            ssl_verify_ignore = &argv[i][ssl_verify_ignore_key_len];
    }

    if (!backend_url)
        return PAM_AUTHINFO_UNAVAIL;

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
