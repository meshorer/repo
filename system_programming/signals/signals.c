#define _POSIX_SOURCE           /* resolve inplicit dec of kill */
#define _XOPEN_SOURCE   600     /* esolve inplicit dec of usleep*/
#include <unistd.h>             /* fork , execvp */
#include <stdio.h>
#include <signal.h>
#include <sys/types.h>          /* pid_t */

/*
    using fork:
    Send signal SIGUSR1 from parent to child.
    When the child receives SIGUSR1 it should return signal SIGUSR2 to its parent, and vice versa.
*/

volatile sig_atomic_t childglobal = 1;
volatile sig_atomic_t parentglobal = 1;

void handle_child(int sig)
{
    if (sig == SIGUSR1)
    {
        parentglobal--;
        write(STDOUT_FILENO,"ping\n",5);
    }
}

void handle_parent(int sig)
{
    if (sig == SIGUSR2)
    {
        childglobal--;
        write(STDOUT_FILENO,"pong\n",5);
    }
}

int main()
{

    pid_t pid_child = 0;
   
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
        while (childglobal)
        {
             raise(SIGUSR2);
             pause();
              
        }
       
    }
    else                   
    {
        while (parentglobal)
        {   
            kill(pid_child, SIGUSR1);
            pause();     
        }
        
    }

    return 0;
}

