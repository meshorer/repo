#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

#define NUM_ARGS 20
#define PATH_LEN 30


int GoFork()
{
    char path[PATH_LEN] = {0};
    int i = 0;
    char *argv_ptr[NUM_ARGS] = {NULL};
    pid_t pid = 0;
    int status = 0;
    int result = 0;
    getc(stdin);
    while (1)
    {
        printf("SHELL: ");
        fgets(path, sizeof(path), stdin);
        path[strlen(path) - 1] = '\0';
        if (0 == strncmp("exit", path, 4))
        {
            break;
        }
        
        argv_ptr[0] = strtok(path, " ");
        for (i = 1; i <NUM_ARGS; ++i)
        {
            argv_ptr[i] = strtok(NULL, " ");
        }
        
        pid = fork();
        if (-1 == pid)
        {
            return pid;
        }
        if ( 0 == pid)
        {
            result = execvp(argv_ptr[0], argv_ptr);
            printf("error: %d\n", result);
            return result;
        }
        else
        {
            waitpid(pid,&status,0);
        }
    }

    return 0;
}

int GoSystem()
{

    char word[20] = {0};

    int result = 0;

    getc(stdin); /* to avoid the first enter*/
    while (1)
    {
        printf("SHELL: ");
        fgets(word, sizeof(word), stdin);
        if (0 == strncmp("exit", word, 4))
        {
            break;
        }
        result = system(word);
        if (0 != result)
        {
            printf("%d\n", result);
        }
    }
    return 0;
}

int main()
{
    int user_choice = 0;
    printf("select choice:\n 1 - fork\n 2 - system\n");
    scanf("%d", &user_choice);

    if (1 == user_choice)
    {
        return GoFork();
    }
    else if (2 == user_choice)
    {
        return GoSystem();
    }

    return 1;
}