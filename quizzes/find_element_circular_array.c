/*Given a circular sorted array of integers, search an element in it. Assume there are no duplicates in the array and the rotation is in anti-clockwise direction. */

#include <stdio.h>


int circular_array_search(int *arr, int size, int target)
{
	int start = 0;
	int end = size - 1;
	int mid = 0;
	
	if (size == 0)
	{
		return -1;  /* return -1 if element wasnt found or if there is no array.. */
	}
	
	while (start <= end)
	{
		mid = start + (end - start) / 2;  /* every time divide by 2 - Binary search */
		
		if (arr[mid] == target)
		{
			return mid;
		}
		
		/* Check if the target element is present in the second half of the array */
		if (arr[mid] < arr[end])
		{
			if (target > arr[mid] && target <= arr[end])
			{
				start = mid + 1;
			}
			else
			{
				end = mid - 1;
			}
		}
		/* Otherwise, it must be present in the first half of the array */
		else
		{
			if (target >= arr[start] && target < arr[mid])
			{
				end = mid - 1;
			}
			else
			{
				start = mid + 1;
			}
		}
	}

	return -1;
}

int main()
{
	int arr1[6]= {7,8,11,1,4,5};
	
	int arr2[100] = {51, 52, 53, 54, 55, 56, 57, 58, 59, 60,
             61, 62, 63, 64, 65, 66, 67, 68, 69, 70,
             71, 72, 73, 74, 75, 76, 77, 78, 79, 80,
             81, 82, 83, 84, 85, 86, 87, 88, 89, 90,
             91, 92, 93, 94, 95, 96, 97, 98, 99, 100,
             1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
             11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
             21, 22, 23, 24, 25, 26, 27, 28, 29, 30,
             31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
             41, 42, 43, 44, 45, 46, 47, 48, 49, 50};
	
	int result = circular_array_search(arr1,6,11);
	
	printf("Element found at index %d\n",result);
	
	result = circular_array_search(arr2,100,47);
	
	printf("Element found at index %d\n",result);

	return 0;
}
