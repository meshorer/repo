#define WORD_SIZE sizeof(void *)

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

