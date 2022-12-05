#include "stack.h"

/*reviewed by Or*/

struct stack{

	char *base;
	char *top;
	size_t capacity;
	size_t elem_size;
};

stack_t *StackCreate(const size_t capacity,const size_t elem_size)
{
	stack_t *ptr = malloc(sizeof(stack_t));
	assert (NULL != ptr);
	ptr->base = malloc(capacity * elem_size);
	assert (NULL != ptr->base);
	ptr->top = ptr->base;
	ptr->capacity = capacity;
	ptr->elem_size = elem_size;
	
	return ptr;
}


int StackDestroy(stack_t *stack)
{
	free(stack->base);
	free(stack);
	return 0;
}


void StackPush(stack_t *stack ,const void *elem)
{		
	memcpy(stack->top,elem,stack->elem_size);
	stack->top =stack->top + stack->elem_size;
	
}

void StackPop(stack_t *stack)
{
	stack->top -= stack->elem_size;	
}

void *StackPeek(const stack_t *stack)
{
	return stack->top - stack->elem_size;
}

size_t StackSize(const stack_t *stack)
{
	return (stack->top -stack->base)/stack->elem_size;
}

int IsStackEmpty(const stack_t *stack)
{
	
	return stack->top - stack->base;
}

size_t StackCapacity(const stack_t *stack)
{
	return stack->capacity;
}
