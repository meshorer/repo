#include "recursion.h"


struct node 
{
	int data;
	struct node *next;
}; 

int main()
{

	Node *n4, *n3, *n2, *n1;
	Node *list;
	char string[] = "string";
	char srccpy[7] = "yosef";
	char destcpy[7] = "daniel";
	char srccat[7] = "second";
	char destcat[14] = "first";
	char haystack[15] = "heystack";
	char needle[7] = "ac";
	
	printf("tets for fibonacci - iteratively: \n");
	printf(" fib for 3 is: %d\n", Fibonacci(-1));
	printf(" fib for 200 is: %d\n", Fibonacci(6));
	
	printf("\n");
	printf("tets for fibonacci - Recursion: \n");
	printf(" fib for 3 is: %d\n", FibonacciRecursion(3));
	printf(" fib for 200 is: %d\n", FibonacciRecursion(6));
	printf("\n");
	
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
	
	printf("tets for strlen - Recursion: \n");
	printf("length of daniel is: %lu\n", StrlenRecursion(string));
	
	
	printf("tests for strcmp - Recursion: \n");
	printf(" strcmp for daniel and daliel: %d\n", StrcmpRecursion("daniel","daniel"));
	
	printf("tests for strcpy - Recursion: \n");
	StrcpyRecursion(destcpy,srccpy);
	printf(" strcpy for yosef: %s\n",destcpy);
	
	
	printf("test for strcat: %s\n",StrcatRecursion(destcat,srccat));
	printf("test for strstr: %s\n",StrstrRecursion(haystack,needle));
	
	
	return 0;
}
