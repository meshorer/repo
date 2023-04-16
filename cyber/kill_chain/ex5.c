/*	Compile it as follows: gcc -Wall -Wextra -g3 -m32 -no-pie
	Add lines in the marked spot to have only num is now 3 printed.
*/

#include <stdio.h>

void func(long a, long b) {

  // Insert lines here
   *(&a - 1) += 8;    /*  find the ebp in func and change it's value directly to the printf line
   you can use disas to find the offset between the line of num=4 (which is the return address) to the printf line     */
   return;
   
  printf("%ld\n", b);
  printf("%ld\n", a);
}

int main() {
  int num = 3;
  func(3, 1);
  num = 4;
  printf("num is now %d\n", num);

  return 0;
}
