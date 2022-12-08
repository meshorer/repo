#include<stdio.h>

int SetTwoBits(unsigned int num)		
{
	int counter = 0;
	
	while (num)
	{
		if ((num & 1) && (num >> 1))
		{
			counter++;
		}
		num >>= 1;
	}
	return counter;
}


void Swap1(int *x, int *y)
{
	int tmp = *x;
	*x = *y;
	*y = tmp;
}


void Swap2(int *x, int *y)
{
	*x = *x ^ *y;
	*y = *x ^ *y;
	*x = *x ^ *y;
}


int setBitsLoop(long num)
{
	int count = 0;
	while (num)
	{
		num = (num & (num - 1));
		++count;
	}
	return count;
}

int main()
{
	
	return 0;
}

