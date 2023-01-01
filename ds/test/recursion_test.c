#include "recursion.h"
#include "utilities.c"
#include "stack.h"


struct node 
{
	int data;
	struct node *next;
}; 

int main()
{
 

	stack_t *stack = StackCreate(5, sizeof(int));
	int values[] = {5, 3, 1, 2, 4};
	int i = 0;
	
	Node *n4, *n3, *n2, *n1;
	Node *list;
	char string[] = "string";
	char srccpy[7] = "yosef";
	char destcpy[7] = "daniel";
	char srccat[7] = "second";
	char destcat[14] = "first";
	char haystack[15] = "heystack";
	char needle[7] = "ac";
	
	/*tets for fibonacci - iteratively*/
	
	if (2 == Fibonacci(3)){PRINT_TESTS(0);}else{PRINT_TESTS(1);}

	/*tets for fibonacci - Recursion*/
	if (2 == FibonacciRecursion(3)){PRINT_TESTS(0);}else{PRINT_TESTS(1);}

	printf("tets for FLIP SLL: \n");
	
	n4 = malloc(sizeof(Node));
	n4->data = 4;
	n4->next = NULL;
	n3 = malloc(sizeof(Node));
	n3->data = 3;
	n3->next = n4;
	n2 = malloc(sizeof(Node));
	n2->data = 2;
	n2->next = n3;
	n1 = malloc(sizeof(Node));
	n1->data = 1;
	n1->next = n2;
	list = n1;

	printf("\nthe list before flip is:\n");
	printf("%d->", list->data);
	printf("%d->", list->next->data);
	printf("%d->", list->next->next->data);
	printf("%d->", list->next->next->next->data);
	printf("%p", (void*)list->next->next->next->next);
	printf("\n");
	printf("the list address :%p->", (void*)list);
	printf("%p->", (void*)n1->next);
	printf("%p->", (void*)n2->next);
	printf("%p->", (void*)n3->next);
	printf("%p->", (void*)n4->next);
	printf("\n");
	
	list = FlipList(list);
	
	printf("\nthe list after flip is:\n");
	
	printf("%d->", list->data);
	printf("%d->", list->next->data);
	printf("%d->", list->next->next->data);
	printf("%d->", list->next->next->next->data);
	printf("%p", (void*)list->next->next->next->next);
	printf("\n");
	printf("the list address :%p->", (void*)list);
	printf("%p->", (void*)list->next);
	printf("%p->", (void*)list->next->next);
	printf("%p->", (void*)list->next->next->next);
	printf("%p->", (void*)list->next->next->next->next);
	printf("\n");
	
	free(n4);
	free(n3);
	free(n2);
	free(n1);
	
	/*tets for strlen - Recursion */
	if (6 == StrlenRecursion(string)){PRINT_TESTS(0);}else{PRINT_TESTS(1);}
	
	/*tests for strcmp - Recursion*/
	if (0 == StrcmpRecursion("daniel","daniel")){PRINT_TESTS(0);}else{PRINT_TESTS(1);}
	
	/*tests for strcpy - Recursion*/
	StrcpyRecursion(destcpy,srccpy);
	if (0 == StrcmpRecursion(destcpy,srccpy)){PRINT_TESTS(0);}else{PRINT_TESTS(1);}
	
	/*tests for strcat - Recursion*/
	if (0 == StrcmpRecursion("firstsecond",StrcatRecursion(destcat,srccat))){PRINT_TESTS(0);}else{PRINT_TESTS(1);}
	
	/*tests for strstr - Recursion*/

	if (0 == StrcmpRecursion("ack",StrstrRecursion(haystack,needle))){PRINT_TESTS(0);}else{PRINT_TESTS(1);}
	
	printf("\n\ntests for stack - Recursive\n");
	for (i = 0; i < 5; i++)
    	{
        	StackPush(stack, &values[i]);
    	}
	
	printf("stack size is: %lu\n", StackSize(stack));    
	printf("\nstack before sort:\n"); 	
    	for (i = 0; i < 5; i++)
	{
		printf("%d ", *(int*)StackPeek(stack));
		StackPop(stack);
	}
	
	for (i = 0; i < 5; i++)
    	{
        	StackPush(stack, &values[i]);
    	}
    	
    	stack = CheckStack(stack, 5);
	printf("\nstack after sort:\n"); 
    	for (i = 0; i < 5; i++)
	{
		printf("%d ", *(int*)StackPeek(stack));
		StackPop(stack);
	}
	printf("\n"); 
	StackDestroy(stack);
    	
	CHECK_ERROR(count_error);
	
	return 0;
}
