#include "word_boundary.h"



void *Memset(void *s, int c, size_t n)
{

	void *start = s;
	unsigned char *ptr = s;
	long buffer = (long) c;
	int i = 0;
	for (i = 0; i<8; i++)
	{
		buffer <<= 8;
		buffer |= c;	
	}
	
	
	while ( 0 < n)
	{
	
	
		if ( 0 == (int)ptr % WORD_SIZE && WORD_SIZE < n) /* when the adress is alligned */
		{
			*(long*) ptr = (long) buffer;
			ptr+=WORD_SIZE;
			n-=WORD_SIZE;		/* move pointer by 8? */	
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



