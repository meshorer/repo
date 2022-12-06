
#ifndef __STRUCTS_H__
#define __STRUCTS_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX2(x,y) ((x>y)?x:y)
#define MAX3(x,y,z) \
(x>y && x> z) ? x; (y > z) ? y:z)
#define my_sizeof(type) (char *)(&type+1)-(char*)(&type)

struct mixed_types{

	void *element;
	void (*add)(struct mixed_types *, int);
	void (*print)(struct mixed_types *);
	void (*clean)(void *);
};

void AddInt(struct mixed_types *ptr, int num_to_add);
void AddFloat(struct mixed_types *ptr, int num_to_add);
void AddString(struct mixed_types *ptr, int num_to_add);
void PrintInt(struct mixed_types *ptr);
void PrintFloat(struct mixed_types *ptr);
void PrintString(struct mixed_types *ptr);
void Cleanup(void *ptr);









#endif
