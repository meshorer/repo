#include <stdio.h>


void AppearsTwo(char *str1, char * str2, char * str3, int len1, int len2, int len3)
{
	int i = 0;
	int help_str[256] = {0};
	
	for ( i = 0; i < len1; i++)
	{
		if ( 0 == help_str[str1[i]])
		{
			help_str[str1[i]]++;
		}
	} 
	
	for ( i = 0; i < len2; i++)
	{
		if ( 1 == help_str[str2[i]])
		{
			help_str[str2[i]]++;
		}
	} 
	
	for ( i = 0; i < len3; i++)
	{	
		help_str[str3[i]]--;
	} 	
	
	for (i = 0; i < 256; i++)
	{
		if ( 2 == help_str[i])
		{
			printf("%c ",i);
		}
	}


}


int main()
{
	char str1[5] = {'a', 'b', 'c', 'd', 'e'};
	char str2[7] = {'e', 'b', 'c', 'd', 'e', 'f', 'e'};
	char str3[4] = {'b', 'x', 'a', 'a'};
	
	AppearsTwo(str1, str2, str3, 5, 7, 3);


	return 0;	
}


