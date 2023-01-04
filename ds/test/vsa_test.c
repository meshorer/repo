#include <stdio.h>
#include <stdlib.h>
#include "vsa.h"
#include "utilities.c"

#define HEADER_SIZE 24
#define WORD_SIZE sizeof(void *)

void PrintBlocks(vsa_t *vsa);



int main()
{
	char *new_memory = NULL;
	vsa_t *handler = NULL;
	
	void* ptr_1 = NULL;
	void* ptr_2 = NULL;
	void* ptr_3 = NULL;

	
	size_t size_ptr_1 = 48;
	size_t size_ptr_2 = 17;
	size_t size_ptr_3 = 20;


	new_memory = malloc(100*sizeof(int));

	handler = VsaInit(new_memory, 100*sizeof(int));
	
	/* test for alloc function */
	ptr_1 = VsaAlloc(handler,500);
	if (NULL == ptr_1){PRINT_TESTS(0);}else{PRINT_TESTS(1);}
	ptr_1 = VsaAlloc(handler,size_ptr_1);
	if (NULL != ptr_1){PRINT_TESTS(0);}else{PRINT_TESTS(1);}
	
	ptr_2 = VsaAlloc(handler,size_ptr_2);
	
	if (NULL != ptr_2){PRINT_TESTS(0);}else{PRINT_TESTS(1);}
	
	ptr_3 = VsaAlloc(handler,size_ptr_3);
	if (NULL != ptr_3){PRINT_TESTS(0);}else{PRINT_TESTS(1);}
	
	
	while (0 != size_ptr_1 % WORD_SIZE)  /* check word allignment */  
	{
		size_ptr_1 += sizeof(char);
	}   
	
	while (0 != size_ptr_2 % WORD_SIZE)  /* check word allignment */  
	{
		size_ptr_2 += sizeof(char);
	}   
	
	while (0 != size_ptr_3 % WORD_SIZE)  /* check word allignment */  
	{
		size_ptr_3 += sizeof(char);
	}   
	
	if (HEADER_SIZE + size_ptr_1 == (size_t)((char*)ptr_2 - (char*)ptr_1)){PRINT_TESTS(0);}else{PRINT_TESTS(1);}

	if (HEADER_SIZE + size_ptr_2 == (size_t)((char*)ptr_3 - (char*)ptr_2)){PRINT_TESTS(0);}else{PRINT_TESTS(1);}

	
	
	
	/* test for free function - depends on the implementation of the header struct*/
 	if (0 == *((int*)ptr_1 - 6)){PRINT_TESTS(0);}else{PRINT_TESTS(1);}
 	if (0 == *((int*)ptr_2 - 6)){PRINT_TESTS(0);}else{PRINT_TESTS(1);}
 	if (0 == *((int*)ptr_3 - 6)){PRINT_TESTS(0);}else{PRINT_TESTS(1);}
	VsaFree(ptr_1);
	


	/*if(size_ptr_1 - HEADER_SIZE - WORD_SIZE == VsaLargestChunk(handler)){PRINT_TESTS(0);}else{PRINT_TESTS(1);}*/
	VsaFree(ptr_2);	

	/*if ((size_ptr_1 + size_ptr_2)-(HEADER_SIZE)- WORD_SIZE == VsaLargestChunk(handler)){PRINT_TESTS(0);}else{PRINT_TESTS(1);} */

	
	/* test for aloc after free */
	ptr_1 = VsaAlloc(handler,32);
	ptr_2 = VsaAlloc(handler,16);
	PrintBlocks(handler);
	CHECK_ERROR(count_error);


	
	free(new_memory);
	return 0;
}



