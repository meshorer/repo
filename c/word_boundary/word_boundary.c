#include "word_boundary.h"



void *Memset(void *s, int c, size_t n)
{

	void *start = s;
	unsigned char *ptr = s;
	long buffer = (long) c;
	int i = 0;
	assert( NULL != s);
	assert( 0 != n);	
	
	for (i = 0; i<8; i++)
	{
		buffer <<= 8;
		buffer |= c;	
	}
	
	while ( 0 < n)
	{

		if ( 0 == (long) ptr % WORD_SIZE && n >= WORD_SIZE) /* when the adress is alligned */
		{
			*(long*) ptr = (long) buffer;
			ptr+=WORD_SIZE;
			n-=WORD_SIZE;			
		}
	
		else
		{
			*ptr = (unsigned char) c; 
			++ptr;
			--n;
		}
	}

	return start;
}

void *Memcpy(void *dest, const void *src, size_t n)
{
	void *start = dest;
	unsigned char *ptr_src =  (void *)src;
	unsigned char *ptr_dest = dest;
	assert (0 != n);
	assert ( NULL != src);
	assert (NULL != dest); 

	while ( n > 0)
	{
		if ( n >= WORD_SIZE)
		{
			*(long*) ptr_dest = *(long*) ptr_src;
			ptr_src+=WORD_SIZE;
			ptr_dest+=WORD_SIZE;
			n-=WORD_SIZE;			
		}
		
		else 
		{
			*ptr_dest = *ptr_src;
			++ptr_src;
			++ptr_dest;
			--n;		
		}
	
	}


	return start;
}


void *Memmove(void *dest, const void *src, size_t n)
{
	void *start = dest;
	unsigned char *ptr_src = (void *) src;
	unsigned char *ptr_dest = dest;
	unsigned char * end_src = ptr_src + n;
	unsigned char * end_dest = ptr_dest + n;
	assert (0 != n);
	assert ( NULL != src);
	assert (NULL != dest);  	
	
	if (ptr_dest < (ptr_src + n))
	{
		while ( n > 0)
		{		
			*end_dest = *end_src;
			--end_src;
			--end_dest;
			--n;			
		}	
		*end_dest = *end_src; 
	}       
       
      	else
      	{
      		Memcpy(ptr_dest, ptr_src, n);
      	} 
      	
      	return start;
      	
}


