#include "comparison_sort.h"


int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}
   
int main()
{


	clock_t start = 0;
	clock_t end = 0;
	int i = 0;
	int arr[5000] = {0};
	srand(time(NULL));
	for (i = 0; i < 5000; i++)
	{
		arr[i] = rand()%5000;
	}
	

	printf("\n");
	start = clock();
	qsort(arr,5000,sizeof(int),cmpfunc);
	end = clock();

	printf("Time elapsed for qsort : %f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);

	printf("\n");
	
	printf("tests for bubble-sort! \n"); 
	printf("----------\n");
	for (i = 0; i < 5000; i++)
	{
		arr[i] = rand()%5000;
	}
	start = clock();
	Bubble(arr,5000);
	end = clock();
	printf("Time elapsed for bubble: %f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);
	
	printf("----------\n");
	printf("\n");
	
	printf("tests for selection-sort! \n"); 
	printf("\n");
	for (i = 0; i < 5000; i++)
	{
		arr[i] = rand()%5000;
	}
	
	/*for (i = 0; i < 5000; i++)
	{
		printf("%d ", arr[i]);
	}*/
	printf("----------\n");
	start = clock();
	Selection(arr,5000);
	end = clock();
	printf("Time elapsed for selection: %f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);
	/*printf("after func:\n");
	for (i = 0; i < 5000; i++)
	{
		printf("%d ", arr[i]);
	}*/
	printf("tests for Insertion-sort! \n"); 
	for (i = 0; i < 5000; i++)
	{
		arr[i] = rand()%5000;
	}
	
	printf("\n");
	start = clock();
	Insertion(arr,5000);
	end = clock();
	printf("Time elapsed for Insertion: %f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);



	printf("\n");
	return 0;
}
