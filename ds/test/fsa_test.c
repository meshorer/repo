#include <stdio.h>
#include <stdlib.h>
#include "fsa.h"

int main()
{
	size_t suggested = 0;
	fsa_t *new_memory = NULL;
	void *handler = NULL;
	void *handler2 = NULL;
	void *handler3 = NULL;
	void *handler4 = NULL;
	void *handler5 = NULL;
	
	suggested = FsaSuggestedSize(4,4);
	
	printf("suggested size is : %lu\n", suggested);

	new_memory = malloc(88);
	new_memory = FsaInit(new_memory, 4, 88);
	printf("after init:\n");
	printf("first count free is : %lu\n\n", FsaCountFree(new_memory));
	printf("after 1 alloc:\n");
	handler = FsaAlloc(new_memory);
	printf("block is : %p\n", handler);
	printf("count free is : %lu\n\n", FsaCountFree(new_memory));

	printf("after 2 alloc:\n");
	handler2 = FsaAlloc(new_memory);
	printf("block is : %p\n", handler2);
	printf("count free is : %lu\n\n", FsaCountFree(new_memory));
	
	printf("after 3 alloc:\n");
	handler3 = FsaAlloc(new_memory);
	printf("block is : %p\n", handler3);
	printf("count free is : %lu\n\n", FsaCountFree(new_memory));
	
	
	printf("after 4 alloc:\n");
	handler4 = FsaAlloc(new_memory);
	printf("block is : %p\n", handler4);
	printf("count free is : %lu\n\n", FsaCountFree(new_memory));
	
	printf("after free:\n");
	FsaFree(new_memory, handler4);
	printf("count free is : %lu\n\n", FsaCountFree(new_memory));
	handler4 = FsaAlloc(new_memory);
	printf("block is : %p\n", handler4);

	free(new_memory);
	return 0;
}
