#include <stdlib.h>     /* malloc */
#include <assert.h>

#include "bst.h"

struct bst_node
{
	void *data;
	struct bst_node *right;
	struct bst_node *left;
};

struct bst
{
	struct bst_node *root;
	int (*compare_func_t)(const void*, const void*);
};


/* creates managment struct for the tree */
bst_t *BstCreate(compare_func_t cmp_func)
{
	bst_t *bst = malloc(sizeof(bst_t));                      /* הקצאת מקום למבנה הניהולי */
	if(NULL == bst)
	{
		return NULL; 
	}
	
	bst -> compare_func_t = cmp_func;                        /* יישום הפרמטרים למבנה הניהולי */
	bst -> root = NULL;
	
	return bst;
}


/* inserts data to new node */
static struct bst_node *InsertRecursive(compare_func_t cmp_func, struct bst_node *node, void *data)
{	
	int cmp_val = 0;
	struct bst_node *save_node = node;

	if(save_node == NULL)
	{
		save_node =  malloc(sizeof(struct bst_node));                             /* החדש nodeהקצאת מקום ל */
		if(NULL == save_node)                                                     /* בדיקה שמאלוק לא נכשל */
		{
			return NULL;
		}
		
		save_node -> data = (void*)data;                                          /* יישום המידע למבנה */          
		save_node -> right = NULL;                                                /* NULLאתחול הפוינטר ל */
		save_node -> left = NULL;                                                 /* NULLאתחול הפוינטר ל */ 
		
		return save_node;                           
	}

	cmp_val = cmp_func(data, node -> data);                                       /* שליחת המידע והמידע מתוך המבנה להשוואה */
	if(cmp_val == -1)                                                             /* אם יצא מינוס 1, נלך לפוינטר השמאלי */                                         
	{
		save_node = InsertRecursive(cmp_func, save_node -> left, data);	
		node -> left = save_node;                                                 /* החדש בפוינטר השמאלי של ההורה שלו nodeשמירת ה */
	}
	else
	{
		save_node = InsertRecursive(cmp_func, save_node -> right, data);          /* אם יצא פלוס 1, נלך לפוינטר הימני */
		node -> right = save_node;                                                /* החדש בפוינטר הימני של ההורה שלו nodeשמירת ה */
	}
	
	return node;
}

/* wrapper for insert */
int BstInsert(bst_t *bst, const void *data)
{
	assert(bst);
	assert(data);

	bst -> root = InsertRecursive(bst -> compare_func_t, bst -> root, (void*)data);  /* למבנה הניהולי rootיישום ה */

	if(NULL == bst -> root)                                                          /* insert בדיקה אם ניתן לבצע את */
	{
		return 1;
	}

	return 0; 
}

/* traverse tree inorder */
static int TraverseInOrder(struct bst_node *node, action_function_t action_func, void *param)
{
	int ret_val = 0;

	if(NULL == node)
	{
		return 0;
	}

	if(-1 == TraverseInOrder(node -> left, action_func, param))   /* שליחה לשמאל */
	{
		return -1;
	}
	
	ret_val = action_func(node -> data, param);                   /* שליחה לפונקצית פעולה ושמירת ערך החזרה שלה */
	if(1 == ret_val)                                              /* אם נכשלה אפילו פעם 1, נחזיר כישלון */
	{
		return -1;
	}

	if(-1 == TraverseInOrder(node -> right, action_func, param))  /* שליחה לימין */
	{
		return -1;
	}

	return 0;
}

/* traverse tree pre order */
static int TraversePreOrder(struct bst_node *node, action_function_t action, void *parameter)
{
	int ret_val = 0;

	if (NULL == node)
	{
		return 0;
	}

	ret_val = action(node -> data, parameter);                 /* שליחה לפונקצית פעולה ושמירת ערך החזרה שלה */
	if (ret_val)                                               /* אם נכשלה אפילו פעם 1, נחזיר כישלון */
	{
		return 1;
	}

	if (TraversePreOrder(node -> left, action, parameter))     /* שליחה לשמאל */
	{
		ret_val = 1;
	}

	if (TraversePreOrder(node -> right, action, parameter))    /* שליחה לימין */
	{
		ret_val = 1;
	}

	return ret_val;
}

/* traverse tree post order */
static int TraversePostOrder(struct bst_node *node, action_function_t action_func, void *param)
{	
	int ret_val = 0;

	if(NULL == node)
	{
		return 0;
	}

	if(TraversePostOrder(node -> left, action_func, param))             /* שליחה לשמאל */
	{
		ret_val = 1;
	}

	if(TraversePostOrder(node -> right, action_func, param))            /* שליחה לימין */
	{
		ret_val = 1;
	}
	
	if(ret_val)
	{
		return 1;
	}

	ret_val = action_func(node -> data, param);                        /* שליחה לפונקצית פעולה ושמירת ערך החזרה שלה */

	return ret_val;
}

/* runs through the tree using the given mode (pre/in/post) and uses action_func on each node */
int BstForEach(bst_t *bst, traversal_t mode, action_function_t action_func, void *param)
{
	int ret_val = -1;

	assert(bst);
	assert(action_func);

	if(mode == IN_ORDER)                                                                 
	{
		ret_val = TraverseInOrder(bst -> root, action_func, param);
	}
	else if(mode == PRE_ORDER)
	{
		ret_val = TraversePreOrder(bst -> root, action_func, param);
	}
	else if(mode == POST_ORDER)
	{
		ret_val = TraversePostOrder(bst -> root, action_func, param);
	}

	return ret_val;
}


/* checks if the tree is empty */
int BstIsEmpty(const bst_t *bst)
{
	assert(bst);

	if(NULL == bst -> root)
	{
		return 1;
	}

	return 0;
}


/* counts nodes in to parameter */
static int counter_func(void *data, void *parameter)
{
	++*(int*)parameter;
	(void)data;

	return 0;
}


/* checks size of tree */
size_t BstSize(const bst_t *bst)
{	
	size_t size = 0;

	assert(bst);

	TraverseInOrder(bst -> root, counter_func, &size);             /* traverse סופרת בעזרת פונקציה */

	return size;
}


/* desroys nodes */
static void DestoryWrapper(struct bst_node *node)
{
	if(NULL == node)
	{
		return;
	}

	DestoryWrapper(node -> left);
	DestoryWrapper(node -> right);
	free(node);
}

/* sends the tree to DestoryWrapper to destroy */
void BstDestroy(bst_t *bst)
{
	assert(bst);

	if(0 == BstIsEmpty(bst))
	{
		DestoryWrapper(bst -> root);
	}	

	free(bst);
}


/* finds the data in the tree and returns the data from inside the node */
static void *FindWrapper(struct bst_node *node, const void *data)
{
	 void *result = NULL;

	if(NULL == node)
	{
		return NULL;
	}

	if(data == node -> data)                                            /* עם התוכן שחיפשנו nodeלעצור כאשר נמצא ה */
	{
			return node -> data;
	}

	result = FindWrapper(node -> left, data);                           /* שליחת שמאל לחיפוש עד שנגיע לקצה או שנעצרנו בתנאים קודם */
	if(result != NULL)
	{
		return result;
	}

	result = FindWrapper(node -> right, data);                          /* שליחת ימין לחיפוש עד נשגיע לקצה או שנעצרנו בתנאים קודם*/
	if(result != NULL)
	{
		return result;
	}

	return NULL;
}

/* sends the tree and data to FindWrapper to search */
void *BstFind(bst_t *bst, const void *data)
{
	assert(bst);
	assert(data);

	return FindWrapper(bst -> root, data);
}


/* checks the height of the tree */
size_t HeightWrapper(struct bst_node *node)
{
	size_t left_height = 0;
	size_t right_height = 0;

	if (NULL == node)
	{
		return 0;
	}
	else 
	{
		left_height = HeightWrapper(node -> left);    /* שליחה לשמאל */
		right_height = HeightWrapper(node -> right);  /* שליחה לימין */
		
		if (left_height >= right_height)              /* בדיקה בקיפול אם שמאל גדול והוספה למשתנה ששומר את סה"כ והחזרה שלו אם הוא יותר גדול מימין */
		{
			return left_height + 1;
		}
		else
		{
			return right_height + 1;                  /* בדיקה בקיפול אם ימין גדול והוספה למשתנה ששומר את סה"כ והחזרה שלו אם הוא יותר גדול משמאל*/
		}
	}
}

/* sends tree to HeightWrapper */
size_t BstHeight(const bst_t *bst)
{
	return HeightWrapper(bst -> root);
}


/* traverses in the right subtree to leaf node and returns the node found */
struct bst_node *GetNode(struct bst_node *node)
{
	struct bst_node *curr = node;

	while(NULL != curr && curr -> right)                        /* הימני כדי להתקדם עד שנגיע לעלה nodeמעבר ל*/
	{
		curr = curr -> right;
	}

	return curr;
}

/* */
static struct bst_node* RemoveWrapper(struct bst_node *node, void *data, compare_func_t cmp_func)
{
	struct bst_node *tmp = NULL;
	int cmp_val = cmp_func(data, node -> data);                    /* להשוואה ושמירת התוצאה nodeשקיבלנו כשפרמטר וגם של ה dataשליחה ה */

	if(NULL == node)
	{
		return NULL;
	}

	if(-1 == cmp_val)                                              /* nodeהשמאלי, אם הערך שאנחנו מחפשים קטן מהערך ב subtreeמעבר ל */ 
	{
		node -> left = RemoveWrapper(node -> left, data, cmp_func);
	}
	else if(1 == cmp_val)                                          /* nodeהימני, אם הערך שאנחנו מחפשים גדול מהערך ב subtreeמעבר ל */
	{
		node -> right = RemoveWrapper(node -> right, data, cmp_func);
	}
	else
	{
		if(NULL == node -> left)                                   /* נעצור כשהגענו לפוינטר ריק משמאל */
		{
			tmp = node -> right;                                   /* נשמור את הפוינטר לילד הימני */
			free(node);                                            /* nodeנשחרר את ה */
			return tmp;                                            
		}
		else if(NULL == node -> right)                             /* נעצור כשהגענו לפוינטר ריק מימין */
		{
			tmp = node -> left;                                    /* נשמור אם הפוינטר לילד השמאלי */
			free(node);                                            /* nodeנשחרר את ה */                   
			return tmp;
		}

		tmp = GetNode(node -> left);                               /* השמאלי subtreeשמצאנו ב nodeנשמור את ה*/
		node -> data = tmp -> data;                                /* מהתוכן שמצאנו nodeניישם את התוכן ב*/
		node -> left = RemoveWrapper(node -> left, tmp -> data, cmp_func);   /* שנמצא nodeרצה על העץ בצד השמאלי ומוחקת את ה */
	}

	return node;
}

/* sends tree to RemoveWrapper */
void BstRemove(bst_t *bst, void *data)
{
	assert(bst);
	assert(data);

	bst -> root = RemoveWrapper(bst -> root, data, bst -> compare_func_t);       /* למבנה הניהולי rootיישום ה */
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
