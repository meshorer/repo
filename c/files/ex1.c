#include <stdio.h>




void Print_num(int num)
{
	printf("%d\n", num);
	
}

struct print_me {
	
	int num;
	void (*print)();
	};


int main ()
{
	int i;	
	
	struct print_me str[10];
	
	for (i = 0; i < 10; i++)
	{
	
		str[i].num = i;
		str[i].print = Print_num;
		str[i].print(i);
	}



	return 0;
}




