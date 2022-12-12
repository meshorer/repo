#include <stdio.h> /* for print */

#include "singly_linked_list.h"



int main()
{

	int i = 0;
	char str1 [] = "node 1";
	char str2 [] = "node 2";
	char str3 [] = "node 3";
	char str4 [] = "node 4";
	char str5 [] = "node 5";
	char str6 [] = "node 6";
	
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
	next = SListNext(next);
	
	printf("\n");
	printf("-----------------------------\n");
	
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
	printf("-----------------------------\n");
	printf("\n");
	printf("test for end function !\n");
	printf("\n");
	next = start;
	next = SListEnd(list1);
	puts(SListGet(list1, next));
	
	
	SListDestroy(list1);
	
	
	return 0;
	
}

