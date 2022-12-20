/* You are given a 2d array of ints. Write a function that looks for indices whose values are equal to 0 and set their entire rows and columns to 0 */

#include <stdio.h>

#define columns 5
#define rows 5

void NUllifyMatrix(int arr[][columns])
{

	int i = 0;
	int j = 0;
	int k = 0;
	
	int arr_rows[rows] = {0};
	int arr_columns[columns] = {0};
	
	for ( i = 0; i < rows ; i++)
	{
		for ( j = 0; j< columns ; j++)
		{
			if(0 == arr[i][j])
			{
				arr_rows[i] = 1;
				arr_columns[j] = 1;
			}
		}
	}
	
	for ( i = 0; i < rows ; i++)
	{
		for ( j = 0; j< columns ; j++)
		{
			if(0 == arr[i][j])
			{
				if (1 == arr_rows[i])
				{
					for(k = 0; k < columns; k++)
					{
						arr[i][k] = 0;
					}
				}
				
				if (1 == arr_columns[j])
				{
					for(k = 0; k < rows; k++)
					{
						arr[k][j] = 0;
					}
				}
			}
		}
	}
}

int main()
{
	
	int i = 0;
	int j = 0;
	int matrix[rows][columns] = {{1,2,3,4,5},{6,7,0,9,1},{1,0,1,1,1},{1,1,1,1,2},{2,2,2,2,2}};
	
	printf("before function :\n");
	
	for ( i = 0; i < rows ; i++)
	{
		for ( j = 0; j< columns ; j++)
		{
			printf("%d ",matrix[i][j]);
		}
		printf("\n");
	}
	NUllifyMatrix(matrix);
	
	printf("\n");
	
	printf("after function :\n");
	
	for ( i = 0; i < rows ; i++)
	{
		for ( j = 0; j< columns ; j++)
		{
			printf("%d ",matrix[i][j]);
		}
		printf("\n");
	}


return 0;
}
