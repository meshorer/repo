#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv, char** envp)
{
	size_t counter = 0, counter_2 = 0;	
	char **buf;
	char **buf2;
	char **tmp = buf;
	char **envp_start = envp;
		
	while (*envp)
	{
		counter++;
		envp++;

	}
	envp = envp_start;
	printf("counter is %lu\n", counter);
	
	buf =  (char **) malloc (sizeof(char)*counter);
	while (*envp)
	{
		while (**envp)
		{
			printf("check\n");
			counter_2++;
			*envp++;
		}
	printf("counter2 is %lu\n", counter_2);
	buf2 = (char **) malloc(counter_2*sizeof(char));
	envp++;
	}
}

/*
int main(int argc, char **argv, char** env)
{
	while (*env)
	printf("%s\n", *env);
	return 0;
}

while (*src)
	{
		*tmp = *src;
		tmp++;
		src++;
	}	
	*tmp = '\0';
	return dest;




*/

	
