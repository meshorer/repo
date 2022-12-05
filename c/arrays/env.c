#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


int main(int argc, char **argv, char** envp)
{
	
	size_t counter = 0;
	char **envp_start = envp;
	char **arr = NULL;
	char **arr_start = NULL;
	int j, k;
	while (*envp) /* find out size of envp and malloc it  */
	{
		counter++;
		envp++;
	}
	
	envp = envp_start;
	arr = malloc(counter*sizeof(char*));
	arr_start = arr;
	while ('\0' != *envp) /* find out size of every string, malloc and copy it */
	{
		*arr = malloc((strlen(*envp)+1)*sizeof(char));
		strcpy(*arr,*envp);
		j = 0, k = 0;
		while ('\0' != *(*(arr)+j)) /* lowercases */
		{
			
			*(*(arr)+j) = tolower(*(*(arr)+j));
			j++;

		}
		printf("%s\n", *arr);
		free(*arr);
		envp++;
		arr++;
	}

	envp = envp_start;
	arr = arr_start;
	free(arr);
	
	return 0;
	
}
	
