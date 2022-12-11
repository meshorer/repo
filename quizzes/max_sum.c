#include <stdio.h>
 
void maxSubArray(int *arr, int size, int *result)
 {
   
   int max_sum = 0;
   int tmp_sum = 0;
   int start_index = 0;
   int end_index = 0;
   int i = 0;

    for ( i = 0; i < size; i++) 
    {
	tmp_sum += arr[i];
        if (tmp_sum > max_sum)
        {
        	max_sum = tmp_sum;
        	end_index = i;
        }
        if (tmp_sum < 0)
        {
        	tmp_sum = 0;
        	start_index = i + 1;
        }
    }

	result[0] = max_sum;
	result[1] = start_index;
	result[2] = end_index;
}

int main() 
{

	int arr[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};

    
	int result[3];

   
	maxSubArray(arr, sizeof(arr)/sizeof(int), result);

	printf("Maximum sub-array sum: %d\n", result[0]);
	printf("Start index: %d\n", result[1]);
	printf("End index: %d\n", result[2]);

    return 0;
}

