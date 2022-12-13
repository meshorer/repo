
#include "slist.h"


#include <stdlib.h>  /* for malloc, realloc */
#include <assert.h>  /* for asserts */




struct s_list_node
{
	void *data;
	struct s_list_node *next;
};

struct s_list
{
	struct s_list_node *head;
	struct s_list_node *next;
};

/***********************************/

/*------------------------------------
	Name: SListCreate
	Date: Dec 13
	Description: create list and insert dummy node to it 
	Status: done
	Reviewer : 
------------------------------------*/

s_list_t *SListCreate()
{
	struct s_list *new = (struct s_list *)malloc(sizeof(struct s_list));
	struct s_list_node *dummy_node = (struct s_list_node *)malloc(sizeof(struct s_list_node));
	
	dummy_node->data = NULL;
	dummy_node->next = NULL;
	
	new->head = dummy_node;
	
	return new;
	
}

/************************************/
/*------------------------------------
	Name: SListBegin
	Date: Dec 13
	Description: returns iterator of the beggining of the SList 
	Status: done
	Reviewer : 
------------------------------------*/

s_list_iterator_t SListBegin(const s_list_t *s_list)
{
	assert(NULL != s_list);
	
	return s_list->head;

}
/************************************/

/*------------------------------------
	Name: SListNext
	Date: Dec 13
	Description: returns iterator to next node
	Status: done
	Reviewer : 
------------------------------------*/

s_list_iterator_t SListNext(const s_list_iterator_t iter)
{
	assert(NULL != iter);
	return iter->next; 	
} 

/************************************/

/*------------------------------------
	Name: SListEnd
	Date: Dec 13
	Description: returns iterator to last node
	Status: done
	Reviewer : 
------------------------------------*/

s_list_iterator_t SListEnd(const s_list_t *s_list)
{

	s_list_iterator_t iter = s_list->head;
	assert(NULL != s_list);
	
	
	while (iter->next != NULL)
	{
		iter = iter->next;	
	}
	
	return iter;
}
/************************************/

/*------------------------------------
	Name: SListSet
	Date: Dec 13
	Description: Update Data in SList in iterator position
	Status: done
	Reviewer : 
------------------------------------*/

void SListSet(s_list_t *s_list, s_list_iterator_t iter, const void *data)
{

	assert(NULL != s_list);
	assert(NULL != iter);
	
	
	/*
	while (0 != IterCmp(s_list->next,iter) && (NULL != s_list->next))
	{
		s_list->next = SListNext(s_list->next);
	}
	
	iter->data = (void *)data; */
	
	iter->data = (void *)data;
	
}



/************************************/

/*------------------------------------
	Name: SListGet
	Date: Dec 13
	Description: Return Data from SList in iterator
	Status: done
	Reviewer : 
------------------------------------*/


void *SListGet(s_list_t *s_list, s_list_iterator_t iter)
{

	s_list_iterator_t head_iter = s_list->head;

	assert(NULL != iter);
	assert(NULL != s_list);
	
	
	while (0 != IterCmp(head_iter,iter) && (NULL != head_iter))
	{
		head_iter = head_iter->next;
	} 
	
	return iter->data;
}

/************************************/

/*------------------------------------
	Name: SListSize
	Date: Dec 13
	Description: To Get Size Of SList
	Status: done
	Reviewer : 
------------------------------------*/

size_t SListSize(const s_list_t *s_list)
{
	size_t count = 0;
	
	s_list_iterator_t head_iter = s_list->head;
	assert(NULL != s_list);
	
	
	
	while (head_iter->next != NULL)
	{
		count++;
		head_iter = head_iter->next;	
	}
	
	return count;
}



/************************************/

/*------------------------------------
	Name: SListDestroy
	Date: Dec 13
	Description: free all
	Status: done
	Reviewer : 
------------------------------------*/


void SListDestroy(s_list_t *s_list)
{

	s_list_iterator_t tmp = NULL;
	s_list_iterator_t iter = s_list->head;
	
	assert(NULL != s_list);
	
	while (iter->next != NULL)
	{
		tmp = iter;
		iter = iter->next;
		free(tmp);
	}
	free(iter);
	free(s_list);
	


	/*
	s_list_iterator_t tmp = s_list->head;
	while (SListSize(s_list) > 0)
	{
		s_list_iterator_t iter = SListEnd(s_list);
		
		free(iter);
	}
	
	free(s_list);  */
}

/************************************/

int IterCmp(s_list_iterator_t iter1, s_list_iterator_t iter2)
{
	return iter1 - iter2;
}


/************************************/

/*------------------------------------
	Name: SListAdd
	Date: Dec 13
	Description: To Add To The SList Data according to iterator position return the iterator pointing to the added node
	Status: done
	Reviewer : 
------------------------------------*/

s_list_iterator_t SListAdd(s_list_t *s_list, s_list_iterator_t position, const void *data)
{

	struct s_list_node *new_node = malloc(sizeof(struct s_list_node));
	
	assert(NULL != s_list);
	assert(NULL != position);
	
	/*s_list_iterator_t head_iter = s_list->head; */
	
	/*
	while (0 != IterCmp(head_iter,position) && (NULL != head_iter))
	{
		head_iter = head_iter->next;
	} 
	
	*/
	
	new_node->data = position->data;
	new_node->next = position->next;
	
	position->data = (void *)data;
	position->next = new_node;
	

	
	return position;
} 

/************************************/


/*------------------------------------
	Name: SListRemove
	Date: Dec 13
	Description: Function to Delete Certain Node from SList using iterator linking the nodes before and after, return the iterator to the next node
	Reviewer : 
------------------------------------*/

s_list_iterator_t SListRemove(s_list_t *s_list, s_list_iterator_t iter)
{

	s_list_iterator_t saved_iter_next = iter->next;
	
	assert(NULL != s_list);
	assert(NULL != iter);
	
	iter->data = (iter->next)->data;
	iter->next = (iter->next)->next;
	
	free(saved_iter_next);

	
	return iter;
}


/************************************/

/*------------------------------------
	Name: SListFind
	Date: Dec 13
	Description: runs through the SList in certain range including the front edge without end edge matching parameter to each node in the range using match_function, return the iterator to the matching node if found, NULL if wasnt found
	Reviewer : 
------------------------------------*/

s_list_iterator_t SListFind(s_list_iterator_t iter_from, s_list_iterator_t iter_to, match_function_t match_func, void *parameter)
{

	assert(NULL != iter_from);
	
	while (iter_from != iter_to && NULL != iter_from->next)
	{
		if (match_func(iter_from ->data, parameter) == 0)
		{
			return iter_from;
		}
		
		iter_from = iter_from->next;
	}
	
	return iter_from;
}

/************************************/
   



/*------------------------------------
	Name: SListForEach
	Date: Dec 13
	Description: runs through the SList in certain range including the front edge without end edge using action_func on each node, keeping certain data in parameter if needed, return 0 if action_func succeeded, not 0 if failed
	Reviewer : 
------------------------------------*/

int SListForEach(s_list_t *s_list, s_list_iterator_t iter_from, s_list_iterator_t iter_to, action_function_t action_func, void *parameter)
{

	int result = 0;
	
	assert(NULL != s_list);
	assert(NULL != iter_from);
	
	
	while (iter_from != iter_to && NULL != iter_from->next)
	{
		if (action_func(iter_from ->data, parameter) == 0)
		{
			result++;
		}
		
		iter_from = iter_from->next;
	}
	
	return (SListSize(s_list)) - result;

}


