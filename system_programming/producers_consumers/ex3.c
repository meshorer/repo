#define _XOPEN_SOURCE 600 /* resolve implicit declaration of usleep */
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>    /* For O_* constants */
#include <sys/stat.h> /* For mode constants */
#include "slist.h"

/*  gd ex2.c /home/daniel/git/ds/src/slist.c -I /home/daniel/git/ds/include
 */

pthread_mutex_t lock = {0};
sem_t sem = {0};

struct my_struct
{
    s_list_t *my_list;
    int data[10];
    int counter;
};
 
void *Producer(void *arg)
{
    struct my_struct *my_struct = (struct my_struct *)arg;
    pthread_mutex_lock(&lock);
    SListAdd(my_struct->my_list, SListEnd(my_struct->my_list), &my_struct->data[my_struct->counter]);
    my_struct->counter++;
    pthread_mutex_unlock(&lock);
    if (-1 == sem_post(&sem))
    {
        return NULL;
    }
    return 0;
}

void *Consumer(void *arg)
{
    struct my_struct *my_struct = (struct my_struct *)arg;
    if (-1 == sem_wait(&sem))
    {
        return NULL;
    }
    pthread_mutex_lock(&lock);
    printf("data consumed: %d\n", *(int *)SListGet(my_struct->my_list, SListBegin(my_struct->my_list)));
    SListRemove(my_struct->my_list, SListBegin(my_struct->my_list));
    pthread_mutex_unlock(&lock);

    return 0;
}

int main()
{

    int i = 0;
    pthread_t id[20] = {0};
    s_list_t *my_list = NULL;
    struct my_struct args;
    my_list = SListCreate();
    args.my_list = my_list;

    for (i = 0; i < 10; i++)
    {
        args.data[i] = i;
    }
    args.counter = 0;

    if (-1 == sem_init(&sem, 0, 0))
    {
        perror("sem_init");
    }
    pthread_mutex_init(&lock, NULL);

    for (i = 0; i < 10; i++)
    {
        if (0 != pthread_create(&id[i], NULL, Producer, &args))
        {
            perror("pthread_create");
        }
    }

    for (; i < 20; i++)
    {
        if (0 != pthread_create(&id[i], NULL, Consumer, &args))
        {
            perror("pthread_create");
        }
    }

    for (i = 0; i < 20; i++)
    {
        if (0 != pthread_join(id[i], NULL))
        {
            perror("pthread_join");
        }
    }
    printf("finished threads\n");
    SListDestroy(my_list);
    pthread_mutex_destroy(&lock);
    sem_destroy(&sem);
    return 0;
}
