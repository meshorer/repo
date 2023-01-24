#include <stdio.h>
#include "bst.h"
#include "utilities.c"   



int compare(const void *data1, const void *data2)
{
    if (*(int *)data1 > *(int *)data2) 
    {
        return 1;
    }
    else
    {
        return -1;
    }
}


int main()
{
    bst_t *my_tree = NULL;
    int shalosh = 3;
    int arba = 4;
    int hamesh = 5;
    int shtaim = 2;

    my_tree = BstCreate(compare);
    if (NULL != my_tree){PRINT_TESTS(0);}else{PRINT_TESTS(1);}
    
    if (0 ==  BstInsert(my_tree,&shalosh)){PRINT_TESTS(0);}else{PRINT_TESTS(1);}
    if (0 ==  BstInsert(my_tree,&arba)){PRINT_TESTS(0);}else{PRINT_TESTS(1);}
    if (0 ==  BstInsert(my_tree,&hamesh)){PRINT_TESTS(0);}else{PRINT_TESTS(1);}
    if (0 ==  BstInsert(my_tree,&shtaim)){PRINT_TESTS(0);}else{PRINT_TESTS(1);}
    if (4 ==  BstSize(my_tree)){PRINT_TESTS(0);}else{PRINT_TESTS(1);}
    if ((void *)(&shalosh) == BstFind(my_tree,&shalosh)){PRINT_TESTS(0);}else{PRINT_TESTS(1);}
    if (3 ==  BstHeight(my_tree)){PRINT_TESTS(0);}else{PRINT_TESTS(1);}
    /*PrintTree(my_tree);*/
    /*printf("size is: %lu\n",BstSize(my_tree));*/
   
    

    printf("hight is :%lu\n",BstHeight(my_tree));

    PrintPostOrder(my_tree);
    printf("\n");
    BstDestroy(my_tree);

    CHECK_ERROR(count_error);
    return 0;
}

