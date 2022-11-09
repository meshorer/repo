#include "string.h"


int main()
{
	
	/* declerations for StrCpy*/
	
	char src_cpy[5] = {'m','i','k','g'};
	char dest_cpy[5];
	/*declerations for StrNcpy func*/
	char src_ncpy[5] = {'a','b','c','d','\0'};
	char dest_ncpy[5];
	size_t n_ncpy = 3; 
	/*declerations for StrCmp*/
	char arr1_cmp[] = "ABC";
	char arr2_cmp[] = "ABCD";
	int res_cmp = 0;

	
	/*declerations for StrNcmp*/
	char arr1_ncmp[] = "ABC";
	char arr2_ncmp[] = "ABCD";
	size_t n_ncmp = 2;
	int res_ncmp = 0;
	
	
	/*  test for StrCpy */
	
	StrCpy(dest_cpy,src_cpy);
	printf("print the src - ");
	puts (src_cpy);
	printf("print the dest - ");
	puts (dest_cpy);
	
	/* tests for StrNcpy*/
	
	StrNcpy(dest_ncpy,src_ncpy,n_ncpy);
	puts (src_ncpy);
	puts (dest_ncpy);
	printf("%c\n ", *(dest_ncpy+2));
		
	/* tests for StrCmp*/
	res_cmp = StrCmp(arr1_cmp,arr2_cmp);
	printf("test for StrCmp: %d\n", res_cmp);

	
	/* tests for StrNcmp*/
	
	
	res_ncmp = StrNcmp(arr1_ncmp,arr2_ncmp,n_ncmp);
	printf("test for StrNcmp fun is : %d\n", res_ncmp);
	
	
	
	return 0;	
	
	
}
