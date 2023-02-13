#define _XOPEN_SOURCE 600 /* resolve implicit declaration of usleep */
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include "slist.h"

/*  gd ex2.c /home/daniel/git/ds/src/slist.c -I /home/daniel/git/ds/include
 */

pthread_mutex_t lock = {0};
s_list_t *my_list = NULL;
int data_to_send[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
int data_to_receive[10] = {0};
int count_consumer = 0;
int count_producer = 0;

void *Producer()
{
    pthread_mutex_lock(&lock);
    SListAdd(my_list, SListEnd(my_list), &data_to_send[count_producer]);
    count_producer++;
    pthread_mutex_unlock(&lock);
    return 0;
}

void *Consumer()
{
    while (SListSize(my_list) == 0){}
    
    pthread_mutex_lock(&lock);
    data_to_receive[count_consumer] = *(int *)SListGet(my_list, SListBegin(my_list));
    count_consumer++;
    SListRemove(my_list, SListBegin(my_list));
    pthread_mutex_unlock(&lock);
      
    
    return 0;
}

int main()
{

    int i = 0;
    pthread_t id[20] = {0};
    pthread_mutex_init(&lock, NULL);

    my_list = SListCreate();

    for (i = 0; i < 10; i++)
    {
        if (0 != pthread_create(&id[i], NULL, Producer, NULL))
        {
            perror("pthread_create");
        }
    }

    for (; i < 20; i++)
    {
        if (0 != pthread_create(&id[i], NULL, Consumer, NULL))
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
    printf("All threads joined\n");
    for (i = 0; i < 10; i++)
    {
        printf("%d\n", data_to_receive[i]);
    }
    SListDestroy(my_list);
    pthread_mutex_destroy(&lock);
    return 0;
}