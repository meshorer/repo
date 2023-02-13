#define _XOPEN_SOURCE 600 /* resolve implicit declaration of usleep */
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdatomic.h>

#define PSHARED_STATE PTHREAD_PROCESS_PRIVATE
int global_data[10] = {0};
pthread_spinlock_t lock = 0;
volatile atomic_int i = 0;
int key = 0;

void *Producer()
{

    while (1)
    {
        if (i >= 10)
        {
            break;
        }
        pthread_spin_lock(&lock);
        global_data[i] = i * 10;
        pthread_spin_unlock(&lock);
        i++;
    }
    return 0;
}

void *Consumer()
{

    while (1)
    {

        if (i >= 10)
        {
            break;
        }
        pthread_spin_lock(&lock);
        if (global_data[i] != global_data[i + 1])
        {
            printf("message received\n");
        }
        pthread_spin_unlock(&lock);
    }
    return 0;
}

int main()
{
    pthread_t id1 = 0;
    pthread_t id2 = 0;

    pthread_spin_init(&lock, PSHARED_STATE);

    if (0 != pthread_create(&id1, NULL, Producer, NULL))
    {
        perror("pthread_create");
    }
    if (0 != pthread_create(&id2, NULL, Consumer, NULL))
    {
        perror("pthread_create");
    }

    if (0 != pthread_join(id1, NULL))
    {
        perror("pthread_join");
        return 1;
    }

    if (0 != pthread_join(id2, NULL))
    {
        perror("pthread_join");
        return 1;
    }

    if (pthread_spin_destroy(&lock))
    {
        perror("pthread_spin_destroy");
        return 1;
    }

    for (i = 0; i < 10; i++)
    {
        printf("global_data[%d] = %d\n", i, global_data[i]);
    }
    return 0;
}