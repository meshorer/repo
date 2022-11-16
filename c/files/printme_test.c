#include "printme.h"



int main ()
{
	int i;	
	
	struct print_me str[10];
	
	for (i = 0; i < 10; i++)
	{
	
		str[i].num = i;
		str[i].print = Print_num;
		str[i].print(str[i].num);
	}



	return 0;
}


