#include <stdio.h> /* for print */
#include <string.h>  /* for strcmp */
#include "slist.h"

int match_func(const void *data, void *parameter);
int action_func(void *data, void *parameter);


int main()
{

	int i = 0;
	char str1 [] = "node 1";
	char str2 [] = "node 2";
	char str3 [] = "node 3";
	char str4 [] = "node 4";
	char str5 [] = "node 5";
	char str6 [] = "node 6";
	char str7 [] = "node 8";
	
	s_list_t *list1 = SListCreate(); 

	
	s_list_iterator_t start = SListBegin(list1); /* dummy */
	s_list_iterator_t next = SListNext(start); /*node 1 */
	
	printf("\n");
	printf("-----------------------------\n");
	printf("test for add and get function !\n");
	printf("\n");
	next = SListAdd(list1,start,str1);
	puts(SListGet(list1, next));
	next = SListNext(next);

	next = SListAdd(list1,next,str2);
	puts(SListGet(list1, next));
	next = SListNext(next);
	
	next = SListAdd(list1,next,str3);
	puts(SListGet(list1, next));
	next = SListNext(next);
	
	next = SListAdd(list1,next,str4);
	puts(SListGet(list1, next));
	next = SListNext(next);
	
	next = SListAdd(list1,next,str5);
	puts(SListGet(list1, next));
	next = SListNext(next);
	
	next = SListAdd(list1,next,str6);
	puts(SListGet(list1, next));
	
	
	printf("\n");
	printf("-----------------------------\n");
	printf("\n");
	
	printf("test for set function !\n");
	printf("\n");
	printf("node was: ");
	puts(SListGet(list1, next));
	SListSet(list1, next, str7); 
	printf("after set node is: ");
	puts(SListGet(list1, next));

	printf("\n");
	printf("-----------------------------\n");
	printf("\n");
	
	printf("test for size function !\n");
	printf("\n");
	printf("number of elements (size) is: %lu\n",SListSize(list1));
	printf("\n");
	printf("-----------------------------\n");
	printf("\n");

	
	printf("test for remove function !\n");
	printf("\n");
	next = start; /* str1 */
	next = SListNext(next);
	next = SListNext(next);
	next = SListRemove(list1, next); /* node 3 */
	printf("number of elements (size) after remove 1 is: %lu\n",SListSize(list1));
	
	next = start;
	for (i = 0; i < 5; i++)
	{
		puts(SListGet(list1, next));
		next = SListNext(next);
	}
	printf("\n");
	printf("-----------------------------\n");
	printf("\n");
	
	printf("test for SListFind function !\n");
	printf("\n");
	
	next = SListFind(start,next,match_func,"node 4");
	if (NULL == next)
	{
		printf("no match found!\n");
	}
	else
	{
		puts(SListGet(list1, next));	
	}
		
	printf("-----------------------------\n");
	printf("\n");


	printf("test for end function !\n");
	printf("\n");
	next = start;
	next = SListEnd(list1);
	printf("dummy is: %d\n",SListGet(list1, next));
	
	
	printf("\n");
	printf("-----------------------------\n");
	printf("\n");
	
	printf("test for SListForEach function !\n");
	printf("\n");
	
	
	if (SListForEach(list1,start,next,action_func, "each") == 0)
	{
		printf("action complete\n");
	}
	else
	{
		printf("action failed\n");
	}

	printf("\n");
	
	next = start;
	for (i = 0; i < 5; i++)
	{
		puts(SListGet(list1, next));
		next = SListNext(next);
	}
	printf("\n");
	printf("-----------------------------\n");
	printf("\n");
	SListDestroy(list1);
	
	
	return 0;
	
}


   
int match_func(const void *data, void *parameter)
{
	int result = strcmp(data,parameter);
	
	return result;
}
	
int action_func(void *data, void *parameter)
{
	int result = 1; 
	
	memcpy((void *)data,parameter,strlen(parameter));
	result = strcmp(data,parameter);
	
	return result;
}





