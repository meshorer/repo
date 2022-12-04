#ifndef __STACK_H__ILRD__CR3_
#define __STACK_H__ILRD__CR3_

#include <stddef.h> /* size_t */
#include <assert.h> /* assert */
#include <stdlib.h> /* malloc */
#include <string.h> /* memcpy */
#include <stdio.h> /* memcpy */

typedef struct stack stack_t;

stack_t *StackCreate(const size_t capacity,const size_t elem_size);

int StackDestroy(stack_t *stack);

void StackPush(stack_t *stack ,const void *elem);

void *StackPeek(const stack_t *stack);

void StackPop(stack_t *stack);

int IsStackEmpty(const stack_t *stack);

size_t StackSize(const stack_t *stack);

size_t StackCapacity(const stack_t *stack);

#endif  /* __STACK_H__ILRD__CR3_ */
