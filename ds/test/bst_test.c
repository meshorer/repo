#include <stdio.h>
#include "bst.h"
#include "utilities.c"   



int compare(const void *data1, const void *data2)
{
    if (*(int *)data1 > *(int *)data2) 
    {
        return 0;
    }
    else
    {
        return 1;
    }
}


int main()
{
    bst_t *my_tree = NULL;

    my_tree = BstCreate(compare);
    if (NULL != my_tree){PRINT_TESTS(0);}else{PRINT_TESTS(1);}
    
    if (0 ==  BstInsert(my_tree,(void *)3)){PRINT_TESTS(0);}else{PRINT_TESTS(1);}

    CHECK_ERROR(count_error);
    return 0;
}

