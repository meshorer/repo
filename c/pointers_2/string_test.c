#include "string.h"


int main()
{

	/* declerations for StrLen*/
	char arr_len[] = {"programer"};
	size_t result_len; 
	size_t result_len1;
	
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
	size_t n_ncmp = 1;
	int res_ncmp = 0;
	int res1_ncmp = 0;
	/*declerations for StrCasecmp*/
	char arr1_strcase[7] = {'A','b','c','d','e','l'};
	char arr2_strcase[7] = {'A','B','E','D','e','l'};
	int res_strcase = 0;
	int res_strcase1 = 0;
	
	/*declerations for strchr*/
	const char ch_chr[] = "danielmeshorer@gmail.com";
	int c = '@';
	char *ptr_chr;
	char *ptr_chr1;
	
	/*declerations for strdup*/
	extern char* strdup(const char*);
	char const str_dup[] = "what is up";
	char const str_dup1[] = "what is up";
	char *ptr_dup;
	char *ptr_dup1;
	
	/*declerations for strcat*/
	char ch1[100] = "you ma";
	char ch2[] = "de it!";
	char ch3[100] = "you ma";
	char ch4[] = "de it!";
	
	/*declerations for strcat*/
	char ch1_ncat[100] = "you ma";
	char ch2_ncat[] = "de it!";
	size_t stop = 5;
	char ch3_ncat[100] = "you ma";
 	char ch4_ncat[] = "de it!";
 	
 	
 	/*declerations for strstr*/
 	
 	char haystack_1[] = "he asked what is your proffesion?";
	char needle_1[] = "what is your proffesion?";
	char *ptr_haystack_1;
	char haystack_2[] = "he asked what is your proffesion?";
	char needle_2[] = "what is your proffesion?";
	char *ptr_haystack_2;
	
 	/*  test for strlen */
 	printf("----------------------\n");
	printf("\n");
	printf("tests for strlen func:\n");
	printf("original func:\n");
	result_len1 = strlen (arr_len);
	printf("%lu \n", result_len1);
	printf("our func:\n");
 	result_len = StrLen (arr_len);
	printf("%lu \n", result_len);
 	
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
	res_ncmp = StrNcmp(arr1_ncmp,arr2_ncmp,n_ncmp);
	res1_ncmp = strncmp(arr1_ncmp,arr2_ncmp,n_ncmp);
	printf("original func:\n");
	printf("result is : %d\n", res1_ncmp);
	printf("\n");
	printf("our func:\n");
	printf("result is : %d\n", res_ncmp);
	printf("\n");
	printf("----------------------\n");
	printf("\n");
	
	/* tests for StrCasecmp*/
	printf("tests for strcasecmp func:\n");
	printf("\n");
	res_strcase = StrCasecmp(arr1_strcase,arr2_strcase);
	res_strcase1 = strcasecmp(arr1_strcase,arr2_strcase);
	printf("test for StrCasecmp:\n");
	printf("original func\n");
	printf("result: %d\n", res_strcase1);
	if (res_strcase1 > 0)
	{
		printf("first string is bigger\n");
	}
	
	else if (res_strcase1 < 0)
	{
		printf("second string is bigger\n");
	}
	
	else
	{
		printf("strings are equal\n");
	}
	printf("our func\n");
	printf("result: %d\n", res_strcase1);
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
	printf("\n");
	printf("----------------------\n");
	printf("\n");
	
	/* tests for strchr*/
	printf("\n");
	printf("----------------------\n");
	printf("\n");
	printf("tests for strchr func:\n");
	printf("\n");
	printf("the string is: ");
	puts (ch_chr);
	ptr_chr= strchr(ch_chr,c);
	ptr_chr1 = StrChr(ch_chr,c);
	printf("origin function:\n");
	if (ptr_chr == 0)
	{
		printf("NULL\n");
	}
	
	else
	{
	printf("the locale of the character %c is %s\n", c, ptr_chr); 
	}
	printf("our func:\n");
	if (ptr_chr1 == 0)
	{
		printf("NULL\n");
	}
	
	else
	{
	printf("the locale of the character %c is %s\n", c, ptr_chr1); 
	
	/* tests for strdup*/
	printf("\n");
	printf("----------------------\n");
	printf("\n");
	printf("tests for strdup:\n");
	printf("\n");
	printf("original func:\n");
	ptr_dup1 =  (char *) strdup(str_dup1);
	printf("%s\n", ptr_dup1);
	printf("our func:\n");
	ptr_dup =  (char *) StrDup(str_dup);
	printf("%s\n", ptr_dup);
	free(ptr_dup);
	free(ptr_dup1);
	
	/* tests for strcat*/
	printf("\n");
	printf("----------------------\n");
	printf("\n");
	printf("tests for strcat:\n");
	printf("\n");
	printf("original func:\n");
	StrCat(ch3,ch4);
	printf("result is: ");
	puts(ch3);
	printf("our func:\n");
	strcat(ch1,ch2);
	printf("result is: ");
	puts (ch1);
	printf("\n");
	printf("----------------------\n");
	printf("\n");

	/* tests for strncat*/
	printf("\n");
	printf("----------------------\n");
	printf("\n");
	printf("tests for strncat:\n");
	printf("\n");
	printf("original func:\n");
	strncat(ch3_ncat,ch4_ncat,stop);
	printf("result is: ");
	puts(ch3_ncat);
	printf("our func:\n");
	StrNcat(ch1_ncat,ch2_ncat,stop);
	printf("result is: ");
	puts(ch1_ncat);
	printf("\n");
	printf("----------------------\n");
	printf("\n");
	
	/* tests for strstr*/
	printf("\n");
	printf("----------------------\n");
	printf("\n");
	printf("tests for strstr:\n");
	printf("\n");
	ptr_haystack_1 = (char *) strstr(haystack_1,needle_1);
	ptr_haystack_2 = (char *) StrStr(haystack_2,needle_2);
	printf("original func:\n");
	
	if (!ptr_haystack_1)
	{
		printf("null");
	}
	
	else
	{
		
		printf("the result is  %s\n", ptr_haystack_1); 
	}
	
	printf("our func:\n");

	
	if (!ptr_haystack_2)
	{
		printf("null");
	}
	
	else
	{
		
		printf("the result is  %s\n", ptr_haystack_2); 
	}
	

}
	return 0;	
}
