#include <stdio.h>

#include "queue.h"

#define MAX_QUEUE_SIZE 10


int main()
{
    queue_t *my_queue = QueueCreate(MAX_QUEUE_SIZE);
    printf("queue size: %lu\n",QueueSize(my_queue));
    printf("is queue empty: %d\n",QueueIsEmpty(my_queue));
    Enqueue(my_queue, 0);
    Enqueue(my_queue, 3);
    printf("queue size: %lu\n",QueueSize(my_queue));
    printf("is queue empty: %d\n",QueueIsEmpty(my_queue));
    printf("peek: %d\n",QueuePeek(my_queue));
    Dequeue(my_queue);
    printf("peek: %d\n",QueuePeek(my_queue));
    printf("queue size: %lu\n",QueueSize(my_queue));
   
    QueueDestroy(my_queue);
    return 0;
}