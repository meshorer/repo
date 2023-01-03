#include <stdio.h>
#include <stdlib.h>
#include "vsa.h"
#include "utilities.c"




int main()
{
	char *new_memory = NULL;
	vsa_t *handler = NULL;
	
	void* ptr_1 = NULL;
	void* ptr_2 = NULL;
	void* ptr_3 = NULL;
	void* ptr_4 = NULL;
	void* ptr_5 = NULL;
	
	new_memory = malloc(100*sizeof(int));

	handler = VsaInit(new_memory, 100*sizeof(int));
	printf("largest after init is: %lu\n",VsaLargestChunk(handler));	
	ptr_1 = VsaAlloc(handler,15);
	printf("largest after alloc 1 is: %lu\n",VsaLargestChunk(handler));
	ptr_2 = VsaAlloc(handler,17);
	printf("largest after alloc 2 is: %lu\n",VsaLargestChunk(handler));
	ptr_3 = VsaAlloc(handler,176);
	printf("largest after alloc 3 is: %lu\n",VsaLargestChunk(handler));
	ptr_4 = VsaAlloc(handler,10);
	printf("largest after alloc 4 is: %lu\n",VsaLargestChunk(handler));
	PrintBlocks(handler);


	VsaFree(ptr_3);
	printf("largest after free 3 is: %lu\n",VsaLargestChunk(handler));

	VsaFree(ptr_2);

	printf("largest after alloc of 10 is: %lu\n",VsaLargestChunk(handler));

	ptr_5 = VsaAlloc(handler,10);
	PrintBlocks(handler);
	
	
	
	printf("%d\n",0x5643428ef300 - 0x5643428ef2f0 );
	free(new_memory);
	return 0;
}



