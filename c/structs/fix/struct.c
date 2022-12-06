#include "struct.h"

/*
void AddInt(void *ptr, int num_to_add)
{
	*(int *) ptr += num_to_add; 
}
*/

/*void AddInt(struct mixed_types *ptr, int num_to_add)
{
	 ptr->element = (int *)ptr->element + (num_to_add)/sizeof(int); 
}*/

void AddInt(void *ptr, int num_to_add)
{
	*(int *) ptr += num_to_add; 
}

/*void AddFloat(struct mixed_types *ptr, int num_to_add)
{
	
	ptr->element = (float *)ptr->element + (num_to_add); 
}*/

void AddFloat(void *ptr, int num_to_add)
{
	*(float *) ptr += num_to_add; 	
}


void AddString(void **ptr, int num_to_add) 
{
	char buffer[11] = {0};
	int len = sprintf(buffer,"%d",num_to_add);
	*ptr = (char *)realloc (*ptr,strlen(*ptr)+len+1);
	sprintf(*ptr, "%s%d", (char *)*ptr, num_to_add);
}


/*void PrintInt(struct mixed_types *ptr)
{
	printf("%d\n",(int *)ptr->element);
}
*/
void PrintInt(void *ptr)
{
	printf("%d\n", *(int *)&ptr);
}
/* void PrintFloat(struct mixed_types *ptr)
{
	ptr++;
	printf("%f\n",((float *)ptr->element));
}*/

void PrintFloat(void *ptr)
{
	printf("%f\n",*(float *)&ptr);
}

void PrintString(void *ptr)
{
	printf("%s\n", (char *)ptr);
}
void Cleanup(void *ptr)
{
	free(ptr);
	printf("cleaned!\n");
}

void Empty()
{

}
struct mixed_types InitFloat(float num)
{
	struct mixed_types Floatstr;
	
	*((float *)&Floatstr.element) = num;
	Floatstr.add = AddFloat;
	Floatstr.print = PrintFloat;
	Floatstr.clean = Empty;
	
	return Floatstr;
}

struct mixed_types InitInt(int num)
{
	struct mixed_types Intstr;

	
	*((int *)&Intstr.element) = num;
	Intstr.add = AddInt;
	Intstr.print = PrintInt;
	Intstr.clean = Empty;
	
	return Intstr;
}

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

