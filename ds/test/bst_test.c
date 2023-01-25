#include <stdio.h>
#include <assert.h>
#include "bst.h"
#include "utilities.c"   


void PrintPreOrder(const bst_t *bst);
void PrintInOrder(const bst_t *bst);


int compare(const void *data1, const void *data2)
{
    if (*(int *)data1 > *(int *)data2) 
    {
        return 1;
    }
    if (*(int *)data1 < *(int *)data2)
    {
        return -1;
    } 

    return 0;
}


int PrintAction(void *data, void *parameter)
{
    assert(parameter);
   
    printf(" %d ",(*(int*)data));

    return 0;
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
    printf("%d \n",BstIsEmpty(my_tree));
    if (0 ==  BstInsert(my_tree,&shalosh)){PRINT_TESTS(0);}else{PRINT_TESTS(1);}
    if (0 ==  BstInsert(my_tree,&arba)){PRINT_TESTS(0);}else{PRINT_TESTS(1);}
    if (0 ==  BstInsert(my_tree,&hamesh)){PRINT_TESTS(0);}else{PRINT_TESTS(1);}
    if (0 ==  BstInsert(my_tree,&shtaim)){PRINT_TESTS(0);}else{PRINT_TESTS(1);}
    if (4 ==  BstSize(my_tree)){PRINT_TESTS(0);}else{PRINT_TESTS(1);}
    if ((void *)(&shalosh) == BstFind(my_tree,&shalosh)){PRINT_TESTS(0);}else{PRINT_TESTS(1);}
    if (3 ==  BstHeight(my_tree)){PRINT_TESTS(0);}else{PRINT_TESTS(1);}
    /*PrintTree(my_tree);*/
    
    if (0 ==  BstForEach(my_tree, IN_ORDER, PrintAction, &shalosh)){PRINT_TESTS(0);}else{PRINT_TESTS(1);}
    BstRemove(my_tree,&arba);
    if (3 ==  BstSize(my_tree)){PRINT_TESTS(0);}else{PRINT_TESTS(1);}
    printf("\n");
    printf("%d \n",BstIsEmpty(my_tree));
    BstDestroy(my_tree);
    CHECK_ERROR(count_error);
    return 0;
}

