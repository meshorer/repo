#include <stdio.h>

struct fix {
int  sell;
int  buy;
int  profit;
};

 struct fix test[8];



void bursa(int *arr, int len_arr)
{
	
	int i = 0;
	int j = 0;
	int profit = 0;
	int buy_max = 0;
	int sell_max = 0;
	for (i = 0; i < len_arr; i++)
	{
		test[i].buy = arr[i];
		test[i].sell = arr[i+1];
		test[i].profit = test[i].sell -test[i].buy;			
		
		for ( j = 0; j < i-1; j++)
		{
			if ( arr[i] > test[j].sell)
			{
				test[j].sell = arr[i];
				test[j].profit = test[j].sell - test[j].buy;				
			}
		
			if (profit < test[j].profit)
			{
				profit = test[j].profit;
				buy_max = j;
				sell_max = i;
			}
		
		}
	}

	printf("biggest profit is %d\n", profit);
	printf("buy index is %d\n", buy_max);
	printf("sell index is %d\n", sell_max);
} 





int main()
{

int arr[8] = {6,12,3,5,1,4,9,2};

bursa(arr, 8);





	return 0;
}



