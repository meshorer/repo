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
    int shalosh = 3;
    int arba = 4;
    int hamesh = 5;

    my_tree = BstCreate(compare);
    if (NULL != my_tree){PRINT_TESTS(0);}else{PRINT_TESTS(1);}
    
    if (0 ==  BstInsert(my_tree,&shalosh)){PRINT_TESTS(0);}else{PRINT_TESTS(1);}
    if (0 ==  BstInsert(my_tree,&arba)){PRINT_TESTS(0);}else{PRINT_TESTS(1);}
    if (0 ==  BstInsert(my_tree,&hamesh)){PRINT_TESTS(0);}else{PRINT_TESTS(1);}

    PrintTree(my_tree);

    CHECK_ERROR(count_error);
    return 0;
}

