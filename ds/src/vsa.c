#include <stddef.h> /* size_t */
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "vsa.h"

#define WORD_SIZE sizeof(void *)
void Defreg(vsa_t *vsa);
void PrintBlocks(vsa_t *vsa);

typedef struct header header_t;

struct vsa
{
	size_t count_allocs;
	void* first_header;
};


struct header
{
	size_t is_free;
	size_t size_block;
	void *next_block;
};
/***********************************/

/*------------------------------------
	Name: VsaInit
	Date: 01/01/2023
	Description: create struct in the begining of the memory pool 
	Status: writing
	Reviewer : 
------------------------------------*/
vsa_t *VsaInit(void *alloc_dest,size_t size)
{

	size_t *start = alloc_dest;
	char *check_aligned = (char*)start;
	vsa_t *new_vsa = NULL;
	header_t *new_header = NULL;

	/* check address allignment and reduce the size of needed */
	/*------------------------------------*/
	

	while (0 != (size_t)check_aligned % WORD_SIZE && size > WORD_SIZE)  
	{
		check_aligned += sizeof(char); /* use char * pointer to increment one byet at a time instead of 8*/
		size -=1;
	} 

	start = (size_t*)check_aligned;

	/*------------------------------------*/
	/* assert the fix size after allignment */
	
	assert(size > sizeof(struct vsa)+sizeof(struct header)); /* assert to the new size after alignment */
	
	/*------------------------------------*/
	
	new_vsa = (vsa_t*)start; /* assign the managing struct to the pool */

	new_vsa->count_allocs = 1;
	new_vsa->first_header = (size_t*)start + sizeof(struct vsa)/WORD_SIZE;
	
	/*------------------------------------*/
	
	start = new_vsa->first_header; /*jump after struct to first header*/
	new_header = (header_t*)start; /* assign the next-free to point to the block */

	/*------------------------------------*/
	/* assigning the header struct */
	
	new_header->is_free = 1; /* 1 is free  */
	new_header->next_block = NULL;
	new_header->size_block = size - (sizeof(struct vsa)) - (sizeof(struct header));

	return new_vsa;
	
}


/***********************************/

/*------------------------------------
	Name: VsaAlloc
	Date: Dec 13
	Description: allign, check for space (using largest_func), loop the blocks to find first block that suits
	Status: done
	Reviewer : 
------------------------------------*/

void *VsaAlloc(vsa_t *vsa,size_t block_size)
{

	void *block_ptr = NULL;
	size_t i = 0;
	header_t *current_header = (header_t*)vsa->first_header;
	header_t *new_header = NULL;
	size_t previous_size = current_header->size_block; 
	
	while (0 != block_size % WORD_SIZE)  /* check word allignment */  
	{
		block_size += sizeof(char);
	}   
	
	Defreg(vsa);
	
	block_size += sizeof(struct header);
	
		for (i =0; i < vsa->count_allocs; i++) /*loop over the pool to find the block */
		{
			if (current_header->is_free == 1 && current_header->size_block >= block_size)
			{
				block_ptr = ((char*)current_header + sizeof(struct header));
				current_header->next_block = (char*)current_header + block_size;
				current_header->is_free = 0;
				current_header->size_block = block_size;
				
				new_header = (header_t*)current_header->next_block;
				new_header->is_free = 1;
				new_header->size_block = previous_size - block_size;
				new_header->next_block = (char*)new_header + block_size;
				
				vsa->count_allocs++;
				return block_ptr;
			}
				
			current_header = (header_t*)current_header->next_block;
			previous_size = current_header->size_block;
		}	
	
		return NULL;

}

void VsaFree(void *block)
{
	size_t* free_block = (size_t*)block;
	
	assert(NULL != block);
	*(free_block - 3) = 1;
	
	
}

size_t VsaLargestChunk(vsa_t *vsa)
{

	
	size_t max = 0;
	size_t i = 0;	
	header_t *current_header = (header_t*)vsa->first_header;

	Defreg(vsa);

	for (i = 0; i < vsa->count_allocs; i++)
	{
	
		if (current_header->is_free== 1 && current_header->size_block > max)
		{
			max = current_header->size_block;
		}
		
		current_header = (header_t*)current_header->next_block;
	}
	
	
	return max;
}

void Defreg(vsa_t *vsa)
{

	header_t *current_header = (header_t*)vsa->first_header;
	header_t *next_header = (header_t*)current_header->next_block;
	size_t i = 0;
	size_t counter = 0;
	if (vsa->count_allocs > 1)
	{
			for (i = 1; i < vsa->count_allocs && NULL != current_header->next_block; i++)
			{	

				if (current_header->is_free== 1 && next_header->is_free== 1)
				{
					current_header->size_block += next_header->size_block;
					current_header->next_block = next_header->next_block;
					counter++;
					
				}
			
				current_header = (header_t*)current_header->next_block;	
				next_header = (header_t*)next_header->next_block;
			}	
	}

	vsa->count_allocs -= counter;
}

void PrintBlocks(vsa_t *vsa)
{

	header_t *current_header = (header_t*)vsa->first_header;
	size_t i = 0;
	printf("\n");
	for (i = 0; i < vsa->count_allocs; i++)
	{
		printf("print header number %lu\n",i+1);
		printf("current header start at: %p\n",current_header);
		printf("current_header->is_free: %lu\n",current_header->is_free);
		printf("current_header->size_block: %lu\n",current_header->size_block);
		printf("current_header->next_block: %p\n",current_header->next_block);
		printf("actual block starts at: %p\n",((char*)current_header + sizeof(struct header)));
		printf("|\nV\n");
		current_header = (header_t*)current_header->next_block;
	}
	
	printf("-------\n\n");
}
