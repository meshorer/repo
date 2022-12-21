#include "memory_mappping_full.h"
#include <stdio.h>

int main(int argc, char **argv, char **envp)
{
	printf("argv address:                 %p\n", &argv);
	printf("envp address:                 %p\n", &envp);
	ExternFunc();
	
	MappingFull(); 
	printf("ex1\n");
	
	return 0;
}




