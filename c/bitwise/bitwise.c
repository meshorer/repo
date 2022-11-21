#include <stdio.h>


long Pow2(unsigned int x, unsigned int y)     /* reviewed by Yahav */
{
	size_t res;
	res = x<<y;
	
	return res;

}

unsigned int Is_pow2 (unsigned int n)
{
	return n &&  !(n & (n -1));    /* check */
}



unsigned int Is_pow2_loop (unsigned int n)
{
	
	while ( 1 <= n)
	{
		n = n>>1;
	}

	if (1 == n)
	{
		return 1;
	}
	
	return 0;
}

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


void Three_on(unsigned int *arr, int size)
{
	int i;
	printf("test for ex4:\n");
	for (i = 0; i < size; i++)
	{
		int tmp;
		int flag;
		
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

int main()
{
	/* declerations for ex1   */
	int res_ex1;
	
	/* declerations for ex2   */
	int res_ex2;
	int res_ex2_loop;
	
	/* declerations for ex3   */
	int res_ex3;
	
	/* declerations for ex4   */
	unsigned int arr_ex4[3] = {50,187,20};
	unsigned int arr_ex4b[5] = {50,187,20, 81, 97};
	
	/* test for ex1   */
	res_ex1 = Pow2(2,3);
	printf("test for ex1 is : %d\n", res_ex1);


	/* test for ex2   */
	res_ex2 = Is_pow2(0);
	printf("test for ex2 is :%d\n", res_ex2);

	/* test for ex2_loop   */
	res_ex2_loop = Is_pow2_loop(0);
	printf("test for ex2_loop is :%d\n", res_ex2_loop);
	
	/* test for ex3   */
	res_ex3 = Add1(157);
	printf("test for ex3 is :%d\n", res_ex3);
	
	/* test for ex4   */
	Three_on(arr_ex4, 3);
	Three_on(arr_ex4b, 5);

	return 0;

}


