#include <pthread.h> /* for pthread_create and mutex*/
#include <stdio.h>
#include <semaphore.h>
#include <errno.h>

#define NUM_THREDS 30000
#define NUM_ELEMENTS 100

/*  gd ex4.c /home/daniel/git/ds/src/slist.c -I /home/daniel/git/ds/include
 */

pthread_mutex_t lock_consumer = {0};
pthread_mutex_t lock_producer = {0};
sem_t sem_read = {0};
sem_t sem_write = {0};

struct my_struct
{
    int data[NUM_ELEMENTS];
    int index_write;
    int index_read;
};

void Enqueue(int *index)
{
    if (*index == NUM_ELEMENTS -1)
    {
        *index = 0;
    }
    else
    {
        (*index)++;
    }
}

void Dequeue(int *index)
{
    if (*index == NUM_ELEMENTS -1)
    {
        *index = 0;
    }
    else
    {
        (*index)++;
    }
}

void *Producer(void *arg)
{
    struct my_struct *my_struct = (struct my_struct *)arg;

    if (-1 == sem_wait(&sem_write))
    {
        return NULL;
    }

    if (0 != pthread_mutex_lock(&lock_producer))
    {
        perror(" produxer pthread_mutex_lock");
    }

    my_struct->data[my_struct->index_write] = 1;
    printf("index write: %d\n", my_struct->index_write);

    Enqueue(&my_struct->index_write);

    if (-1 == sem_post(&sem_read))
    {
        return NULL;
    }

    if (0 != pthread_mutex_unlock(&lock_producer))
    {
        perror("pthread_mutex_unlock");
    }

    return 0;
}

void *Consumer(void *arg)
{
    struct my_struct *my_struct = (struct my_struct *)arg;

    if (-1 == sem_wait(&sem_read))
    {
        return NULL;
    }

    if (0 != pthread_mutex_lock(&lock_consumer))
    {
        perror("pthread_mutex_lock");
    }

    printf("data consumed: %d i:%d\n", my_struct->data[my_struct->index_read],my_struct->index_read);

    Dequeue(&my_struct->index_read);

    if (-1 == sem_post(&sem_write))
    {
        return NULL;
    }

    if (0 != pthread_mutex_unlock(&lock_consumer))
    {
        perror("pthread_mutex_unlock");
    }

    return 0;
}

int main()
{

    int i = 0;
    pthread_t id[NUM_THREDS] = {0};
    struct my_struct args;
    args.index_read = 0;
    args.index_write = 0;
    for (i = 0; i < NUM_ELEMENTS; i++)
    {
        args.data[i] = 0;
    }

    if (-1 == sem_init(&sem_read, 0, 0))
    {
        perror("sem_init");
    }
    if (-1 == sem_init(&sem_write, 0, NUM_ELEMENTS))
    {
        perror("sem_init");
    }

    if (0 != pthread_mutex_init(&lock_consumer, NULL))
    {
        perror("pthread_mutex_init");
    }

    if (0 != pthread_mutex_init(&lock_producer, NULL))
    {
        perror("pthread_mutex_init");
    }

    for (i = 0; i < NUM_THREDS / 2; i++)
    {
        if (0 != pthread_create(&id[i], NULL, Producer, &args))
        {
            perror("pthread_create");
        }
    }

    for (i = NUM_THREDS / 2; i < NUM_THREDS; i++)
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
    if (0 != pthread_mutex_destroy(&lock_consumer))
    {
        perror("pthread_mutex_destroy");
        return -1;
    }

    if (0 != pthread_mutex_destroy(&lock_producer))
    {
        perror("pthread_mutex_destroy");
        return -1;
    }

    if (0 != sem_destroy(&sem_read))
    {
        perror("sem_read destroy");
        return errno;
    }
    if (0 != sem_destroy(&sem_write))
    {
        perror("sem_write destroy");
        return errno;
    }
    return 0;
}
