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

int child_process()
{
	while(TRUE)
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


int main()
{
	
    struct sigaction sa_child;
    
	sa_child.sa_handler = sig_hand_child;                   /* set up signal handler function for child */

	if (sigaction(SIGUSR1, &sa_child, NULL) == -1)
	{
		perror("sigaction");
	}
	
    child_process();
	return 0;
}