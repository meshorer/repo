#include "recursion.h"
#include "stack.h"
#include "stack.c"
/* the function recieves number and create fibonacci sequence untill that index number - iterativelty */
int Fibonacci(int element_index)
{
	int sum = 1;
	int back_num = 0;
	int sec_back_num = 1;
	int i = 0;

	for ( i = 0; i < element_index; i++)
	{
		sum = back_num + sec_back_num;
		sec_back_num = back_num;
		back_num = sum;
	}		

	return sum;
}  

int FibonacciRecursion(int element_index)
{

	if (element_index <= 1)
	{
		return element_index;
	}
	
	return FibonacciRecursion(element_index-1) + FibonacciRecursion(element_index-2) ;
	
	
	/* 0 1 1 2 3 5 8 13 21 34 55 */
}


struct node 
{
	int data;
	struct node *next;
}; 


Node *FlipList(Node *node)
{
	Node *fliped = NULL;
	
	if (NULL == node || NULL == node->next)
	{
		return node;
	}
	
	fliped = FlipList(node->next);
	
	node->next->next = node;
	node->next = NULL;
	
	return fliped;
}

size_t StrlenRecursion(const char *s)
{
	if ('\0' == *(s))
	{
		return 0;
	}
	
	return 1 + StrlenRecursion(s+1);
}

int StrcmpRecursion(const char *s1, const char *s2)
{
	if (*(s1) != *(s2) || !*s1) 
	{
		return *s1 - *s2;		
	}
	
	return StrcmpRecursion((s1+1),(s2+1));
}

char *StrcpyRecursion(char *dest, const char *src)
{
	if ('\0' == *src)
	{
		*dest = '\0';
		return dest;
	}
	
	*dest = *src;
	
	return StrcpyRecursion((dest+1),(src+1))-1;/* -1 come back to the begining of the return value(dest)   */
}
	
char *StrcatRecursion(char *dest, const char *src)
{
	
	if ('\0' == *dest)
	{
		 return StrcpyRecursion(dest,src);
	}
	
	return StrcatRecursion((dest+1),src)-1;
	
	 
}
	
char *StrstrRecursionWIthSize(const char *haystack, const char *needle, size_t size)
	{
	
		if ('\0' != *haystack)
		{
			if (*haystack == *needle && 0 == strncmp(haystack, needle, size))
			{
				return (char *)haystack;
			}
			return StrstrRecursion(haystack+1,needle);
		}
		else
		{
			return NULL;
		}
	
	}
char *StrstrRecursion(const char *haystack, const char *needle)
{
	
	size_t size = StrlenRecursion(needle);
	
	return StrstrRecursionWIthSize(haystack,needle,size);
	
}

stack_t *SortRecursive(stack_t *stack)
{
	int valueA = 0;
	int valueB = 0;
	int max = 0;
	if (StackSize(stack) > 1)
	{
		valueA = *(int*)StackPeek(stack);
		StackPop(stack);
		valueB = *(int*)StackPeek(stack);
		StackPop(stack);
		if (valueA > valueB)
		{
			max = valueA;
			StackPush(stack, &valueB);
			
		}
		else
		{
			max = valueB;
			StackPush(stack, &valueA);
		}
		
		SortRecursive(stack);
	}
	
	else if (StackSize(stack) == 1)
	{
		return stack;
	}
	
	StackPush(stack,&max);
	return stack;
}

stack_t *CheckStack(stack_t *stack,size_t size)
{
	if (size > 1)
	{
		SortRecursive(stack);
	}
	else
	{
		return stack;
	}
	
	return CheckStack(stack, size-1);
}
  
/*
void sort_stack(stack_t *stack)
{
	if (IsStackEmpty(stack))
	{
        	return;
    	}

    	int value = *(int*)StackPeek(stack);
    	StackPop(stack);
    	sort_stack(stack);
    	insert_sorted(stack, value);
}



void insert_sorted(stack_t *stack, int value)
{
    	if (IsStackEmpty(stack) || value > *(int*)StackPeek(stack))
    	{
      		StackPush(stack, &value);
        	return;
    	}

    	int temp = *(int*)StackPeek(stack);
    	StackPop(stack);
    	insert_sorted(stack, value);
    	StackPush(stack, &temp);
}

*/ 
