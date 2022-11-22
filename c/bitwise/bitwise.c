#include "bitwise.h"

 /* reviewed by Yahav */
long Pow2(unsigned int x, unsigned int y)    
{
	size_t res;
	res = x<<y;
	
	return res;

}
 /* reviewed by Yahav */
unsigned int Is_pow2 (unsigned int n)
{
	return n &&  !(n & (n -1));    /* check */
}


 /* reviewed by Yahav */
unsigned int Is_pow2_loop (unsigned int n)
{
	
	while ( 1 < n)
	{
		n = n>>1;
	}

	if (1 == n)
	{
		return 1;
	}
	
	return 0;
}
 /* reviewed by Yahav */
int Add1(int n)
{
	int y = 1;
	
	while ( n & y)
	{
		n = n ^ y; /*    flip all the bits */
		y <<=1;	
	} 
	
	n = n ^ y; /*flip the right 0 bit */
	return n;
}

/* reviewed by Yosef   */ 
void ThreeOn(unsigned int *arr, int size)
{
	int i;
	printf("test for ex4: "); 
	for (i = 0; i < size; i++)
	{
		int tmp = 0;
		int flag = 0;
		
		tmp = arr[i];
		flag = 0;
		while ( 0  != tmp)
		{
			if (( tmp & 1) == 1)
			{
				flag++;
			}
			
			tmp = tmp >>1;
		}
		if ( 3 == flag)
		{
			printf("%d, ", arr[i]);
		}
	}
		printf("\n");
}
 /* reviewed by Yahav */
void ByteMirrorLoop(unsigned char ch)
{
	
	int rev = 0;
	int i = 0;
	for ( i = 6; i>=0; i--)
	{

		if (( ch & 1) == 1)
		{
			rev = rev + (2<<i);	
		}
		ch = ch>>1;
	}
	printf("test for ex5 : %d\n", rev);
}
 /* reviewed by Yahav */
void ByteMirror(unsigned char x)
{
	x = x >> 4 | x << 4;
	x = ((x >> 2) & 0x33) | ((x & 0x33) << 2);
	x = ((x >> 1) & 0x55) | ((x & 0x55) << 1);
	printf("test for ex5 without loop: %d\n", x);
}

 /* reviewed by Yahav */
int Ex6a(unsigned char n)
{
	
	return ((1 == (n>>1 & 1)) && (1 == (n>>5 & 1)));
}

 /* reviewed by Yahav */
int Ex6b(unsigned char n)
{
	
	return ((1 == (n>>1 & 1)) || (1 == (n>>5 & 1)));
}

 /* reviewed by Yahav */
int Ex6c(unsigned char n)
{
		
		unsigned char third = (n>>2) & 1; 
		unsigned char fifth = (n>>4) & 1;
		unsigned char res = 0;
		unsigned char c = third ^ fifth;
		c = (c << 2) | (c << 4);
		res = n ^ c; 		
		return res;
}

 /* reviewed by Yahav */
int DividedSixteen(unsigned int n)
{
	n  = n >> 4;
	return n << 4;
}

 /* reviewed by Yahav */
void Swap(int *x, int *y)
{
	*x = *x ^ *y ;
	*y = *x ^ *y ;
	*x = *x ^ *y ;
}

 /* reviewed by Yahav */
void CountBitsLoop(int n)
{

	int counter = 0;
	int i = 0;	
	while ( 0  != n && i < 32)
	{
		if (( n & 1) == 1)
		{
			counter++;
		}			
		n = n >>1;
		i++;
	}
		
		printf("test for ex9 is : %d\n", counter);
}


void CountBits(int i)
 {
	i = i - ((i >> 1) & 0x55555555);
	i = (i & 0x33333333) + ((i >> 2) & 0x33333333);
	i = (i + (i >> 4)) & 0x0f0f0f0f;
	i = i + (i >> 8);
	i = i + (i >> 16);
	printf("test for ex9b : %d\n",  i & 0x3f);
	
	/*
The first line counts the number of ones every two bits and store them using two bits. For example, 01101100 -> 01011000. The original can be grouped to 01 10 11 00, the number of ones is 1, 1, 2, 0 			then written in binary is 01011000.

The second counts the number of ones every four bits and store them using four bits. The number we obtained after the first operation is 01011000, then we group them into 0101, 1000 and add neighbour two bits, 01+01=10, 10+00=10, and represent them using four bits, which is 0010 0010.

And this goes on every 8, 16, 32 bits.
	
	*/
}

/*reviewed by Maskit */
void Bynary(int n)
{

    int buff = 0;
    int i = 31;

    while(i >= 0)
    {
        buff = (n & (1 << i));
        if(buff == 0)
        {
            printf("0");
        } 
        else
        {
            printf("1");
        }
        -- i;
    }
}



