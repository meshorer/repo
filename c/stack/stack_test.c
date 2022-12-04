#include "stack.h"



int main()
{
	
	int i = 0;
	int x = 8;
	void *ptr_x = &x;

	stack_t *stack1 = StackCreate(10,4);

	printf("peak/base is : %p\n", StackPeek(stack1));
	if ( 0 != IsStackEmpty(stack1))
	{
		StackPop(stack1);
		printf("pop succes\n");
	}
	else
	{
		printf("pop failed\n");
	}	
	for (i = 0; i < 10; i++)
	{
		StackPush(stack1,(char *)ptr_x+i);
	}
	
	printf("stack amount: %lu\n", StackSize(stack1));
	printf("peak is : %p\n", StackPeek(stack1));
	

	if ( 0 != IsStackEmpty(stack1))
	{
		StackPop(stack1);
		printf("pop succes\n");
	}
	else
	{
		printf("pop failed\n");
	}		
	printf("stack amount: %ld\n", StackSize(stack1));
	printf("after pop peak is : %p\n", StackPeek(stack1));
	

	if ( 0 == StackDestroy(stack1))
	{
		printf("destroy success\n");
	}
	
	
	
return 0;
}


	



