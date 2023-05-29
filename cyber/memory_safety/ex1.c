#include <string.h>
#include <stdio.h>

int main() {
    char password[20] = "this is my password";
    char buff[20] = "";
    gets(buff);

    if (0 == strncmp(buff, password, 20)) {
        printf("You have successfully entered the password.\n");
    }
    else {
        printf("Sorry, your password is incorrect.\n");
    }

    return 0;
}