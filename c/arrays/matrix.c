#include <stdio.h>

int main()
{
	int matrix[2][3] = { {1, 4, 2}, {3, 6, 8} };
	int res[2];
	int r = 2;
	int c = 3;
	int i = 0;
	sum_matrix(matrix, r,c,res);
	
	for (i = 0; i < r; i++)
	{
		printf("%d ,", res[i]);
	}
	
	return 0;
}



void sum_matrix( int r, int c, int arr[2][3], int *res)
{
	int i = 0;
	for (i = 0; i < r; i++)
	{
		int sum = 0;
		int j = 0;
		for (j = 0; j < c; j++)
		{
			sum = sum + arr[i] [j];
		}
		*res = sum;
		res++;	
	}
}


/*
rowCalc(arr1, res, 4, 4);
	for (; k < 4; k++)
	{
		printf("%d ",res[k]);
	}
	printf("\n");

*/
