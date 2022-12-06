#include "structstest.h"

/* reviewed by MrArthur  */
int main()
{


	
	float num_float = 35.324;
	int num_int = 30;

	struct mixed_types str[3];
	char string[20] = "whatsup";
	char * ptr_str = (char *) malloc (strlen(string)+sizeof(int)*1);
	
	float *x = &num_float;
	
	strcpy(ptr_str, string);
	
	str[0].element =(int *)num_int;
	str[0].add = &AddInt;
	str[0].print = &PrintInt;
	str[0].clean = &Cleanup;	
	str[1].element  = x;
	str[1].add = &AddFloat;
	str[1].print = &PrintFloat;
	str[1].clean = &Cleanup;	
	str[2].element  = ptr_str;
	str[2].add = &AddString;
	str[2].print = &PrintString;
	str[2].clean = &Cleanup;	
	
	str[0].print(str);
	str[0].add(str,12);
	str[0].print(str);
	str[1].print(str);
	str[1].add(str,4);
	str[1].print(str);
	str[2].clean(str[2].element);
	/*printf("biggest number is %f\n", MAX2(*(int *) str[0].element,*(float *)str[1].element));*/
	
	return 0;
}


