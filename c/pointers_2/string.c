#include "string.h"



size_t StrLen(const char *s)

{
    
    size_t counter = 0; 
    while (*s)
   {
     counter++;  
     s++;
   }
   
  return counter;
}


char *StrCpy(char *dest, const char *src)
{

	char *tmp = dest;
	while (*src)
	{
		*tmp = *src;
		tmp++;
		src++;
	}	
	*tmp = '\0';
	return dest;
}	
	

char *StrNcpy(char *dest, const char *src, size_t n)
{	
	size_t i = 0;
	char *tmp = dest;	
	while (*src && i<n)
	{
		*tmp = *src;
		tmp++;
		src++;
		i++;
	}

	
	if (sizeof(dest)>n)
	{
		for (; i<n; i++)
		{
			dest[i] = '\0';
		}
	}
	
	return dest;	
}

int StrCmp (const char* str1, const char* str2)
{
int res = 0;
while (*str1 == *str2 && str1 && str2) 
{
	str1++;
	str2++;
}

if (*str1 != *str2)
{
	res = *str1 - *str2;
}
return res;

}


int StrNcmp(const char *str1, const char *str2, size_t n)

{
	size_t i = 0;
	int res = 0;
	while (*str1 == *str2 && *str1 && *str2 && i<n)
	{
		str1++;
		str2++;	
		i++;
	}
	
	if (*str1 > *str2)
	{
	res = 1;
	}

	else if (*str2 > *str1)
	{
	res = -1;
	}
	return res;	
}


int StrCasecmp(const char *str1, const char *str2)
{
	int res = 0;
	int i = 0;
	char ctmp1;
	char ctmp2;
	while (str1)
	{
	ctmp1 = str1[i];
	ctmp2 = str2[i];
	if (str1[i] != str2[i])
	{
		if (ctmp1 >= 'A' && ctmp1 <= 'Z')
		{
			ctmp1 = ctmp1+32;
			printf("1 if\n");
		}
	
		if (ctmp2 >= 'A' && ctmp2 <= 'Z')
		{
			ctmp2 = ctmp2+32;
		}
	
		if (ctmp1 != ctmp2)
		{
			break;
		}
	}

	i++;
	}

	if (ctmp1 > ctmp2)
	{
		res = 1;
	}

	else if (ctmp1 < ctmp2)
	{
		res = -1;
	}
	return res;
}
	

char *StrChr(const char *s, int c)
{
	char *res = (char *)*s;
	while (s && *s != c)
	{
		s++;
	}

	return res;
}


char *StrDup(const char *s)
{

size_t len = StrLen(s);

char *s_sec = malloc((len*sizeof(char)));
while (*s)
{
	*s_sec = *s;
	s++;
	s_sec++;
}

return s_sec-len;
}





 char *StrCat(char *dest, const char *src)
{

	while (*dest)
	{
		dest++;
	}

	while (*src)
	{
		*dest = *src;
		dest++;
		src++;	
	}
	
	return dest;   
} 


 char *StrNcat(char *dest, const char *src, size_t n)
{
	size_t i = 0;

	while (*dest)
	{
		dest++;
	}
	
	while (*src && i !=n)
	{
		*dest = *src;
		dest++;
		src++;	
		i++;
	}
	
	return dest;   
    
}


char *StrStr(const char *haystack, const char *needle)
{

	const char *start = haystack;
	const char *start_n = (char*) needle;
	start = haystack;
	while (*haystack)
	{

		if (*haystack == *needle)
		{
			start = haystack;
		
			while (*haystack == *needle && *needle)
			{
				haystack++;
				needle++;

			}

			if (!*needle) 
			{
				return (char *) start;
			}
			else 
			{

				haystack = (char*) start;
				
			}
		}
		haystack++;
		needle = start_n;
	}	
	return NULL;
}





