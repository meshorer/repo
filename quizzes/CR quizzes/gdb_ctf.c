#include <stdio.h> /*   printf  */

char *secret(char *param);

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        puts("Please insert your ID");
        return 1;
    }
    size_t a[3] = {0};

    *(size_t *)((char *)a + 1) = *(size_t *)secret(argv[1]);
    *((size_t *)((char *)a) + 1) = 2314885686279031104;
    *(void **)a = NULL;
    *((void **)a + 1) = NULL;
    *((void **)a + 2) = NULL;

    return 0;
}
