#include <stddef.h> /* size_t */
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "fsa.h"

#define WORD_SIZE sizeof(void *)

struct fsa
{
	size_t block_size;
	size_t count_free;
	void *next_free;
};


size_t FsaSuggestedSize(size_t num_blocks, size_t block_size)
{
	size_t optimized;
	
	while (0 != block_size % WORD_SIZE) /* check word allignment */
	{
		block_size += sizeof(char);
	}  
	
	optimized = sizeof(struct fsa) + (num_blocks * WORD_SIZE) + (block_size * num_blocks) + WORD_SIZE-1; /* word-1 in case the address is not aligned */
	
	return optimized;
}

/* Description: the function creates the managment struct (and headers) ,and returns the pointer to that struct */
fsa_t *FsaInit(void *alloc_dest, size_t block_size, size_t suggested_size)
{
	size_t *start = (size_t*)alloc_dest;
	size_t block_plus_header = 0;
	size_t num_blocks = 0;
	size_t counter = 0;
	char *check_aligned = (char*)start;
	fsa_t *new_fsa = NULL;
	
	assert(suggested_size>sizeof(new_fsa));
	
	while (0 != block_size % WORD_SIZE)  /* check word allignment */
	{
		block_size += sizeof(char);
	} 
	
	while (0 != (size_t)check_aligned % WORD_SIZE)  /* check address allignment */
	{
		check_aligned += sizeof(char); /* use char * pointer to increment one byet at a time instead of 8*/
	} 
	
	start = (size_t*)check_aligned;
	block_plus_header = block_size + WORD_SIZE; 
	
	new_fsa = (fsa_t*)start; /*assign struct in allocated dest */
	printf("start of pool(func) : %p\n",new_fsa);
	
	num_blocks = (suggested_size - sizeof(struct fsa)) / block_plus_header; /*calculate number of blocks after optimization */
	
	new_fsa->block_size = block_size;
	printf("block size is : %lu\n",new_fsa->block_size);
	new_fsa->count_free = num_blocks;
	
	new_fsa->next_free = (size_t*)start+sizeof(struct fsa)/WORD_SIZE;
	printf("first next is  : %p\n",new_fsa->next_free);
	
	
	
	*(size_t*)&start += sizeof(struct fsa); /*jump after struct to first header*/
	
	while (counter < num_blocks) /* assign headers in their place  */
	{
		*(size_t *)start = (size_t)start + block_plus_header; /*  assign the pointer to point to the next header   */
		printf("header is : %p \n",start);

		start = (size_t*)start + block_plus_header/WORD_SIZE; /*  jump to next header */

		counter++;
	}

	start = NULL;  /* assign the last header to point to null  */
	
	return new_fsa;
}



void *FsaAlloc(fsa_t *fsa)
{
	size_t *tmp = (size_t*)fsa->next_free;  /* save the current next free in tmp   */
		
	if(0 == fsa->count_free)
	{
		return NULL;
	}
	

	fsa->next_free = (void *)(*tmp);  /*  assign the next free ot point to the value-direference of itself  */
	fsa->count_free--;	
	
	
	return (size_t *)tmp+1; /* return the tmp plus wordsize to get to the block   */
}


void FsaFree(fsa_t *fsa, void *block)
{
	*((size_t *)block - 1) = (size_t)fsa->next_free;  /*  -1 to get the header, assign it to point to the next free    */
	fsa->next_free = (size_t*)(block) - 1;  /* assign the next free to point to the freed block   */
	
	fsa->count_free++;
}

size_t FsaCountFree(const fsa_t *fsa)
{
	return fsa->count_free;
}
