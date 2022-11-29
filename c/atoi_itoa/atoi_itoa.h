#ifndef __ATOI_ITOA_H__
#define __ATOI_ITOA_H__



#include <stdio.h>
#include <string.h>
#include <stdlib.h> /* for itoa    */
#include <limits.h> /* for int_max */


#define PRINT_TESTS(num) ( 0 == (num)) ? printf("\n") : printf("\033[0;31mFAIL in line %d \033[0m\n",__LINE__ )

void Reverse(char * str, int count);
void Itoa10(int num, char *str, int base);
int Atoi10(const char * str);



#endif





