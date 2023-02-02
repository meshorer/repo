#include <sys/types.h> /* pid_t */
#include <stdlib.h>    /* system */
#include <unistd.h>    /* fork , execvp */
#include <string.h>    /* strcmp */
#include <stdio.h>
#include <sys/wait.h> /* waitpid */
#include <errno.h>    /* errno */
#include <signal.h>

#define NUM_ARGS 20
#define command_LEN 30

void ExtractCommand(char *command, char **argv_ptr)
{
    int i = 0;
    argv_ptr[0] = strtok(command, " "); /*extract the command from the string*/

    while (NULL != argv_ptr[i]) /* stop when reaching a null terminator*/
    {
        ++i;
        argv_ptr[i] = strtok(NULL, " ");
    }
}

void CheckChildStatus(int child_status)
{

    if (!WIFEXITED(child_status)) /* WIFEXITED to check if the child process exited normally  */
    {
        printf("WIFEXITED - exit abnormally\n");
    }
    else if (WIFSIGNALED(child_status))
    {
        printf("child was terminated with signal: %d\n", WTERMSIG(child_status));
    }
    else if (WIFSTOPPED(child_status))
    {
        printf("child was stopped with signal: %d\n", WSTOPSIG(child_status));
    }
}

int GoFork()
{
    char command[command_LEN] = {0};
    char *argv_ptr[NUM_ARGS] = {0};
    pid_t pid = 0;
    int child_status = 0;
    int result = 0;
    getc(stdin);
    while (1)
    {
        printf("SHELL: ");
        fgets(command, sizeof(command), stdin);
        command[strlen(command) - 1] = '\0'; /*to avoid the \n in the end*/
        if (0 == strncmp("exit", command, 4))
        {
            break;
        }

        ExtractCommand(command, argv_ptr);

        pid = fork();
        if (-1 == pid)
        {
            perror("fork");
            return errno;
        }
        if (0 == pid) /* 0 means I am the child now */
        {
            result = execvp(argv_ptr[0], argv_ptr);
            printf("%s: command not found\n", argv_ptr[0]);
            return result;
        }
        else if (0 < pid)
            {
                if (-1 == wait(&child_status)) /* Wait for the child process to complete. */
                {
                    perror("wait");
                    return errno;
                }
                CheckChildStatus(child_status);
            }
    }
    
    return 0;
}

int GoSystem()
{

    char word[command_LEN] = {0};

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