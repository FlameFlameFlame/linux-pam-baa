#include <stdio.h>

#include <security/pam_ext.h>
#include <security/pam_modules.h>

int pam_sm_authenticate(pam_handle_t *pamh, int flags, int argc, const char **argv) {
    int retval;
    const char *user=NULL;
    const char *password=NULL;

    retval = pam_get_user(pamh, &user, NULL);
    if (retval != PAM_SUCCESS) {
        return retval;
    }

    /*if (user[0] == 'a') {
        return PAM_SUCCESS;
    } else {
        return PAM_PERM_DENIED;
    }*/

    retval = pam_get_authtok(pamh, PAM_AUTHTOK, &password, NULL);
    if (retval != PAM_SUCCESS) {
        return retval;
    }

    if (password[0] == 'a') {
        return PAM_SUCCESS;
    }

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
