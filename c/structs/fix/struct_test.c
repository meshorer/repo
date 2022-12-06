#include "struct.h"

/* reviewed by MrArthur  */
int main()
{


	
	struct mixed_types str[3];
	 int i = 0;
	 
	str[0] = InitInt(5);
	str[1] = InitFloat(7.5);
	str[2] = InitString("whatsup");
	
	for (i = 0; i < 3; i++)
	{
		str[i].print(str[i].element);	
	}
	
	for (i = 0; i < 3; i++)
	{
		str[i].add(&str[i].element,10);	
	}
	
	for (i = 0; i < 3; i++)
	{
		str[i].print(str[i].element);
	}
	
	for (i = 0; i < 3; i++)
	{
		str[i].clean(str[i].element);
	}
	/*printf("biggest number is %f\n", MAX2(*(int *) str[0].element,*(float *)str[1].element));*/
	
	return 0;
}


