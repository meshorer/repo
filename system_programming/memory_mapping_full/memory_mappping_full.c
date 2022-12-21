#include <stdio.h>
#include <stdlib.h>
#include "memory_mappping_full.h"

static void StaticFunc() {}
void ExternFunc() {}

const int con_global = 0;
int non_con_global = 0;

static const int con_static_global = 2;	
static int non_con_static_global = 3;

void MappingFull() 
{
	int *heap = (int*)malloc(sizeof(int));
	int *heap2 = (int*)malloc(100*sizeof(int));
	int non_con_local = 5;
	printf("\n**** STACK ****\n");
	char *str = "ravid";
	printf("str address:                  %p\n", &str);
	printf("heap address:                 %p\n", &heap);
	printf("heap2 address:                %p\n", &heap2);
	const int con_local = 10;
	printf("con_local address:            %p\n", &con_local);
	printf("non_con_local address:        %p\n", &non_con_local);
	
	printf("\n**** HEAP ****\n");
	printf("heap2 content:                %p\n", heap2);
	printf("heap content:                 %p\n", heap);
	
	printf("\n**** BSS ****\n");
	printf("non_con_global address:       %p\n", &non_con_global);
	static const int con_static_local = 0;
	printf("con_static_local address:     %p\n", &con_static_local);
	printf("con_global address:           %p\n", &con_global);
	
	printf("\n**** RODATA ****\n");
	printf("str content:                  %p\n", str);
	printf("con_static_global address:    %p\n", &con_static_global);
	
	printf("\n**** DATA ****\n");
	static int non_con_static_local = 4;
	printf("non_con_static_local address: %p\n", &non_con_static_local);
	printf("non_con_static_global address:%p\n", &non_con_static_global);

	printf("\n**** TEXT ****\n");
	printf("ExternFunc address:           %p\n", &ExternFunc);
	printf("StaticFunc address:           %p\n", &StaticFunc);

        free(heap);
}

