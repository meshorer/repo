


/*	Change the value of x to 1337, by inserting code only in  AREA1.

	Same as 1., but do not use the letter x in the code you add. 
	
	Insert code only in AREA2, so that the output of the program will be exactly as follows: 
	x=1
	Enter func1
	Enter func2
	Exit func2
	Exit main */


#include <stdio.h>
void func2(void *arg) {
	long f2;
	printf("Enter func2\n");
 
    /* AREA2 */
    	
	/*try to find the return address of func 1 in main,
	and change the address of main to that */
	


	printf("Exit func2\n");
}

void func1() {
	long f1;
	printf("Enter func1\n");
	func2(&f1);
	printf("Exit func1\n");
}
 
int main() {
	const long x=1;
	long y=5;
 
    /* AREA1 */
    
	/* ----anser 1----------------------------------------------------*/
	
	/*long * ptr = (long *)&x;  */ /* option a - using ptr */
  	*ptr = 1337;
  	
  /*	y = (long)&x;			/* option b - y becomes a pointer */
  /*	*(long *)y = 1337;    */
 	
	/* ----anser 2----------------------------------------------------/*
	
 /*	long * ptr = &y+1;  */		/* option a - using ptr */
 /*	*ptr = 1337;*/
 	
 /*	y = (long)&y + 8;  	*/ 	 /* option b - y becomes a pointer */
 /*	*(long *)y = 1337;	*/
 	
	printf("x=%lu\n",x);
	func1();
 
	printf("Exit main\n");
	return 0;
}
