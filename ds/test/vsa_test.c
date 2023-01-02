#include <stdio.h>
#include <stdlib.h>
#include "vsa.h"
#include "utilities.c"




int main()
{
	char *new_memory = NULL;
	vsa_t *handler = NULL;
	
	void* ptr = NULL;
	
	new_memory = malloc(100*sizeof(int));

	handler = VsaInit(new_memory+1, 100*sizeof(int));
	
	ptr = VsaAlloc(handler,15);
	
	
	
	
	

	

	
	free(new_memory);
	return 0;
}



