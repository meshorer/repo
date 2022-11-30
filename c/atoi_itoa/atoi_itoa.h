#ifndef __ATOI_ITOA_H__
#define __ATOI_ITOA_H__

#define IS_BIG_ENDIAN ((*(unsigned short int *)"\0\xff" < 0x0100) ? printf("This computer is Big Endian\n") : printf("This computer is little Endian\n"))



#include <stdio.h>
#include <string.h>
#include <stdlib.h> /* for itoa    */
#include <limits.h> /* for int_max */

#define PRINT_TESTS(num) ( 0 == (num)) ? printf("\r") : printf("\033[0;31mFAIL in line %d \033[0m\n",__LINE__ )


void Reverse(char * str, int count);
void Itoa10(int num, char *str, int base);
int Atoi10(const char * str, int base);
int Endian();
void AppearsTwo(char *str1, char * str2, char * str3, int len1, int len2, int len3);


#endif





