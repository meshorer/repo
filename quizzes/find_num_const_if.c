#include<stdio.h>


/*Find num in array with const number of if

Given an array of ints and a number, find if the number is in the array.

The number of "if"s used in the function should be const (pre-determined, does not depend on the size of array)*/

int FindNumConstIf(int *arr,int num, size_t size)
{

	size_t i = 0;
	int flag = 0;
	
	for (i = 0; i < size ; i++)
	{
		flag += !(arr[i] ^ num); /* if there is a match, flag will increment, anf if no match flag will remain 0  */
	}
	
	return flag > 0;
}

int main()
{
	int arr[] = {15,32,1,2,3,17};	
	
	printf("is num found? %d\n", FindNumConstIf(arr,15,5));
	printf("is num found? %d\n", FindNumConstIf(arr,5,32));
	
	return 0;
}

