#include <unistd.h> /* fork , execvp */
#include <stdio.h>
#include <signal.h>
#include <sys/types.h> /* pid_t */

/*
    using fork:
    Send signal SIGUSR1 from parent to child.
    When the child receives SIGUSR1 it should return signal SIGUSR2 to its parent, and vice versa.
*/

int childglobal = 0;
int parentglobal = 0;

void handle_child(int sig)
{
    if (sig == SIGUSR1)
    {
        childglobal++;
        printf("Caught signal in child:  %d\n", sig);
    }
}

void handle_parent(int sig)
{
    if (sig == SIGUSR2)
    {
        parentglobal++;
        printf("Caught signal in parent: %d\n", sig);
    }
}

int main()
{

    pid_t pid_child = 0;
    int child_status;

    signal(SIGUSR1, handle_child);
    signal(SIGUSR2, handle_parent);

    pid_child = fork();

    if (pid_child < 0)
    {
        perror("fork error");
        return pid_child;
    }
    if (0 == pid_child)    
    {
        raise(SIGUSR2);
        raise(SIGUSR2);
    }
    else                   
    {
        kill(pid_child, SIGUSR1);
        kill(pid_child, SIGUSR1);       
    }

    return 0;
}

