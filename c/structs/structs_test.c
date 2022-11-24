#include "structs.h"


int main()
{


	
	float num_float = 5.324;
	int num_int = 10;
	int i = 0;
	struct mixed_types str[3];
	str[0].element  =&num_int;
	str[0].add = &AddInt;
	str[0].print = &PrintInt;
	str[1].element  = &num_float;
	str[1].add = &AddFloat;
	str[1].print = &PrintFloat;
	str[2].element  = "whatsup";
	str[2].add = &AddString;
	str[2].print = &PrintString;



	for ( i; i < 3; i++)
	{
		str[i].print(str[i].element);
	}

	str[0].add(str[0].element, 10);
	str[0].print(str[0].element);	
	str[1].add(str[1].element, 10.453);
	str[1].print(str[1].element);	
	
	return 0;
}


/* *(float **)&x; */
