#include "functions.h"

typedef void (*ptr_t)();

void use_case()
{

	char ch = 0;
	printf("welcome to case option\n");
	printf("to go back to main press -\n");
	printf("enter latters\n");
	while (27 != ch)
	{
		/*ch = getchar();*/
		scanf("%c", &ch);
		switch (ch)
		{
			case 'T':
			printf("T-pressed\n");		
    			break;
   			case 'A':
			printf("A-pressed\n");	
			break;
			case '-':
			main();	
			break;
		}
	}

	exit(0);
}


void empty()
{


}

void Print_a()
{
	printf("A-pressed\n");
}

void Print_t()
{
	printf("T-pressed\n");
}


void use_if()
{

	char ch = 0;
	printf("welcome to if option\n");
	printf("enter latters\n");
	while (27 != ch)
	{
		/*ch = getchar();*/
		scanf("%c", &ch);
		
		if (84 == ch)
		{
			printf("T-pressed\n");		
		}
		
		if (65 == ch)
		{
			printf("A-pressed\n");	
		}	
	}

	exit(0);
	
}


void use_lut()
{

	char ch = 0;
	int k;
	ptr_t arr[256];
	k = 0;
	while (k < 256)
	{
		arr[k] = empty;
		k++;
	}	

	arr[65] = Print_a;
	arr[84] = Print_t;
	printf("what key do yo want to press?\n");
	while (27 != ch)
	{
		scanf("%c", &ch);
		 arr[(int) ch]();
	}

}
    
