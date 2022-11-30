#include "atoi_itoa.h"

/* reviewed by Arthur */

void Itoa10(int num, char *str, int base)
{
	
	int sign = 0;
	char * ptr = str;
	int count = 0;
	int chr = '0';
	if ( base > 25)
	{
		chr+=7;
	}
	
	if ( num < 0)
	{
		sign--;
		num*=-1;
		*ptr = '-';
		ptr++;
	}
	
	while ( num >= base)
	{
		*ptr = (num % base) + chr;
		count ++;
		num = num / base;
		ptr++;
	}
	if (base > 25 && num < 9)
	{
		chr = '0';
	}
	count ++;
	*ptr = num + chr;
	*(ptr+1) = '\0';
	
	Reverse((str + sign), count);
	

}

void Reverse(char * str, int count)
{
	int i = 0;
	char temp;
	int j = count/2;
	count -=1;
	for ( i = 0; i < j; i ++)
	{
		temp = str[i];
		str[i] = str[count];
		str[count] = temp;
		count --;
	}
}


int Atoi10(const char * str, int base)
{

	int res = 0;
	int sign = 1;
	char * ptr = (char *)str;

	if ( '-' == *ptr)
	{
		sign = -1;
		ptr++;
	}
	
	while ( '\0' != *ptr)
	{
		res *=base;
	
		res += *ptr -'0' -(*ptr > '9') * ('A' - '9' -1);
		++ptr;
	}
	
	
	return res*sign;
}

int Endian()
{
/* return 0 if little, 1 if big */
	int check = 1;
	char *ptr = (char *) &check;
	
	if (0 == *ptr)
	{
		check = 0;	
	}
	
	return check;
}


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


