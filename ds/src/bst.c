#include <stdlib.h>
#include <stdio.h>
#include "bst.h"
#include "assert.h"

#define RIGHT 0
#define LEFT 1
#define MAX(a,b) (((a) > (b)) ? (a) : (b))

 
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
size_t WrapperBstSize(struct bst_node *node);
void *WrapperBstFind(struct bst_node *node,compare_func_t compare,const void *data);
size_t WrapperBstHeight(struct bst_node *node);
void WrapperBstDestroy(struct bst_node *node);
int PostOrder(struct bst_node *node,action_function_t action_func, void *param); 
int InOrder(struct bst_node *node,action_function_t action_func, void *param);
int PreOrder(struct bst_node *node,action_function_t action_func, void *param);
struct bst_node *WrapperBstRemove(struct bst_node *node, compare_func_t cmp_func, void *data);
struct bst_node *BstFindRightmost(struct bst_node *node);
void SwapNode(struct bst_node **node1,struct bst_node **node2);
void WrapperMirorBSTree(struct bst_node *node);


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
   assert(bst);
   bst->root = WrapperInsert(bst->root,bst->compare_func_t,(void *)data);

   if(NULL == bst->root)
   {
        return 1;
   }

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
    if (0 < direction)
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


size_t BstSize(const bst_t *bst)
{
    size_t result = 0;
    assert(bst);
  
    result = WrapperBstSize(bst->root);
    return result;
}

size_t WrapperBstSize(struct bst_node *node)
{
    if (NULL == node)
   {
        return 0;
   }

    return 1+ WrapperBstSize(node->left) + WrapperBstSize(node->right);
}

int BstIsEmpty(const bst_t *bst)
{
    assert(bst);

    if (NULL != bst->root)
    {
        return 0;
    }
    return 1;
}

void *BstFind(bst_t *bst, const void *data)
{
    assert(bst);
    assert(data);
    return WrapperBstFind(bst->root,bst->compare_func_t,(void *)data);
}

void *WrapperBstFind(struct bst_node *node,compare_func_t compare,const void *data)
{
    int direction = 0;
    struct bst_node *saver = node;
    if (NULL == saver)
    {
        return NULL;
    }
    if (data == node->data)
    {
        return node->data; 
    }
    direction = compare(data,saver->data);
    if (0 < direction)
    {
        saver = WrapperBstFind(saver->right,compare,data);
        node->right = saver;
    }
    else
    { 
        saver = WrapperBstFind(saver->left,compare,data);
        node->left = saver;
    }
    return saver;
}

size_t BstHeight(const bst_t *bst)
{
    size_t result = 0;
    assert(bst);
    result = WrapperBstHeight(bst->root);
    return result;
}

size_t WrapperBstHeight(struct bst_node *node)

{
    size_t res1 = 0;
    size_t res2 = 0;

    if (NULL == node)
   {
        return 0;
   }

    res1 = WrapperBstHeight(node->left);
    res2 = WrapperBstHeight(node->right);
    return 1+ MAX(res1,res2);
}

void BstDestroy(bst_t *bst)
{
    assert(bst);

    if (BstIsEmpty(bst))
    {
        WrapperBstDestroy(bst->root);
    }
    WrapperBstDestroy(bst->root);
    free(bst);
}

void WrapperBstDestroy(struct bst_node *node)
{
    if (NULL != node)
    {
        WrapperBstDestroy(node->left);
        WrapperBstDestroy(node->right);

        free(node);
    }
}

int PostOrder(struct bst_node *node,action_function_t action_func, void *param)
{
   
    if (NULL == node)
    {
        return 0;
    }
    
    if (PostOrder (node->left,action_func,param)|| PostOrder (node->right,action_func,param) || PostOrder (node->left,action_func,param))
    {
        return 1;
    }
         
    return 0;
} 


int PreOrder(struct bst_node *node,action_function_t action_func, void *param)
{
    
    if (NULL == node)
    {
        return 0;
    }
    
    if (action_func(node->data,param) || PreOrder (node->left,action_func,param) || PreOrder (node->right,action_func,param))
    {
        return 1;
    }
         
    return 0;
}

int InOrder(struct bst_node *node,action_function_t action_func, void *param)
{
    
    if (NULL == node)
    {
        return 0;
    }
    
    if (InOrder (node->left,action_func,param)|| action_func(node->data,param)|| InOrder (node->right,action_func,param))
    {
        return 1;
    }
         
    return 0;
}

int BstForEach(bst_t *bst, traversal_t mode, action_function_t action_func, void *param)
{
    int result = 1;
    assert(bst);
    assert(action_func);

    switch (mode)
    {
    case IN_ORDER:
        result = InOrder(bst->root,action_func,param);
        break;
    
    case PRE_ORDER:
        result = PreOrder(bst->root,action_func,param);
        break;
    
    case POST_ORDER:
        result = PostOrder(bst->root,action_func,param);
        break;
    }

    return result;
}

void BstRemove(bst_t *bst,void *data)
{
    assert(bst);
    assert(data);
    bst->root = WrapperBstRemove(bst->root,bst->compare_func_t,data);
}

struct bst_node *WrapperBstRemove(struct bst_node *node, compare_func_t cmp_func, void *data)
{
    struct bst_node *right_child, *left_child, *rightmost;
    int cmp_result;
    if (node == NULL)
    {
        return NULL;
    }

    cmp_result = cmp_func(data, node->data);
    if (cmp_result < 0)
    {
        node->left = WrapperBstRemove(node->left, cmp_func, data);
    }
    else if (cmp_result > 0)
    {
        node->right = WrapperBstRemove(node->right, cmp_func, data);
    }
    else
    {
        if (node->left == NULL)
        {
            right_child = node->right;
            free(node);
            return right_child;
        }
        else if (node->right == NULL)
        {
            left_child = node->left;
            free(node);
            return left_child;
        }
            rightmost = BstFindRightmost(node->left);
            node->data = rightmost->data;
            node->left = WrapperBstRemove(node->left, cmp_func, rightmost->data);  
    }

    return node;
}
struct bst_node *BstFindRightmost(struct bst_node *node)
{
    if (node->right == NULL)
    {
        return node;
    }
    return BstFindRightmost(node->right);
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


void MirorBSTree(bst_t *bst)
{
    WrapperMirorBSTree(bst->root);
}


void WrapperMirorBSTree(struct bst_node *node)
{
    if (NULL == node)
    {
        return;
    }
    
    SwapNode(&node->left,&node->right);
    
    WrapperMirorBSTree(node->right);
    WrapperMirorBSTree(node->left);
}

void SwapNode(struct bst_node **node1,struct bst_node **node2)
{
    void *tmp = *node1;
    *node1 = *node2;
    *node2 = tmp;
}
