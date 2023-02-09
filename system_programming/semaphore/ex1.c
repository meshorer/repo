#include <stdio.h>
#include <fcntl.h>    /* For O_* constants */
#include <sys/stat.h> /* For mode constants */
#include <semaphore.h>
#include <stdlib.h> /*atoi */
#include <string.h> /*strcmp*/


int CheckUndo(char *command)
{
    int count_space = 0;
    while(*command)
    {
        if (*command == ' ')
        {
            count_space++;
        }
        command++;
        if (count_space == 2)
        {
            break;
        }
    }
    if (strncmp(command, "undo", 4) == 0)
    {
        return 0;
    }
    return 1;
}

int Decrement(sem_t *sem, int number)
{
    int i = 0;
    for (i = 0; i < number; i++)
    {
        if (-1 == sem_wait(sem))
        {
            return -1;
        }
    }
    return 0;
}

int Increment(sem_t *sem, int number)
{
    int i = 0;
    for (i = 0; i < number; i++)
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
    int counter_undo = 0;
    if (2 > argc)
    {
        return -1;
    }
    sem = sem_open(name_sem, O_CREAT, 0666, 1);
    if (sem == SEM_FAILED)
    {
        perror("sem_open");
        return -1;
    }
    while (1)
    {
        printf("enter a command on the semaphore\n");
        if (NULL == fgets(command, sizeof(command) - 1, stdin))
        {
            perror("fgets");
            continue;
        }
        command[strlen(command) - 1] = '\0';
        

        if ((*command == 'D') | (*command == 'I'))
        {
            number = atoi(command + 2);
           
            if (*command == 'D')
            {
                if ( 0 == CheckUndo(command))
                {
                    counter_undo-=number;
                }
                result = Decrement(sem, number);
                if (-1 == result)
                {
                    perror("Decrement");
                }
            }
            else
            {  
                if ( 0 == CheckUndo(command))
                {
                    counter_undo+=number;
                }
                result = Increment(sem, number);
                if (-1 == result)
                {
                    perror("Decrement");
                }
            }
        }
        if (0 == strcmp(command, "V"))
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

       if (0 == strcmp(command, "X"))
        {
            if (0 > counter_undo)
            {
                result = Increment(sem, counter_undo);
                if (-1 == result)
                {
                    perror("Increment");
                }
            }
             if (0 < counter_undo)
            {
                result = Decrement(sem, counter_undo);
                if (-1 == result)
                {
                    perror("Decrement");
                }
            }
            if ( -1 == sem_close(sem))
            {
                perror("sem_close");
            }
            break;
        }
        if (0 == strcmp(command, "Q"))
        {
            
            if ( -1 == sem_close(sem))
            {
                perror("sem_close");
            }
            if ( -1 == sem_unlink(name_sem))
            {
                perror("Sem unlink");
            }
            
            break;
        }
    }

    return 0;
}