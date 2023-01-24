#ifndef __BST_H__ILRD__CR3_
#define __BST_H__ILRD__CR3_

#include <stddef.h> /* size_t */

typedef enum {IN_ORDER, PRE_ORDER, POST_ORDER} traversal_t;

typedef struct bst bst_t;

/* returns an integer indicating the result of the action
return value:
    0 - success
    1 - failure
*/
typedef int (*action_function_t)(void *data, void *parameter);

/*returns an integer indicating the result of the comparison, as follows:

        0 - if the data1 and data2 are equal;
        negative value - if data1 is less than data2;
        positive value - if data1 is greater than data2.
*/
typedef int (*compare_func_t)(const void *data1, const void *data2);


/* Create a managment struct for the binary search tree, receives a compare function to compare between elements */
bst_t *BstCreate(compare_func_t cmp_func);

/* Destroy the binary search tree */
void BstDestroy(bst_t *bst);

/* remove node in the binary search tree */
void BstRemove(bst_t *bst,void *data);


/* insert node in the binary search tree, 
return value:
    0 - success
    1 - failure
 */
int BstInsert(bst_t *bst, const void *data);

/* check the Height(depth) of the binary search tree */
size_t BstHeight(const bst_t *bst);

/* return the sum of nodes in the binary search tree */
size_t BstSize(const bst_t *bst);

/* check if the tree contains any node 
return value:
    0 - NotEmpty
    1 - Empty
*/
int BstIsEmpty(const bst_t *bst);

/* runs through the binary search tree to find the node that contain the received data and return a void *, NULL if does not exist */
void *BstFind(bst_t *bst, const void *data);

/* runs through the binary search tree using the given mode (pre / in / post order) and using action_func on each node, keeping certain data in parameter if needed, return :
0 - if action_func succeeded,
not 0 - if failed */
int BstForEach(bst_t *bst, traversal_t mode, action_function_t action_func, void *param);


#endif /*__BST_H__ILRD__CR3_*/