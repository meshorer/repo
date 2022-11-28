#include "word_boundary.h"

static char test_memset[38] = "what is your proffesion of any at all";
static char test1_memset[38] = "what is your proffesion of any at all";

static char dest_memcpy[40] = "daniel is your proffesion of any at all";
static char src_memcpy[40] = "what proffesion of any at all";

static char dest1_memcpy[40] = "daniel is your proffesion of any at all";
static char src1_memcpy[40] = "what proffesion of any at all";

static char dest_memmove[40] = "daniel is your proffesion of any at all";
static char src_memmove[40] = "what proffesion of any at all";

static char dest1_memmove[40] = "daniel is your proffesion of any at all";
static char src1_memmove[40] = "what proffesion of any at all";

char target[21] = "a shiny white sphere";
char * p = target + 8;  
char * source = target + 2;

int main()
{
	/* tests for memset    */
	printf("test for memset\n");
	printf("-------------------\n");
	printf("original function\n");
	printf("%s\n", test1_memset);
	memset(test1_memset +1, '$', 20);
	printf("%s\n", test1_memset);
	printf("\n");
	printf("our function\n");
	printf("%s\n", test_memset);
	Memset(test_memset +1, '$', 20);
	printf("%s\n", test_memset);
	printf("\n");
	printf("-------------------\n");	
	
	/* tests for memcpy    */
	
	printf("test for memcpy\n");
	printf("-------------------\n");	
	printf("original function\n");
	memcpy(dest1_memcpy ,src1_memcpy, 9);
	printf("%s\n", dest1_memcpy);
	printf("\n");
	printf("our function\n");
	Memcpy(dest_memcpy,src_memcpy, 9);
	printf("%s\n", dest_memcpy);
	printf("\n");
	printf("-------------------\n");
	
	/* tests for memmove    */
	printf("test for memmove\n");
	printf("-------------------\n");	
	printf("original function\n");
	memmove(dest1_memmove,src1_memmove, 10);
	printf("%s\n", dest1_memmove);
	printf("\n");
	printf("our function\n");
	Memmove(dest_memmove,src_memmove, 10);
	printf("%s\n", dest_memmove);
	printf("\n");
	Memmove(p,source, 5);
	printf("%s\n", target);
return 0;

}




