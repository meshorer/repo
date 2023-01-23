#include <stdlib.h>
#include "bst.h"


#define RIGHT 0
#define LEFT 1

struct bst_node
{
    void *data;
    struct bst_node *right;
    struct bst_node *left;
};

struct bst
{
    struct bst_node *root;
    int (*compare_func_t)(const void *data1, const void *data2);
};

int WrapperInsert(struct bst_node *node,compare_func_t compare,void *data);


/* Create binary search tree, receives a compare function to compare between elements */
bst_t *BstCreate(compare_func_t cmp_func)
{

    bst_t *managment = NULL;

    managment = malloc(sizeof(bst_t));
    if (NULL == managment)
    {
        return NULL;
    }

    managment->compare_func_t = cmp_func;
    managment->root = NULL;

    return managment;
}


int BstInsert(bst_t *bst, const void *data)
{
    /* call wraper func - with root:
        1. check stop conditoin - if compare funciton return the direction + that direction is NULL
        2. else - send the functiom the right/left 
    */
   
   int result = 0;
   result = WrapperInsert(bst->root,bst->compare_func_t,(void *)data);

   return result;
}

int WrapperInsert(struct bst_node *node,compare_func_t compare,void *data)
{
    int direction = 0;
    struct bst_node *new_node = NULL;
    
    
    if (NULL == node)
    {
        new_node = malloc(sizeof(struct bst_node));
        if (NULL == new_node)
        {
            return 1;
        }
        new_node->right = NULL;
        new_node->left = NULL;
        new_node->data = data;
        return 0;
    }
    direction = compare(data,node->data);
    if (0 == direction)
    {
        WrapperInsert(node->right,compare,data);
    }
    else
    {
        WrapperInsert(node->left,compare,data);
    }

    return 0;
}
