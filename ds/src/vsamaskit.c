#include <assert.h> /* assert */
#include <stdio.h>
#include "vsa.h"

/* 1 = free */

#define COOKIE 0xDEADBEEF
#define WORD_SIZE sizeof(long)

typedef struct header header_t;

struct vsa
{
	size_t *first_header;
};

struct header
{
	size_t is_free;
	void *next_block;
	size_t block_size;
	size_t cookie;
};

/* description: merge two consecutive free blocks */
void Defragmentation(vsa_t *vsa)
{
	header_t *current_header = (header_t*)vsa->first_header;			/* first header used to iterate */
	header_t *next_header = (header_t*)current_header->next_block;		/* second header used to iterate */
	
	assert(vsa);
	
	while(current_header != NULL && current_header->next_block != NULL)		/* make sure both headers are valid */
	{
		if((current_header->is_free == 1) && (next_header->is_free == 1))	/* if both are free */
		{
			current_header->block_size += next_header->block_size;	/* merge size */
			current_header->next_block = next_header->next_block;
			next_header = next_header->next_block;			/* move next and keep current in place */
			next_header->cookie = 0;					/* deleted header disassigns DEADBEEF */
		}									/* this way can merge more than 2 headers in O(n) */
		else
		{
			current_header = current_header->next_block;			/* move both iterators */
			next_header = next_header->next_block;
		}
	}	
}

/* description: align address and size to WORD if needed
		create management struct + first header
		return management struct */
vsa_t *VsaInit(void *alloc_dest, size_t size)
{
	vsa_t *my_vsa = NULL; 								/* management struct */
	header_t *header = NULL;                                      		/* header struct */
	size_t remainder_address = (size_t)alloc_dest % WORD_SIZE;			/* check if address isn't aligned to WORD */   
	char *start_address = (char*)alloc_dest;					
 	
	assert(size >= (sizeof(vsa_t) + sizeof(header_t))); 				/* make sure size has enough space for management struct + first header */
	assert(alloc_dest);    				        		/* make sure valid address received */
	
	if(0 != remainder_address) 							/* add padding if address isn't aligned to WORD */
	{
		size = size - (WORD_SIZE - remainder_address);
		start_address += (WORD_SIZE - remainder_address);
	}
	
	my_vsa = (vsa_t*)start_address;						/* asign management struct to first memory address */
	my_vsa->first_header = (size_t*)start_address + sizeof(vsa_t)/WORD_SIZE;	/* first header is right after management struct */
	
	header = (header_t*)my_vsa->first_header;					/* initialize first header */	
	header-> is_free = 1;			 		
	header->next_block = NULL;
	header->block_size = size - sizeof(vsa_t);					/* block size includes header */
	header->cookie = COOKIE;
	
	return my_vsa; 
}

/* description: create new block of memory, update header accordingly
		create new header for the rest of the remaining memory
		return allocated address or NULL if allocation failed.  */
void *VsaAlloc(vsa_t *vsa, size_t block_size)
{  
	void *return_block = 0;
	header_t *current_header = (header_t*)vsa->first_header;
	size_t remainder_block = block_size % WORD_SIZE; 			
	size_t original_block_size = current_header->block_size;
	void *saved_next = NULL; 
	
	assert(vsa);									/* make sure valid struct received */
	
	if(0 != remainder_block)   							/* align block size to WORD if needed */
	{
		block_size += (WORD_SIZE - remainder_block);
	}
	block_size += sizeof(header_t); 						/* add header size */
	
	Defragmentation(vsa);
	printf("block size: %lu\n", block_size);
	printf("header address: %p\n", current_header);
	
	while(current_header != NULL)											
	{
		original_block_size = current_header->block_size;
		
		if((current_header->is_free == 1) && (current_header->block_size >= block_size))	/* if block is free and requested size fits */
		{
			saved_next = current_header->next_block;					 
			printf("current block size: %lu\n", current_header->block_size);
			current_header->is_free = 0; 							/* modift header to be unavailable */
			current_header->cookie = COOKIE;						/* add DEADBEEF to header */
			return_block = (size_t*)current_header + (sizeof(header_t)/WORD_SIZE);	/* save return address */
			
			/* there's enough space for new header + memory to use */
			if(original_block_size - block_size >= (sizeof(header_t) + WORD_SIZE)) 	/* if there's enough remainder space to be used in block after requested alloc */
			{										
				current_header->next_block = (char*)current_header + block_size;	/* update next block */
				current_header->block_size = block_size; 				/* update block size to be size of requested block */
				current_header = current_header->next_block;				/* move to next header */
				
				current_header->is_free = 1;						/* next header is free */
				current_header->block_size = original_block_size - block_size;	/* next header's block size is the remainder */
				current_header->cookie = COOKIE;				
				
				if(saved_next == NULL)							/* previous headers's next was NULL, meaning it was the last header */
				{
					current_header->next_block = NULL;				/* update this header's next to be NULL */
					printf("new block size: %d\n", current_header->block_size);
				} 
				else									/* if it wasn't the last one */
				{
					current_header->next_block = saved_next;			/* update this header to point to the previous header's next */
				}
			}
			return return_block;								/* alloc succeful - return saved block */
		}
		current_header = current_header->next_block;						/* this block is not free/doesn't have enough space, move to the next */
	}
	return NULL;											/* no block was found available to requested size */
}

/* description: update received block to be available */
void VsaFree(void *block)
{
	header_t *current_header = NULL;
	
	assert(block);									
	
	printf("recieved block: %p\n", block);
	
	current_header = (header_t*)block - 1;							/* move received block back to its header */
	printf("header to free: %p\n", current_header);
	
	#ifdef DEBUG
		printf("debug: %p\n", current_header->cookie);
		assert(current_header->cookie == COOKIE);
	#endif	
	
	current_header->is_free = 1;									/* modify it to be unavailable */ 
	printf("is header free? %lu\n", current_header->is_free);
}

/* description: search for largest block available
		return its size (minus header size) */
size_t VsaLargestChunk(vsa_t *vsa)
{
	header_t *current_header = (header_t*)vsa->first_header;					
	size_t largest_chunk = 0;
	
	assert(vsa);
	
	Defragmentation(vsa);
	
	while(current_header != NULL)
	{
		if((current_header->is_free == 1) && (current_header->block_size > largest_chunk))  /* check which block is largest */
		{
			largest_chunk = current_header->block_size - sizeof(header_t);		/* saved size is calculated without its header size */
		}
		current_header = current_header->next_block;						/* move to next header */
	}
	return largest_chunk;
}


void PrintBlocks(vsa_t *vsa)
{

	header_t *current_header = (header_t*)vsa->first_header;
	size_t i = 0;
	printf("\n");
	while(current_header != NULL)
	{
		printf("print header number %lu\n",i+1);
		printf("current header start at: %p\n",(void*)current_header);
		printf("current_header->is_free: %u\n",current_header->is_free);
		printf("current_header->size_block: %lu\n",current_header->block_size);
		printf("current_header->next_block: %p\n",current_header->next_block);
		printf("actual block starts at: %p\n",((char*)current_header + sizeof(struct header)));
		printf("|\nV\n");
		current_header = current_header->next_block;
		++i;
	}
	
	printf("-------\n\n");
}
