#include <security/pam_appl.h>
#include <security/pam_misc.h>
#include <pwd.h>
#include <stdio.h>
#include <string.h>


/*
	1. our "coppy common" file contains this sentences:
	auth required pam_listfile.so onerr=fail item=group sense=allow file=/etc/pam.d/check_user_groups
	auth       required     pam_unix.so
	
	2. "check_user_groups" needs to have permissions "600" . this file contains a list of the groups allowed to enter
	3. compile this file and link with lpam and lpam_misc
	4. run this program with sudo
*/
#define MY_CONFIG "copy_common"

static struct pam_conv conv = { misc_conv, NULL };

int main()
{
    char user_name[100], password[100];
    pam_handle_t *pamh;
    int result;

    printf("Enter user name: ");
    scanf("%s", user_name);
    printf("Enter password: ");
    scanf("%s", password);

    result = pam_start(MY_CONFIG, user_name, &conv, &pamh);

    if (result == PAM_SUCCESS)
    {
        result = pam_authenticate(pamh, 0);
    }

    if (result == PAM_SUCCESS)
    {
        printf("User authenticated\n");
    } 
    else
    {
        printf("User not authenticated\n");
    }

    pam_end(pamh, result);
    return 0;
}
