#include <stddef.h> /* size_t */
#include <string.h>

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
	
	optimized = sizeof(struct fsa) + (num_blocks * WORD_SIZE) + (block_size * num_blocks);
	
	return optimized;
}

/* Description: the function creates the managment struct (and headers) ,and returns the pointer to that struct */
fsa_t *FsaInit(void *alloc_dest, size_t block_size, size_t suggested_size)
{
	void *start = alloc_dest;
	size_t block_plus_header = 0;
	size_t num_blocks = 0;
	size_t counter = 0;
	fsa_t *new_fsa = NULL;
	
	while (0 != block_size % WORD_SIZE)  /* check word allignment */
	{
		block_size += sizeof(char);
	} 
	
	block_plus_header = block_size + WORD_SIZE;
	
	num_blocks = (suggested_size - sizeof(struct fsa)) / block_plus_header;
		
	new_fsa->block_size = block_size;
	new_fsa->count_free = num_blocks;
	new_fsa->next_free = (long*)alloc_dest+sizeof(struct fsa);
	
	new_fsa = (fsa_t*)alloc_dest; /*assign struct here */
	
	
	*(long*)&alloc_dest += sizeof(struct fsa); /*jump after struct */

	while (counter < num_blocks)
	{
		*(long *)&alloc_dest = *(long *)&alloc_dest + block_plus_header;

		counter++;
	}

	alloc_dest = NULL;
	
	return start;
	
}



void *FsaAlloc(fsa_t *fsa)
{

	void *tmp = fsa->next_free;
	*((long *)fsa->next_free) = (long)fsa->next_free;
	fsa->count_free--;	
	
	
	return (long *)tmp+WORD_SIZE;
}


void FsaFree(fsa_t *fsa, void *block)
{
	*((long *)block - WORD_SIZE) = (long)fsa->next_free;
	fsa->next_free = (long*)(block) - WORD_SIZE;
	
	fsa->count_free++;
}

size_t FsaCountFree(const fsa_t *fsa)
{
	return fsa->count_free;
}
