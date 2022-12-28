
#include "comparison_sort.h"


void Bubble(int *arr, size_t size)
{

	size_t i = 0;
	size_t j = 0;
	int tmp = 0;
	
	for (i = 0; i < size -1; i++)
	{
	
		for (j = 0; j < size -1; j++)
		{
			if (arr[j] > arr[j+1])
			{
				tmp = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = tmp;
			}
		}
	}
}


void Selection(int *arr, size_t size)
{

	int min = INT_MAX;
	size_t i = 0;
	size_t j = 0;
	int tmp = 0;
	int idx_min = 0;
	
	for (i = 0; i < size; i++)
	{
	
		for (j = i; j < size; j++)
		{
			if(arr[j] < min)
			{
				min = arr[j];
				idx_min = j;
			}
		
		} 

		tmp = arr[i];
		arr[i] = arr[idx_min];
		arr[idx_min] = tmp; 
		min = INT_MAX;

	
	}

}

void Insertion(int *arr, size_t size)
{
	size_t k = 0;
	size_t j = 0;
	int tmp = 0;
	
	for (j = 0; j < size -1; j++)
	{
		if (arr[j] > arr[j+1])
		{
			tmp = arr[j];
			arr[j] = arr[j+1];
			arr[j+1] = tmp;
			k = j;
			while (arr[k] < arr[k-1] && k > 0)
			{
				tmp = arr[k];
				arr[k] = arr[k-1];
				arr[k-1] = tmp;
				k--;
			}
		}	
	}	



}
