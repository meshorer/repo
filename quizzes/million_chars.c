#include <stdio.h> /* for print */


void OneMillion(char chr)
{

	static int arr[256] = {0};
	int i = 0;
	int max = 0;
	
	while (0 != chr)
	{
		arr[chr]++;
	}

	for ( i = 0; i < 256; i++)
	{
		if (arr[i] > max)
		{
			max = arr[i];
		}
	}
	
	printf("the maximum number of ocuurrences of same char is: %d\n", max);

}

int main()
{

	char chr;
	printf("enter chars\n");
	scanf("%c",chr);
	/*scanf("%c",OneMillion); */
	OneMillion(chr);




	return 0;
}
