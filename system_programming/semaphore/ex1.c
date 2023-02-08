#include <stdio.h>
#include <fcntl.h>    /* For O_* constants */
#include <sys/stat.h> /* For mode constants */
#include <semaphore.h>
#include <stdlib.h> /*atoi */
#include <string.h> /*strcmp*/

int Decrement(sem_t *sem, int number)
{
    int i = 0;
    for (i == 0; i < number; i++)
    {
        if (-1 == sem_trywait(sem))
        {
            return -1;
        }
    }
    return 0;
}

int Increment(sem_t *sem, int number)
{
    int i = 0;
    for (i == 0; i < number; i++)
    {
        if (-1 == sem_post(sem))
        {
            return -1;
        }
    }
    return 0;
}

int ViewSem(sem_t *sem)
{
    int sem_value = -1;
    sem_getvalue(sem, &sem_value);

    return sem_value;
}

int main(int argc, char **argv)
{
    char *name_sem = argv[1];
    char command[30] = {0};
    sem_t *sem = NULL;
    int number = 0;
    int result = 0;
    sem = sem_open(name_sem, O_CREAT, O_EXCL, 1);
    if (sem == SEM_FAILED)
    {
        perror("sem_open");
        return -1;
    }
    while (1)
    {
        printf("enter a command on the semaphore\n");
        fgets(command, sizeof(command) - 1, stdin);

        if ((*command == 'D') | (*command == 'I'))
        {
            number = atoi(command + 2);

            if (*command == 'D')
            {
                result = Decrement(sem, number);
                if (-1 == result)
                {
                    perror("Decrement");
                }
            }
            else
            {
                result = Increment(sem, number);
                if (-1 == result)
                {
                    perror("Decrement");
                }
            }
        }
        if (0 == strncmp(command, "V", 1))
        {
            result = ViewSem(sem);
            if (-1 == result)
            {
                perror("ViewSem");
            }
            else
            {
                printf("Viewed semaphore %d\n", result);
            }
        }

       if (0 == strncmp(command, "X", 1))
        {
            sem_close(sem);
            sem_unlink(name_sem);
            break;
        }
    }

    return 0;
}