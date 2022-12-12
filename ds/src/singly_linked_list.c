
#include "singly_linked_list.h"


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
	struct s_list_node *tail;
	struct s_list_node *next;
	size_t size;
};


s_list_t *SListCreate()
{
	struct s_list *new = (struct s_list *)malloc(sizeof(struct s_list));
	struct s_list_node *dummy_node = malloc(sizeof(struct s_list_node));
	
	dummy_node->data = NULL;
	dummy_node->next = NULL;
	
	new->head = dummy_node;
	new->tail = dummy_node; 
	
	return new;
	
}

/************************************/
/*
Name: SListBegin
Date: Dec 11
Description: returns iterator of the beggining of the SList 
Status: writing
Reviewer : 
*/

s_list_iterator_t SListBegin(const s_list_t *s_list)
{
	return s_list->head;

}
/************************************/

/*
Name: SListNext
Date: Dec 11
Description: returns iterator to next node
Status: writing
Reviewer : 
*/

s_list_iterator_t SListNext(const s_list_iterator_t iter)
{
	return iter->next; 	
} 

/************************************/

/*
Name: SListSet
Date: Dec 11
Description: Update Data in SList in iterator position
Status: writing
Reviewer : 
*/

void SListSet(s_list_t *s_list, s_list_iterator_t iter, const void *data)
{

	if (0 == IterCmp(s_list->head,iter))
	{
		iter->data = (void *)data;
	}
	
	while (0 != IterCmp(s_list->next,iter) && (NULL != s_list->next))
	{
		s_list->next = SListNext(s_list->next);
	}
	
	iter->data = (void *)data;
}



/************************************/

/*
Name: SListGet
Date: Dec 11
Description: Return Data from SList in iterator
Status: writing
Reviewer : 
*/


void *SListGet(s_list_t *s_list, s_list_iterator_t iter)
{
	if (0 == IterCmp(s_list->head,iter))
	{
		return iter->data;
	}
	
	while (0 != IterCmp(s_list->next,iter) && (NULL != s_list->next))
	{
		s_list->next = SListNext(s_list->next);
	}
	
	return iter->data;
}

/************************************/


void SListDestroy(s_list_t *s_list)
{
	
	while (s_list->next != NULL)
	{
		free(s_list->next);
		s_list->next = SListNext(s_list->next);
	}
	
	free(s_list->head);
	free(s_list);
}

/************************************/

/*
Name: SListSize
Date: Dec 11
Description: To Get Size Of SList
Status: writing
Reviewer : 
*/

size_t SListSize(const s_list_t *s_list)
{
	return s_list->size;
}



/************************************/

int IterCmp(s_list_iterator_t iter1,s_list_iterator_t iter2)
{
	return iter1 - iter2;
}



/************************************/

/*
Name: SListAdd
Date: Dec 11
Description: To Add To The SList Data according to iterator position return the iterator pointing to the added node
Status: writing
Reviewer : 
*/

s_list_iterator_t SListAdd(s_list_t *s_list, s_list_iterator_t position, const void *data)
{
	/*if (0 == IterCmp(s_list->head,iter)
	{
		struct s_list_node *new_node = malloc(sizeof(s_list_node));
		new_node->data = iter->data;
		new->node->next = iter->next;
	
		iter->data = data;
		iter->next = &new_node;	
		
		return iter;
	} */
		struct s_list_node *new_node = malloc(sizeof(struct s_list_node));
		
	while (0 != IterCmp(s_list->next,position) && (NULL != s_list->next))
	{
		s_list->next = SListNext(s_list->next);
	}
	

	new_node->data = position->data;
	new_node->next = position->next;
	
	position->data = (void *)data;
	position->next = new_node;
	
	s_list->size++;
	return position;
} 


/************************************/   
