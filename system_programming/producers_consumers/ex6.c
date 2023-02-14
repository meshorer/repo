#include <pthread.h> /* for pthread_create and mutex*/
#include <stdio.h>
#include <semaphore.h>
#include <errno.h>

#define NUM_THREDS 5

pthread_mutex_t lock = {0};
sem_t sem_read = {0};
int condition_variable = 0;
int message = 0;

void *Producer()
{
    int i = 0;

    message = 1;

    for (; i < NUM_THREDS - 1; i++)
    {
        if (-1 == sem_post(&sem_read))
        {
            return NULL;
        }
    }
    condition_variable = 1;

    while (condition_variable == 0)
    {
    }

    return 0;
}

void *Consumer()
{
    int sem_value = 0;
    if (-1 == sem_wait(&sem_read))
    {
        return NULL;
    }

    if (0 != pthread_mutex_lock(&lock))
    {
        perror(" produxer pthread_mutex_lock");
    }
    printf("message : %d\n", message);

    if (0 != pthread_mutex_unlock(&lock))
    {
        perror("pthread_mutex_unlock");
    }

    if (sem_getvalue(&sem_read,&sem_value) != 0)
    {
        perror("sem_getvalue");
        return NULL;
    } 

    if ( 0 == sem_value)
    {
        condition_variable = 0;
    }

    return 0;
}

int main()
{

    int i = 0;
    pthread_t id[NUM_THREDS] = {0};

    if (-1 == sem_init(&sem_read, 0, NUM_THREDS - 1))
    {
        perror("sem_init");
    }

    if (0 != pthread_mutex_init(&lock, NULL))
    {
        perror("pthread_mutex_init");
    }

    if (0 != pthread_create(&id[0], NULL, Producer, NULL))
    {
        perror("pthread_create");
    }

    for (i = 1; i < NUM_THREDS; i++)
    {
        if (0 != pthread_create(&id[i], NULL, Consumer, NULL))
        {
            perror("pthread_create");
        }
    }

    for (i = 0; i < NUM_THREDS; i++)
    {
        if (0 != pthread_join(id[i], NULL))
        {
            perror("pthread_join");
        }
    }

    printf("finished threads\n");

    if (0 != pthread_mutex_destroy(&lock))
    {
        perror("pthread_mutex_destroy");
        return -1;
    }

    if (0 != sem_destroy(&sem_read))
    {
        perror("sem_read destroy");
        return errno;
    }

    return 0;
}
