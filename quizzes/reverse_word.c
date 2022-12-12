#include<string.h>
#include<stdio.h>
#include <stdlib.h>


void Reverse_String(char *src, int len)
{
	char *result = malloc(len+1);
	int i = len-1;
	char *ptr_end = '\0';
	int tmp = 0;
	
	while (i >= 0)
	{
	
		while (src[i] != ' ' && i != 0)
		{
			i--;
		} 

		if (i == 0)
		{	
			strcat(result,src);
			break;
		}
		
		ptr_end = strrchr(src,' ')+1; 
		strcat(result, ptr_end); 
		tmp = strlen(result);
		result[tmp] = ' ';
	
		src[i] = '\0';
		
	}
	
	memcpy(src,result,len); 
	free(result);

}

int main()
{
	
	char str[] = "I am student";
	int len = strlen(str);
	Reverse_String(str,len);
	puts(str);
	
	


return 0;
}
