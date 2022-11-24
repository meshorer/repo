#include <stdio.h>


struct mixed_types{

	void *element;
	void (*add)(void *, int);
	void (*print)(void *);
};

void AddInt(void *ptr, int num_to_add);
void AddFloat(void *ptr, int num_to_add);
void AddString(void *ptr, int num_to_add);
void PrintInt(void *ptr);
void PrintFloat(void *ptr);
void PrintString(void *ptr);
