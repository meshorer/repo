

#include <string.h>
#include <stdio.h>

void permute(char *str) {
    int n = strlen(str);
    int i;
    if (n == 1) {
        printf("%s\n", str);
    } else {
        for (i = 0; i < n; i++) {
            char tmp = str[0];
            str[0] = str[i];
            str[i] = tmp;

            permute(str + 1);

            tmp = str[0];
            str[0] = str[i];
            str[i] = tmp;
        }
    }
}




int main()
{

	char str[] = "ABC";
	permute(str);



	return 0;
}
