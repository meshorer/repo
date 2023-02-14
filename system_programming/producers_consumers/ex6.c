#include <pthread.h> /* for pthread_create and mutex*/
#include <stdio.h>
#include <semaphore.h>
#include <errno.h>

#define NUM_THREDS 5

pthread_mutex_t lock = {0};
sem_t sem_read = {0};
pthread_cond_t condition_variable = {0};

struct my_struct
{
    int counter_consume;
    int message;
};

void *Producer(void *arg)
{
    int i = 0;

    struct my_struct *my_struct = (struct my_struct *)arg;

    if (0 != pthread_mutex_lock(&lock))
    {
        perror(" produxer pthread_mutex_lock");
    }
    my_struct->message = 10;
    for (; i < NUM_THREDS - 1; i++)
    {
        if (-1 == sem_post(&sem_read))
        {
            return NULL;
        }
    }

    if (0 != pthread_mutex_unlock(&lock))
    {
        perror("pthread_mutex_unlock");
    }

    pthread_cond_wait(&condition_variable, &lock);

    printf("producer out\n");

    return 0;
}

void *Consumer(void *arg)
{

    struct my_struct *my_struct = (struct my_struct *)arg;

    if (-1 == sem_wait(&sem_read))
    {
        return NULL;
    }

    if (0 != pthread_mutex_lock(&lock))
    {
        perror(" produxer pthread_mutex_lock");
    }

    printf("message : %d\n", my_struct->message);

    my_struct->counter_consume--;

    if (0 != pthread_mutex_unlock(&lock))
    {
        perror("pthread_mutex_unlock");
    }

    if (0 == my_struct->counter_consume)
    {
        pthread_cond_signal(&condition_variable);
    }

    return 0;
}

int main()
{
    struct my_struct args;
    int i = 0;
    pthread_t id[NUM_THREDS] = {0};

    args.message = 0;
    args.counter_consume = NUM_THREDS - 1;

    if (-1 == sem_init(&sem_read, 0, NUM_THREDS - 1))
    {
        perror("sem_init");
    }

    if (0 != pthread_mutex_init(&lock, NULL))
    {
        perror("pthread_mutex_init");
    }

    pthread_cond_init(&condition_variable, NULL);

    if (0 != pthread_create(&id[0], NULL, Producer, &args))
    {
        perror("pthread_create");
    }

    for (i = 1; i < NUM_THREDS; i++)
    {
        if (0 != pthread_create(&id[i], NULL, Consumer, &args))
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
