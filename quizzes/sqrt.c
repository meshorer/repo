
/*Write Sqrt() function that takes a single argument (in double) and returns the square root of it (also in double). */

#include<stdio.h>

double Sqrt(double number)
{

	double root = number / 2;  /* Initialize the root to the half of the number*/
	double prev_root = 0;  /* Initialize the previous root to 0 */
	  
	/* Iterate until the root does not change*/
	while (root != prev_root)
	{
		prev_root = root;  /* Update the previous root */
		root = (number / prev_root + prev_root) / 2;  /* Calculate the new root */
	}
	  
	return root;
}



int main()
{
	printf("the square root of 9 is: %f\n", Sqrt(9));
	printf("the square root of 4.5 is: %f\n", Sqrt(4.5));
	printf("the square root of 100.28 is: %f\n", Sqrt(100.28));
	
	return 0;
}

