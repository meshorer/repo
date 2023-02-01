#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>


int main()
{
    /*char **argv = NULL;
    char *path = "ls -l -a -g";
    char *command = NULL;
    int i = 0;
    argv = (char **)malloc(3);
    argv[0] = (char *)malloc(10);
    argv[1] = (char *)malloc(10);
    argv[2] = (char *)malloc(10);
    command = strtok(path, " ");
    for (i = 0; i < 3; i++)
    {
        argv[i] = strtok(NULL, " ");
        printf("%s\n", argv[i]);
    }
    */
    char path[] = "ls -l -a -g";
    char *command = NULL;
    int i = 0;
    char **argv_ptr = (char **)malloc(4 * sizeof(char *));
    for (i = 0; i < 4; i++)
    {
        argv_ptr[i] = (char *)malloc(10);
    }
    command = strtok(path, " ");
    printf("%s\n", command);
    argv_ptr[0] = command;
    for (i = 1; (argv_ptr[i] = strtok(NULL, " ")) != NULL; i++);
    for (i = 1; i < 4; i++)
    {
        printf("%s\n", argv_ptr[i]);
    }
    return 0;
}