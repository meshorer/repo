

/*  to follow the child process instead of parent  - use set follow-fork-mode child in gdb */
/*  to follow already running child process instead of parent 
 1. - find the process of the child
 2. - while in gdb use attch <pid> command to attach it 
 */

#define _POSIX_SOURCE           /* resolve implicit declaration of kill */
#define _XOPEN_SOURCE   600     /* resolve implicit declaration of usleep */
#include <unistd.h>             /* fork, execvp */
#include <stdio.h>				
#include <signal.h>				/* for signal*/
#include <sys/types.h>          /* pid_t */
#include <errno.h>				

#define WORD_LENGTH 5
#define CHILD_PROCESS "./ponga.out"

void sig_hand_parent(int sig)                               /* signal handle function for parent */
{
    if (sig == SIGUSR2)
    {
        write(STDOUT_FILENO, "pong\n", WORD_LENGTH);
    }
}

int parent_process(pid_t pid)
{
	while (1)
	{
		usleep(1000000);                                    /* sleep for 1 second */

		if (-1 == kill(pid, SIGUSR1))                       /* send SIGUSR1 signal to child process (pid recieved as argument) */
        {
            return errno;
        }                                 
        pause();                                            /* wait for signal */
	}
	return 0;
}

int main()
{
    
    pid_t child_pid = 0;
	struct sigaction sa_parent;
    char *argv_ptr[2] = {0};
    argv_ptr[0] = CHILD_PROCESS;
    argv_ptr[1] = NULL;
        
    sa_parent.sa_handler = sig_hand_parent;                 /* set up signal handler function for parent */

    if (sigaction(SIGUSR2, &sa_parent, NULL) == -1)
	{
		perror("sigaction");
	}
	
	child_pid = fork();                                     /* create child process */

    if (-1 == child_pid)                                    /* check that fork worked */
    {
        perror("fork");
    }

	if (0 == child_pid)
	{
        if (-1 == execvp(argv_ptr[0],argv_ptr))
        {
            printf("%s: command not found\n", argv_ptr[0]);
            kill(getppid(),SIGTERM);                           /* if execvp fails - kill the parent   */
        }
	}
	else
	{
		return parent_process(child_pid);                          /* run parent_process()  */
	}
	
	return 0;
}