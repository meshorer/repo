#define _POSIX_SOURCE           /* resolve implicit declaration of kill */
#define _XOPEN_SOURCE   600     /* resolve implicit declaration of usleep */
#include <unistd.h>             /* fork, execvp */
#include <stdio.h>				
#include <signal.h>				/* for signal*/
#include <sys/types.h>          /* pid_t */
#include <errno.h>				

#define WORD_LENGTH 5

void sig_hand_child(int sig)                                /* signal handle function for child */
{
    if (sig == SIGUSR1)
    {
        write(STDOUT_FILENO, "ping\n", WORD_LENGTH);        /* write is an async-signal-safe function */
    }
}

void sig_hand_parent(int sig)                               /* signal handle function for parent */
{
    if (sig == SIGUSR2)
    {
        write(STDOUT_FILENO, "pong\n", WORD_LENGTH);
    }
}


int child_process()
{
	while(1)
	{
        pause();                                            /* wait for signal */
		
		usleep(1000000);                                    /* sleep for 1 second */

		if (-1 == kill(getppid(), SIGUSR2))                 /* send SIGUSR2 signal to parent procesig_handparentss */
        {
            return errno;
        }                         
	}
	return 0;
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
    struct sigaction sa_child;
    
    
	sa_child.sa_handler = sig_hand_child;                   /* set up signal handler function for child */
    sa_parent.sa_handler = sig_hand_parent;                 /* set up signal handler function for parent */

	if (sigaction(SIGUSR1, &sa_child, NULL) == -1)
	{
		perror("sigaction");
	}

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
		return child_process();                                    /* run child_process()  */
	}
	else
	{
		return parent_process(child_pid);                          /* run parent_process()  */
	}
	
	return 0;
}