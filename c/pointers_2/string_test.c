#include "string.h"


int main()
{
	 char src[5] = {'m','i','k','g'};
	 char dest[5];
	 size_t n = 3;
	/*StrCpy(dest,src);
	puts (src);
	puts (dest);*/
	StrNCpy(dest,src,n);
	puts (src);
	puts (dest);
	printf("%c ", *(dest+2));
	
	return 0;
}
