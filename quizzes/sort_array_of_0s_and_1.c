
/*Given an array of values 0 and 1, implement a function that sorts the 0 to the beginning and 1 to the end.

Note: You cannot sort by simply counting the number of 0s and 1s. Implement the sort algorithm by swapping elements.*/


#include<stdio.h>




void Sort0sAnd1s(int *arr, int size)
{

	int left = 0;
	int tmp = 0;
	int i = 0;
	
    	for (i = 0; i < size; i++) 
    	{
        	if (arr[i] == 0)
        	{
            		tmp = arr[left];
            		arr[left] = arr[i];
            		arr[i] = tmp;
            		left++;	
		}
		
	}
}


int main()
{

	int arr[10] = {0,1,1,0,1,0,1,0,0,1};
	int i = 0;
	
	printf("before change: \n");
	for (i = 0; i < 10; ++i)
	{
		printf("%d ", arr[i]);
	
	}
	
	printf("\n");
	Sort0sAnd1s(arr,10);
	
	printf("after change: \n");
	for (i = 0; i < 10; ++i)
	{
		printf("%d ", arr[i]);
	
	}

	printf("\n");

	return 0;
}
