#include "string.h"

char *StrCpy(char *dest, const char *src)
{

	int i = 0;
	
	while (*(src+i) != '\0' || *(dest+i) != '\0')
	{
		*(dest+i) = *(src+i);
		i++;
	}	
	
	return dest;
}	
	


char *StrNCpy(char *dest, const char *src, size_t n)
{
	size_t i = 0; 
	while (*(src+i) != '\0' && i<n)
	{
		*(dest+i) = *(src+i);
		i++;
	}
	
	if (sizeof(dest)>n)
	{
		for (; i<n; i++)
		{
			*(dest+i) = '\0';
		}
	}
	
	return dest;	
}


