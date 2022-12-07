#include "struct.h"

#include <stdio.h> /* for print */
#include <string.h> /* for strcpy */
#include <stdlib.h>  /* for malloc, realloc */
#include <assert.h>  /* for asserts */


/************************************/
/*   */
/*date: Dec 6
description: add int to int
Reviewer: 
*/

void AddInt(void *ptr, int num_to_add)
{
	assert(ptr);
	
	*(int *) ptr += num_to_add; 
}

/**************************************/

/*date: Dec 6
description: add int to float
Reviewer: 
*/

void AddFloat(void *ptr, int num_to_add)
{
	assert(ptr);
	
	*(float *) ptr += num_to_add; 	
}

/**************************************/

/*date: Dec 6
description: add int to string
Reviewer: 
*/

void AddString(void **ptr, int num_to_add) /* receives **ptr to make sure the realloc ptr will not delete after returning from the function */
{
	
	char buffer[11] = {0};
	int len = sprintf(buffer,"%d",num_to_add); /* find numbers of chats to add */
	
	assert(*ptr);	
		
	*ptr = (char *)realloc (*ptr,strlen(*ptr)+len+1);
	sprintf(*ptr, "%s%d", (char *)*ptr, num_to_add); /* concatenate numbers with chats */
}

/**************************************/

/*date: Dec 6
description: print int
Reviewer: 
*/

void PrintInt(void *ptr)
{
	assert(ptr);	
	
	printf("%d\n", *(int *)&ptr);
}

/**************************************/

/*date: Dec 6
description: print float
Reviewer: 
*/

void PrintFloat(void *ptr)
{
	assert(ptr);	
	
	printf("%f\n",*(float *)&ptr);
}

/**************************************/

/*date: Dec 6
description: print string
Reviewer: 
*/

void PrintString(void *ptr)
{
	assert(ptr);	
	
	printf("%s\n", (char *)ptr);
}

/**************************************/

/*date: Dec 6
description: free dynamic allocation
Reviewer: 
*/

void Cleanup(void *ptr)
{
	assert(ptr);
	
	free(ptr);
	printf("cleaned!\n");
}

/**************************************/

/*date: Dec 6
description: fake function
Reviewer: 
*/

void Empty()
{

}

/**************************************/

/*date: Dec 6
description: initialize float structure
Reviewer: 
*/

struct mixed_types InitFloat(float num)
{
	struct mixed_types Floatstr;
	
	*((float *)&Floatstr.element) = num;
	Floatstr.add = AddFloat;
	Floatstr.print = PrintFloat;
	Floatstr.clean = Empty;
	
	return Floatstr;
}

/**************************************/

/*date: Dec 6
description: initialize int structure
Reviewer: 
*/

struct mixed_types InitInt(int num)
{
	struct mixed_types Intstr;

	
	*((int *)&Intstr.element) = num;
	Intstr.add = AddInt;
	Intstr.print = PrintInt;
	Intstr.clean = Empty;
	
	return Intstr;
}

/**************************************/

/*date: Dec 6
description: initialize string structure
Reviewer: 
*/

struct mixed_types InitString(char *ptr)
{
	struct mixed_types Stringstr;
	
	Stringstr.element = (char *)malloc(strlen(ptr)+1);
	strcpy(Stringstr.element,ptr);
	Stringstr.add = AddString;
	Stringstr.print = PrintString;
	Stringstr.clean = Cleanup;
	
	return Stringstr;
}

/**************************************/

/*void PrintInt(struct mixed_types *ptr)
{
	printf("%d\n",(int *)ptr->element);
}
*/

