#include <stdio.h>


void AppearsTwo(char *str1, char * str2, char * str3, int len1, int len2, int len3)
{
	int i = 0;
	int help_str[256] = {0};
	
	for ( i = 0; i < len1; i++)
	{
		if ( 0 == help_str[(int)str1[i]])
		{
			help_str[(int)str1[i]]++;
		}
	} 
	
	for ( i = 0; i < len2; i++)
	{
		if ( 1 == help_str[(int)str2[i]])
		{
			help_str[(int)str2[i]]++;
		}
	} 
	
	for ( i = 0; i < len3; i++)
	{	
		help_str[(int)str3[i]]--;
	} 	
	
	for (i = 0; i < 256; i++)
	{
		if ( 2 == help_str[i])
		{
			printf("%c ",i);
		}
	}

	printf("\n");
}


int main()
{
	char str1[5] = {'a', 'b', 'c', 'd', 'e'};
	char str2[7] = {'e', 'b', 'c', 'd', 'e', 'f', 'e'};
	char str3[4] = {'b', 'x', 'a', 'a'};
	
	char str4[16] = "hello world 90%";
	char str5[16] = "world hello 99%";
	char str6[18] = "hello warning 71#";	
	
	AppearsTwo(str1, str2, str3, 5, 7, 3);
	AppearsTwo(str4, str5, str6, 16, 16, 18);

	return 0;	
}


