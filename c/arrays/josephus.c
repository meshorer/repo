#include <stdio.h>
#include <stdlib.h>


int main()

{
	
	int num = 5;
	int res;
	res = josephus(num);
	printf("%d\n", res);
	

}



int josephus(int num)
{
	
	int curr;
	int *arr = malloc(num * sizeof (int));
	int i;
	for (i = 0; i<num-1; i++)
	{
	
	arr[i] = i+1;
	}
	
	
	while (curr != arr[curr])
	{
		int next_alive = arr[curr];
		arr[curr] = arr[next_alive];
		curr = arr[curr];
	}
	
	free(arr);
	return curr;
	
}

