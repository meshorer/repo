#include "structs.h"


void AddInt(void *ptr, int num_to_add)
{
	*(int *) ptr += num_to_add; 
}


void AddFloat(void *ptr, int num_to_add)
{
	*(float *) ptr += num_to_add; 	
}


void AddString(void *ptr, int num_to_add)
{
	printf("ok");
}


void PrintInt(void *ptr)
{
printf("%d\n", *(int *) ptr);
}

void PrintFloat(void *ptr)
{
printf("%f\n",*(float *)ptr);
}

void PrintString(void *ptr)
{
printf("%s\n", (char *)ptr);
}



/*float f = *(float *) &ptr; */
