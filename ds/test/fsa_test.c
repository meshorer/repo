#include <stdio.h>
#include "fsa.h"

int main()
{
	size_t suggested = 0;
	suggested = FsaSuggestedSize(4,4);
	
	printf("suggested size is : %lu\n", suggested);

	return 0;
}
