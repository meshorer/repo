
#define _POSIX_SOURCE           /* resolve implicit declaration of kill */
#define _XOPEN_SOURCE   600     /* resolve implicit declaration of usleep */
#include <unistd.h>             /* fork, execvp */
#include <stdio.h>				
#include <signal.h>				/* for signal*/
#include <sys/types.h>          /* pid_t */
#include <errno.h>				

#define WORD_LENGTH 5

void sig_handler_first_process(int sig)                               /* signal handle function for parent */
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
		usleep(1000000);                                               /* sleep for 1 second */

		if (-1 == kill(pid, SIGUSR1))                                   /* send SIGUSR1 signal to child process (pid recieved as argument) */
        {
            return errno;
        }                                 
        pause();                                                        /* wait for signal */
	}
	return 0;
}

int main()
{
    
    pid_t other_pid = 0;
	struct sigaction sa_first_process;

    sa_first_process.sa_handler = sig_handler_first_process;                 /* set up signal handler function for parent */
    
    if (sigaction(SIGUSR2, &sa_first_process, NULL) == -1)
	{
		perror("sigaction");
	}
	
	printf("enter pid to send signal\n");
    scanf("%d", &other_pid);
	return parent_process(other_pid);                                       /* run parent_process()  */
}