#include "structs.h"

/* reviewed by MrArthur  */
int main()
{


	
	float num_float = 35.324;
	int num_int = 30;
	int i = 0;

	struct mixed_types str[3];
	char string[20] = "whatsup";
	char * ptr_str = (char *) malloc (strlen(string)+sizeof(int)*1);
	
	strcpy(ptr_str, string);
	
	str[0].element  =&num_int;
	str[0].add = &AddInt;
	str[0].print = &PrintInt;
	str[0].clean = &Cleanup;	
	str[1].element  = &num_float;
	str[1].add = &AddFloat;
	str[1].print = &PrintFloat;
	str[1].clean = &Cleanup;	
	str[2].element  = ptr_str;
	str[2].add = &AddString;
	str[2].print = &PrintString;
	str[2].clean = &Cleanup;	
	
	
	
	for ( i = 0 ; i < 3; i++)
	{
		str[i].print(str[i].element);
	}

	for ( i = 0; i < 3; i++)
	{
		str[i].add(str[i].element,10);
		str[i].print(str[i].element);
	}	
	

	str[2].clean(str[2].element);
	
	printf("biggest number is %f\n", MAX2(*(int *) str[0].element,*(float *)str[1].element));
	
	return 0;
}


