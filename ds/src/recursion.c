#include "recursion.h"

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

char *strcpyRecursion(char *dest, const char *src)
{
	if ('\0' == *src)
	{
		*dest = '\0';
		return dest;
	}
	
	*dest = *src;
	
	return strcpyRecursion((dest+1),(src+1))-1;/* -1 come back to the begining of the return value(dest)   */
}
	
char *strcatRecursion(char *dest, const char *src)
{
	
	if ('\0' == *dest)
	{
		 return strcpyRecursion(dest,src);
	}
	
	return strcatRecursion((dest+1),src)-1;
	
	
}
	



