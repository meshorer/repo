#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

int main()
{
	 char src[5] = {'m','i','k','g'};
	 char dest[5];
	StrCpy(dest,src);
	puts (src);
	puts (dest);
	return 0;
}
