#include "structstest.h"

/*
void AddInt(void *ptr, int num_to_add)
{
	*(int *) ptr += num_to_add; 
}
*/

void AddInt(struct mixed_types *ptr, int num_to_add)
{
	 ptr->element = (int *)ptr->element + (num_to_add)/sizeof(int); 
}

void AddFloat(struct mixed_types *ptr, int num_to_add)
{
	
	ptr->element = (float *)ptr->element + (num_to_add); 
}


void AddString(struct mixed_types *ptr, int num_to_add) 
{
	sprintf(ptr->element, "%s%d", (char *)ptr, num_to_add);
}


void PrintInt(struct mixed_types *ptr)
{
	printf("%d\n",(int *)ptr->element);
}

void PrintFloat(struct mixed_types *ptr)
{
	printf("%f\n",(float *)ptr->element);
}

void PrintString(struct mixed_types *ptr)
{
printf("%s\n", (char *)ptr->element);
}

void Cleanup(void *ptr)
{
	free(ptr);
	printf("cleaned!\n");
}


