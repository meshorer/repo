#include "string.h"

char *StrCpy(char *dest, const char *src)
{

	int i = 0;
	
	while (*(src+i) != '\0')
	{
		*(dest+i) = *(src+i);
		i++;
	}	
	
	return dest;
}	
	

char *StrNcpy(char *dest, const char *src, size_t n)
{
	size_t i = 0; 
	while (*(src+i) != '\0' && i<n)
	{
		*(dest+i) = *(src+i);
		i++;
	}
	
	if (sizeof(dest)>n)
	{
		for (; i<n; i++)
		{
			*(dest+i) = '\0';
		}
	}
	
	return dest;	
}

int StrCmp (const char* str1, const char* str2)
{
int res = 0;
int i = 0;

while (str1[i] == str2[i] && str1[i] != '\0' && str2[i] != '\0') 
{
	i++;

}

if (str1[i] > str2[i])
{
	res = 1;
}

else if (str2[i] > str1[i])
{
	res = -1;
}
return res;

}


int StrNcmp(const char *str1, const char *str2, size_t n)

{
	size_t i = 0;
	int res = 0;
	while (str1[i] == str2[i] && str1[i] != '\0' && str2[i] != '\0' && i<n)
	{
		i++;	
	}
	
	if (str1[i] > str2[i])
	{
	res = 1;
	}

	else if (str2[i] > str1[i])
	{
	res = -1;
	}
	return res;	
}








