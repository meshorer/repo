#define _POSIX_SOURCE     /* resolve implicit declaration of kill */
#define _XOPEN_SOURCE 600 /* resolve implicit declaration of usleep, and for siginfo_t */
#include <unistd.h>       /* fork, execvp */
#include <stdio.h>
#include <signal.h>    /* for signal*/
#include <sys/types.h> /* pid_t */
#include <errno.h>

#define WORD_LENGTH 5
static volatile sig_atomic_t signalPid = 0;                             /* An int type that can be modified atomically */

void sig_handler_sec_process(int sig, siginfo_t *info,void *ptr)        /* signal handle function */
{
    signalPid = info->si_pid;
    if (sig == SIGUSR1)
    {
        write(STDOUT_FILENO, "ping\n", WORD_LENGTH);                    /* write is an async-signal-safe function */
    }
}

int child_process()
{
    while (1)
    {
        pause(); /* wait for signal */

        usleep(1000000);                                               /* sleep for 1 second */
        if (-1 == kill(signalPid, SIGUSR2))                             /* send SIGUSR2 signal to parent procesig_handparentss */
        {
            return errno;
        }
    }
    return 0;
}

int main()
{

    struct sigaction sa_sec_process;
    sa_sec_process.sa_sigaction = sig_handler_sec_process;             /* we use sa_sigaction because When the SA_SIGINFO flag is specified the signal handler address is passed via sa_sigaction field */
    sa_sec_process.sa_flags = SA_SIGINFO;
    printf("my pid is %d\n", getpid());
    if (sigaction(SIGUSR1, &sa_sec_process, NULL) == -1)
    {
        perror("sigaction");
    }

    return child_process(sa_sec_process.sa_flags);
    
}