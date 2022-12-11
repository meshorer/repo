#include<string.h>
#include<stdio.h>


char * Reverse_String(char *src, int len)
{
	char result[16] = {'\0'};
	int i = 0;
	char *ptr_end = '\0';
	int counter_end = 0;
	
	while (src[i] != ' ')
	{
		i--;
	} 
	
	ptr_end = strchr(src,' ');
	strcat(result, ptr_end);
	return result;
}

int main()
{
	
	char str[16] = "daniel meshorer";
	char *new;
	new = Reverse_String(str,16);
	puts(new);
	
	


return 0;
}
