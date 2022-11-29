#include <stdio.h>
#include <string.h>

#define PRINT_TESTS(num) ( 0 == (num)) ? printf("\n") : printf("\033[0;31mFAIL in line %d \n",__LINE__ )

void Reverse(char * str, int count);
void Itoa10(int num, char *str, int base);
int Atoi10(const char * str);
