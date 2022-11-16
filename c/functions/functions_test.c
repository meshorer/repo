#include "functions.h"
typedef  void (*ptr_t)();

int main()
{

	int options = 0; 
	printf("helllo friend!\n");
	printf("if you want to use if -  press 1 \n");
	printf("if you want to use case -  press 2 \n");
	printf("if you want to use LUT -  press 3 \n");
	scanf("%d", &options);
	switch (options)
	{
		case 1:
			use_if();		
    			break;
   		case 2:
			use_case();	
			break;
		case 3:
			use_lut();	
			break;
		default:
			printf("you didnt enter match number");
	}
	


	return 0;
}
