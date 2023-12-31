#include <stddef.h> /* size_t */
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "vsa.h"

#define WORD_SIZE sizeof(void *)
#define DEADBEEF 0xDEADBEEF 
#define HEADER_SIZE sizeof(struct header)

void Defreg(vsa_t *vsa);
           

typedef struct header header_t;

struct vsa
{
	size_t count_allocs;
	void* first_header;
};


struct header
{
	unsigned int is_free;
	unsigned int magic_number;
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

	size_t *start = NULL;
	char *check_aligned = NULL;
	vsa_t *new_vsa = NULL;
	header_t *new_header = NULL;
	
	assert(NULL != alloc_dest);

	start = alloc_dest;
	check_aligned = (char*)start;
	
	
	
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
	
	assert(size > sizeof(struct vsa)+ HEADER_SIZE + WORD_SIZE); 			/* assert to the new size after alignment and the sizes of the managing struct, header and at least one WORD of block */
	
	/*------------------------------------*/
	
	new_vsa = (vsa_t*)start; 										/* assign the managing struct to the pool */

	new_vsa->count_allocs = 1;
	new_vsa->first_header = (size_t*)start + sizeof(struct vsa)/WORD_SIZE;
	
	/*------------------------------------*/
	
	start = new_vsa->first_header; 										/*jump after struct to first header*/
	new_header = (header_t*)start; 										/* assign the next-free to point to the block */

	/*------------------------------------*/
	/* assigning the header struct */
	
	new_header->is_free = 1; 										/* 1 is free  */
	new_header->next_block = (char*)new_vsa->first_header + HEADER_SIZE;
	new_header->size_block = size - sizeof(struct vsa) - HEADER_SIZE;
	new_header->magic_number = DEADBEEF;

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

	void *block_ptr = NULL; 										/* a pointer to point to the block we found */
	size_t i = 0;
	header_t *new_header = NULL;
	header_t *current_header = NULL;
	size_t previous_size = 0;
	
	assert(NULL != vsa);

	current_header = (header_t*)vsa->first_header;
	previous_size = current_header->size_block; 
	
	while (0 != block_size % WORD_SIZE)  									/* check word allignment */  
	{
		block_size += sizeof(char);
	}   
	
	Defreg(vsa);
		
	for (i =0; i < vsa->count_allocs; i++) 									/*loop over the pool to find a block */
	{
		if (current_header->is_free == 1 && current_header->size_block >= (block_size + HEADER_SIZE))   /*you must check that besides the block-size, you have room for (next) header-size */
		{
			block_ptr = ((char*)current_header + HEADER_SIZE); 					/*assign the block pointer to point to the start of the block */
			current_header->next_block = (char*)block_ptr + block_size; /*				assign to the header of the next block */
			current_header->is_free = 0;
			current_header->size_block = block_size; 						/*the actual net size, without the header-size */
			current_header->magic_number = DEADBEEF; 						/*assign a key place-holder */
			
			new_header = (header_t*)current_header->next_block; 					/* assign a key place-holder */
			new_header->is_free = 1; 								/* assign the new header to next block as free */
			new_header->size_block = previous_size - block_size - HEADER_SIZE; 			/* the size of next block should be the previous size minus the header size */
			new_header->next_block = (char*)current_header->next_block + HEADER_SIZE + new_header->size_block; /* assigning   the header of the next block to be at the end of the size */
			
			vsa->count_allocs++;

			return block_ptr;
		}
			 
		current_header = current_header->next_block; 							/* advance the current header to the next one */
		previous_size = current_header->size_block;							/* update the previous size to the current-header size */
	}	

	return NULL;
}

void VsaFree(void *block)
{
	
	header_t* to_free = (header_t*)block-1;
	assert(NULL != block);
	
	#ifdef DEBUG
		assert(to_free->magic_number == DEADBEEF);
	#endif	
	
	to_free->is_free = 1;
	
	
}

size_t VsaLargestChunk(vsa_t *vsa)
{
	size_t max = HEADER_SIZE + WORD_SIZE; 						/* keep in mind that after an alloc you should create a header at its end */
	size_t i = 0;	
	header_t *current_header = NULL;
	
	assert(NULL != vsa);
	current_header = (header_t*)vsa->first_header;
	
	Defreg(vsa);
 
	for (i = 0; i < vsa->count_allocs; i++) 					/* loop to find the biggest free block */
	{
		if (current_header->is_free== 1 && current_header->size_block > max)
		{
			max = current_header->size_block;
		}
		
		current_header = (header_t*)current_header->next_block; 		/* advance the header to its next */
	}
	
	return max - HEADER_SIZE - WORD_SIZE; 						/* return the exact (net) size that the user can  */
}

void Defreg(vsa_t *vsa)
{

	header_t *current_header = NULL;
	header_t *next_header = NULL;
	size_t i = 0;
	
	assert(NULL != vsa);
	
	current_header = (header_t*)vsa->first_header;
	next_header = (header_t*)current_header->next_block;
	
	for (i = 1; i < vsa->count_allocs; i++) 					/* i starts from one because the last header doesn't have a 'next-header' */
	{	

		if (current_header->is_free== 1 && next_header->is_free== 1) 		/* check that both of the adjacent headers are free  */
		{
			current_header->size_block += next_header->size_block + HEADER_SIZE; /* the size of the first block should recieve the size of the second block  */
			current_header->next_block = next_header->next_block; 		/* the first header next->block should point to where the second header pointed to */
			next_header->magic_number = 2; 					/* because we "delete" this header we would like to overwrite the DEADBEEF (for edge cases)*/
			vsa->count_allocs --;
			
		}
	
		current_header = (header_t*)current_header->next_block;			/* advance the header to its next */
		next_header = (header_t*)next_header->next_block;			/* advance the next header to its next */
	}	
}

void PrintBlocks(vsa_t *vsa)
{

	header_t *current_header = (header_t*)vsa->first_header;
	size_t i = 0;
	printf("\n");
	for (i = 0; i < vsa->count_allocs; i++)
	{
		printf("print header number %lu\n",i+1);
		printf("current header start at: %p\n",(void*)current_header);
		printf("current_header->is_free: %u\n",current_header->is_free);
		printf("current_header->size_block: %lu\n",current_header->size_block);
		printf("current_header->next_block: %p\n",current_header->next_block);
		printf("actual block starts at: %p\n",((char*)current_header + sizeof(struct header)));
		
		printf("|\nV\n");
		current_header = (header_t*)current_header->next_block;
	}
	/*printf("\nlargest net block is: %lu\n",VsaLargestChunk(vsa));*/
	printf("-------\n\n");
}
