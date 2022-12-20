#include <stdio.h>
#include "multiple_instances.h"


extern int x = 10;

void PrintGlobalVariablesAddress()
{
printf("the address: %p\n", &x);
}
