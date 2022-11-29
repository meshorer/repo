#include "atoi_itoa.h"

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


int Atoi10(const char * str)
{

	int res = 0;
	int sign = 1;
	char * ptr = (char *)str;
	if ( '-' == *ptr)
	{
		sign = -1;
		ptr++;
	}
	res = *ptr - '0';
	ptr++;
	
	while ( '\0' != *ptr)
	{
		res *=10;
		res += *ptr - '0';
		ptr++;
	}
	
	
	return res*sign;
}


