#include <stdlib.h>
#include <stdio.h>
#include "queue.h"


/* implemented to work for queue of ints. to convert it to void*. please see example in stack.c (similar)*/

struct queue {
    int *data;
    size_t capacity;
    size_t size;
    int top_element_index;
    int last_element_index;
};

queue_t *QueueCreate(size_t capacity)
{
    queue_t *my_queue = malloc(sizeof(queue_t));

    if (NULL == my_queue)
    {
        return NULL;
    }

    my_queue->data = malloc(capacity * sizeof(int));

    if (NULL == my_queue->data)
    {
        free(my_queue);
        return NULL;
    }

    my_queue->capacity = capacity;
    my_queue->size = 0;
    my_queue->top_element_index = 0;
    my_queue->last_element_index = 0;

    return my_queue;
}

int QueueIsEmpty(queue_t *q)
{
    return q->size != 0;
}

int QueueIsFull(queue_t *q)
{
    return q->size != q->capacity;
}

int Enqueue(queue_t *q, int value) 
{
    if (QueueIsFull(q) == 0)
    {
        return -1;
    }
 
    q->data[q->last_element_index] = value;

    if (q->last_element_index == (int)q->capacity)
    {
        q->last_element_index = 0;
    }
    else
    {
        q->last_element_index++;
    }

    q->size++;

    return 0;
}

int Dequeue(queue_t *q)
{
    if (QueueIsEmpty(q)== 0)
    {
        return -1;
    }

    q->top_element_index++;

    q->size--;

    return 0;
}

int QueuePeek(queue_t *q)
{
    return q->data[q->top_element_index];
}

size_t QueueSize(queue_t *q)
{
    return q->size;
}

size_t QueueCapacity(queue_t *q)
{
    return q->capacity;
}

void QueueDestroy(queue_t *q)
{
    free(q->data);
    free(q);
}
