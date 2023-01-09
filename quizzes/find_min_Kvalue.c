/*Find minimum k-value in array:
Given an array and a number K, where K is smaller than size of array, find the K’th smallest element in the given array. All array elements are distinct. */


#include <stdio.h>
#include <limits.h>

int MinimumKvalue(int *arr, int size, int k)
{

	int counter  = 0;
	int min = INT_MAX;
	int last_min =INT_MIN;
	int i = 0;
	
	if (size <=k)
	{
		return -1;
	}
	
	while (counter < k)
	{
	
		for (i = 0; i < size; i++)
		{
		
			if (arr[i] < min && arr[i] >last_min)
			{
				min = arr[i];
			}
			
		}
		++counter;
		last_min = min;
		min = INT_MAX;
	}
	
	return last_min;
	
}

int main()
{

	int arr[10] = {1,6,4,3,8,14,7,9,65,11};
	
	printf("min size in the k number is: %d\n",MinimumKvalue(arr,10,3));

	return 0;
}
