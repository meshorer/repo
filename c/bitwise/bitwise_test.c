#include "bitwise.h"



int main()
{
	/* declerations for ex1   */
	int res_ex1;
	
	/* declerations for ex2   */
	int res_ex2;
	int res_ex2_loop;
	
	/* declerations for ex3   */
	int res_ex3;
	
	/* declerations for ex4   */
	unsigned int arr_ex4[3] = {50,187,20};
	unsigned int arr_ex4b[5] = {50,187,20, 81, 97};
	
	/* declerations for ex6   */
	
	unsigned char res_ex6a;
	unsigned char res_ex6b;
	unsigned char res_ex6c;
	
	/* declerations for ex7   */
	
	unsigned int res_ex7;	
		
		
	/* declerations for ex8   */
	 int num1_ex8;
	 int num2_ex8;	
	 
	 /* declerations for ex10   */
	 float ex10;
	 int *ptr_ex10;

	
	/* test for ex1   */
	res_ex1 = Pow2(2,3);
	printf("test for ex1 is : %d\n", res_ex1);

	/* test for ex2   */
	res_ex2 = Is_pow2(0);
	printf("test for ex2 is :%d\n", res_ex2);

	/* test for ex2_loop   */
	res_ex2_loop = Is_pow2_loop(4);
	printf("test for ex2_loop is :%d\n", res_ex2_loop);
	
	/* test for ex3   */
	res_ex3 = Add1(157);
	printf("test for ex3 is :%d\n", res_ex3);
	
	/* test for ex4   */
	ThreeOn(arr_ex4, 3);
	ThreeOn(arr_ex4b, 5);
	
	/* test for ex5   */
	ByteMirror(3);
	ByteMirrorLoop(3);	


	/* test for ex6   */
	res_ex6a = Ex6a(79);
	res_ex6b = Ex6b(77);
	res_ex6c = Ex6c(135);		
	printf("test for ex6a is :%d\n", res_ex6a);
	printf("test for ex6b is :%d\n", res_ex6b);
	printf("test for ex6c is :%d\n", res_ex6c);	
	
	
	/* test for ex7   */
	res_ex7 = DividedSixteen(50);
	printf("test for ex7 is :%d\n", res_ex7);	
	
	
	/* test for ex8   */	
	num1_ex8 = -10;
	num2_ex8 = 15;	
	Swap(&num1_ex8, &num2_ex8);
	printf("test for ex8 is : %d, %d \n", num1_ex8,num2_ex8);
	
	/* test for ex9   */	
	CountBitsLoop(-141);
	CountBits(-134326);
	
	
	/* test for ex10 */  	/*  verify */
		
	ex10 = 3.1254; 
	ptr_ex10 = (int *) & ex10;
	printf("test for ex10 : \n");
	
 	 Bynary(*ptr_ex10);
	 printf("\n");
	 
	 
	return 0;

}

