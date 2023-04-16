/*
	Compile it with gcc -Wall -Wextra -g3 -no-pie.
	Add lines in the marked spot to run the finish function,
	without calling any functions.
*/


#include <stdio.h>

void finish(int a, int b) {
  if (42 == a) {
    printf("That's an interesting value for a.\n");
  }
  if (0 == b) {
    printf("How mundane.\n");
  }
  if (32767 == a * b) {
    printf("Keep in mind that neither success not failure is ever final.\n");
  }
  if (8001 == a * b || 9001 == a * b) {
    printf("Realize that while the first 90 percent of code accounts for 90 "
           "percent of the development time, so does the last 10 percent of "
           "the code.");
  }

  printf("You've successfully finished this part of the exercise.\n");
}

void func() {
	long a = 9999;
	*(&a +3) -= 238;
	
}

int main() {
  func();

  return 0;
}
