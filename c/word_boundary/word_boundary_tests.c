#include "word_boundary.h"

static char test[38] = "what is your proffesion of any at all";
static char test1[38] = "what is your proffesion of any at all";

int main()
{
	printf("original function\n");
	printf("-------------------\n");
	printf("%s\n", test1);
	Memset(test1 +1, '$', 20);
	printf("%s\n", test1);
	printf("\n");
	
	
	
	printf("our function\n");
	printf("-------------------\n");	
	printf("%s\n", test);
	Memset(test +1, '$', 20);
	printf("%s\n", test);

return 0;

}




