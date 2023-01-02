#include <stddef.h> /* size_t */
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "vsa.h"

#define WORD_SIZE sizeof(void *)

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
	

	printf("address before aligment : %p\n", start);
	while (0 != (size_t)check_aligned % WORD_SIZE && size > WORD_SIZE)  
	{
		check_aligned += sizeof(char); /* use char * pointer to increment one byet at a time instead of 8*/
		size -=1;
	} 

	start = (size_t*)check_aligned;
	printf("address after aligment : %p\n", start);
	/*------------------------------------*/
	/* assert the fix size after allignment */
	
	assert(size > sizeof(struct vsa)+sizeof(struct header)); /* assert to the new size after alignment */
	
	/*------------------------------------*/
	
	new_vsa = (vsa_t*)start; /* assign the managing struct to the pool */
	printf("managing struct is at : %p\n", start);
	new_vsa->count_allocs = 1;
	new_vsa->first_header = (size_t*)start + sizeof(struct vsa)/WORD_SIZE;
	
	/*------------------------------------*/
	
	*(size_t*)&start += sizeof(struct vsa); /*jump after struct to first header*/
	new_header = (header_t*)start; /* assign the next-free to point to the block */
	printf("header starts at : %p\n", start);
	/*------------------------------------*/
	/* assigning the header struct */
	
	new_header->is_free = 1; /* 1 is free  */
	new_header->next_block = NULL;
	new_header->size_block = size - (sizeof(struct vsa)) - (sizeof(struct header));
	printf("size block is : %lu\n", new_header->size_block );
	
	
	
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
	
	block_size += sizeof(struct header);
	
	if (VsaLargestChunk(vsa) >= block_size)   /* check that there is a size that big */
	{
		
		for (i =0; i < vsa->count_allocs; i++) /*loop over the pool to find the block */
		{
			if (current_header->is_free== 1 && current_header->size_block >= block_size)
			{
				printf("here1\n");
				block_ptr = current_header->next_block;
				printf("here2\n");
				current_header->next_block = current_header + block_size;
				printf("here3\n");
				current_header->is_free = 0;
				printf("here4\n");
				new_header = current_header->next_block;
				printf("here5\n");
				new_header->is_free = 1;
				printf("here6\n");
				new_header->size_block = previous_size - block_size;
				printf("here7\n");
				new_header->next_block = NULL;
				break;
			}
				printf("here2\n");
				new_header = new_header->next_block;
		}	
	}
	
	else
	{
		return NULL;
	}
	
	
	vsa->count_allocs++;
	printf("address of alloc is : %p\n",block_ptr);
	return block_ptr;
}



size_t VsaLargestChunk(vsa_t *vsa)
{

	/*  send to defregmentation function first  */
	/*
	size_t max = 0;
	size_t i = 0;
	vsa_t *check_next = vsa->next_free;
	
	for (i = 0; i < vsa->count_allocs; i++)
	{
		if (*((size_t *)check_next - 1) > max)
		{
			max = *((size_t *)check_next - 1);
		}
		
		check_next = check_next->next_free;
	}
	
	*/
	
	
	return 200;
}
