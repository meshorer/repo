#include "string.h"


int main()
{
	
	/* declerations for StrCpy*/
	
	char src_cpy[5] = {'m','i','k','g'};
	char dest_cpy[5] = {'d','a','\0','\0'};
	char src1_cpy[5] = {'m','i','k','g'};
	char dest1_cpy[5] = {'d','a','\0','\0'};
	char src2_cpy[5] = {'m','i','k','g'};
	char dest2_cpy[5];
	char src3_cpy[5] = {'m','i','k','g'};
	char dest3_cpy[5];
	/*declerations for StrNcpy func*/
	char src_ncpy[5] = {'a','b','c','d','\0'};
	char dest_ncpy[5];
	size_t n_ncpy = 3; 
	char src1_ncpy[5] = {'a','b','c','d','\0'};
	char dest1_ncpy[5];
	size_t n1_ncpy = 3; 
	char src2_ncpy[5] = {'a','b','c','d','\0'};
	char dest2_ncpy[5] = {'m','o','s','h'};
	size_t n2_ncpy = 2;
	char src3_ncpy[5] = {'a','b','c','d','\0'};
	char dest3_ncpy[5] = {'m','o','s','h'};
	size_t n3_ncpy = 2;  
	/*declerations for StrCmp*/
	char arr_cmp[] = "ABC";
	char arr1_cmp[] = "ABCD";
	int res_cmp = 0;
	char arr2_cmp[] = "ABC";
	char arr3_cmp[] = "ABCD";
	int res1_cmp = 0;
	char arr4_cmp[] = "checking";
	char arr5_cmp[] = "checkind";
	int res2_cmp = 0;
	char arr6_cmp[] = "checking";
	char arr7_cmp[] = "checkind";
	int res3_cmp = 0;
	
	/*declerations for StrNcmp*/
	char arr1_ncmp[] = "ABC";
	char arr2_ncmp[] = "ABCD";
	size_t n_ncmp = 2;
	int res_ncmp = 0;
	
	/*declerations for StrCasecmp*/
	char arr1_strcase[7] = {'A','b','c','d','e','l'};
	char arr2_strcase[7] = {'A','B','E','D','e','l'};
	int res_strcase = 0;
	
	/*declerations for strchr*/
	const char ch[] = "danielmeshorer@gmail.com";
	const char chnull[] = {'d','a','n','i','\0'};
	int c = '\0';
	char *ptr;
	
	/*declerations for strdup*/
	char const str_dup[] = "hello";
	char *ptr_dup;
	int i_dup = 0;
	
	
	
	/*  test for StrCpy */
	printf("----------------------\n");
	printf("\n");
	printf("tests for strcpy func:\n");
	printf("1. copy to full array:\n");
	StrCpy(dest_cpy,src_cpy);
	strcpy(dest1_cpy,src1_cpy);
	printf("original func:\n");
	printf("src is:  ");
	puts (src1_cpy);
	printf("dest is: ");
	puts (dest1_cpy);
	printf("our func:\n");
	printf("src is:  ");
	puts (src_cpy);
	printf("dest is  ");
	puts (dest_cpy);
	printf("\n");
	printf("2. copy to blank array:\n");
	StrCpy(dest2_cpy,src2_cpy);
	strcpy(dest3_cpy,src3_cpy);
	printf("original func:\n");
	printf("src is:  ");
	puts (src2_cpy);
	printf("dest is: ");
	puts (dest2_cpy);
	printf("our func:\n");
	printf("src is:  ");
	puts (src3_cpy);
	printf("dest is  ");
	puts (dest3_cpy);
	printf("\n");
	printf("----------------------\n");
	
	/* tests for StrNcpy*/
	printf("tests for strncpy func:\n");
	printf("\n");
	printf("1. copy to blank array:\n");
	StrNcpy(dest_ncpy,src_ncpy,n_ncpy);
	strncpy(dest1_ncpy,src1_ncpy,n1_ncpy);
	printf("original func:\n");
	printf("  src is:  ");
	puts (src1_ncpy);
	printf("dest is  ");
	puts (dest1_ncpy);
	printf("our func:\n");
	printf("  src is:  ");
	puts (src_ncpy);
	printf("dest is  ");
	puts (dest_ncpy);
	printf("\n");
	printf("2. copy to full array:\n");
	StrNcpy(dest2_ncpy,src2_ncpy,n2_ncpy);
	strncpy(dest3_ncpy,src3_ncpy,n3_ncpy);
	printf("original func:\n");
	printf("  src is:  ");
	puts (src3_ncpy);
	printf("dest is  ");
	puts (dest3_ncpy);
	printf("our func:\n");
	printf("  src is:  ");
	puts (src2_ncpy);
	printf("dest is  ");
	puts (dest2_ncpy);
	printf("\n");
	printf("----------------------\n");
	printf("\n");
		
	/* tests for StrCmp*/
	printf("tests for strcmp func:\n");
	printf("\n");
	printf("1. compare not same length :\n");
	res_cmp = StrCmp(arr_cmp,arr1_cmp);
	res1_cmp = StrCmp(arr2_cmp,arr3_cmp);
	printf("original func:\n");
	printf("test for StrCmp: %d\n", res_cmp);
	printf("our func:\n");
	printf("test for StrCmp: %d\n", res1_cmp);
	printf("\n");
	printf("2. compare with same length :\n");
	res2_cmp = StrCmp(arr4_cmp,arr5_cmp);
	res3_cmp = StrCmp(arr6_cmp,arr7_cmp);
	printf("original func:\n");
	printf("test for StrCmp: %d\n", res2_cmp);
	printf("our func:\n");
	printf("test for StrCmp: %d\n", res3_cmp);
	printf("\n");
	printf("----------------------\n");
	printf("\n");
	
	/* tests for StrNcmp*/
	printf("tests for strncmp func:\n");
	printf("\n");
	printf("1. compare not same length :\n");
	/*res_ncmp = StrNcmp(arr_ncmp,arr1_ncmp,n_ncmp);*/
	/*res1_ncmp = StrNcmp(arr2_ncmp,arr3_ncmp,n1_ncmp);*/
	printf("original func:\n");
	printf("test for StrNcmp fun is : %d\n", res_ncmp);
	printf("\n");
	printf("----------------------\n");
	printf("\n");
	
	/* tests for StrCasecmp*/
	printf("tests for strcmp func:\n");
	printf("\n");
	res_strcase = StrCasecmp(arr1_strcase,arr2_strcase);
	printf("test for StrCasecmp: %d\n", res_strcase);
	if (res_strcase > 0)
	{
		printf("first string is bigger\n");
	}
	
	else if (res_strcase < 0)
	{
		printf("second string is bigger\n");
	}
	
	else
	{
		printf("strings are equal\n");
	}
	
	
	/* tests for strchr*/
	printf("the string is: ");
	puts (ch);
	ptr = strchr(ch,c);
	printf("origin function:\n");
	if (ptr == 0)
	{
		printf("NULL\n");
	}
	
	else
	{
	printf("the locale of the character %c is %s\n", c, ptr); 
	}
	ptr = strchr(chnull,c);
	if (ptr == 0)
	{
		printf("NULL\n");
	}
	
	else
	{
	printf("the locale of the character %c is %s\n", c, ptr); 
	}
	
	/* tests for strdup*/
	printf("----------------------\n");
	printf("\n");
	ptr_dup = StrDup(str_dup);
	while (*(ptr_dup+i_dup))
	{
		printf("%p", ptr_dup);	
	}
	
	return 0;	
}
