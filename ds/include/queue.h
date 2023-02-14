#ifndef __QUEUE_H__ILRD__CR3_
#define __QUEUE_H__ILRD__CR3_

#include <stddef.h>


typedef struct queue queue_t;

queue_t *QueueCreate(size_t size); /* initialize queue */
int QueueIsEmpty(queue_t *q); /* check if queue is empty */
int QueueIsFull(queue_t *q); /* check if queue is full */
int Enqueue(queue_t *q, int value); /* add element to back of queue, 0 for success, not 0 for failure  */
int Dequeue(queue_t *q); /* remove and return element at front of queue */
int QueuePeek(queue_t *q); /* return element at front of queue without removing it */
size_t QueueSize(queue_t *q); /* return number of elements now in queue */
size_t QueueCapacity(queue_t *q); /* return number of total possible elements in queue */
void QueueDestroy(queue_t *q); /* destroy queue */
void print_queue(queue_t *q); /* print elements in queue */


#endif /* __QUEUE_H__ILRD__CR3_ */
