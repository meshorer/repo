#include <stdio.h>
#include <string.h>

void permute(char *str, size_t start, size_t str_len) 
{
	size_t i = 0;
	char tmp = 0;

	if (start == str_len) 
	{
		printf(" %s ", str);
	} 
	else 
	{
		for (i = start; i <= str_len; i++) 
		{
			tmp = str[start];
			str[start] = str[i];
			str[i] = tmp;
			
			permute(str, start+1, str_len);
			
			str[i] = str[start];
			str[start] = tmp;
		}
	}
}

int main() 
{
	char str[] = "abcd";
	
	permute(str, 0, strlen(str) - 1);

	return 0;
}

