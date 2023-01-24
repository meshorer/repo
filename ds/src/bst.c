#include <stdlib.h>
#include <stdio.h>
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

struct bst_node *WrapperInsert(struct bst_node *node,compare_func_t compare,void *data);
void PrintTree(bst_t *my_tree);
void WrapperPrintTree(struct bst_node *node);



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
   
   bst->root = WrapperInsert(bst->root,bst->compare_func_t,(void *)data);

   return 0;
}

struct bst_node *WrapperInsert(struct bst_node *node,compare_func_t compare,void *data)
{
    int direction = 0;
    struct bst_node *saver = node;
    if (NULL == saver)
    {
        saver = malloc(sizeof(struct bst_node));
        if (NULL == saver)
        {
            return NULL;
        }
        saver->right = NULL;
        saver->left = NULL;
        saver->data = data;
        return saver;
    }
    direction = compare(data,saver->data);
    if (0 == direction)
    {
        saver = WrapperInsert(saver->right,compare,data);
        node->right = saver;
    }
    else
    {
        saver = WrapperInsert(saver->left,compare,data);
        node->left = saver;
    }
    return node;

}

void WrapperPrintTree(struct bst_node *node)
{

   printf("data: %d\n",*(int *)node->data);

   if (NULL != node->left)
   {
        WrapperPrintTree(node->left);
   }
   
    if (NULL != node->right)
   {
        WrapperPrintTree(node->right);
   }
}

void PrintTree(bst_t *my_tree)
{
    WrapperPrintTree(my_tree->root);
}