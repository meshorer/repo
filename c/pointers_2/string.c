#include "string.h"

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
	while (*str1 == *str2 && str1 && str2 && i<n)
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
	printf("ctmps are %c %c \n",ctmp1,ctmp2);
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
			printf("2 if\n");
			printf("now they %c %c \n",ctmp1,ctmp2);
		}
	
		if (ctmp1 != ctmp2)
		{
			printf("need to exit\n");
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
	char * dup = NULL;
	char *ptr = NULL;
	dup= malloc(sizeof(s));
	if (!dup)
	{
		return NULL;
	}
	else
	{
		ptr = dup;
		while (s)
		{
			*dup = *s;
			s++;
			dup++;
		}
	
		return ptr;
	}

}

