
#include "singly_linked_list.h"

#include <stdio.h> /* for print */
#include <stdlib.h>  /* for malloc, realloc */
#include <assert.h>  /* for asserts */
#include <string.h>  /* for memcpy */


struct s_list_node
{
	void *data;
	struct node *next;
};

struct s_list
{
	struct s_list_node *head;
	struct s_list_node *tail;
	size_t size;
}


s_list_t *SListCreate()
{
	struct s_list *new = malloc(sizeof(s_list));
	struct s_list_node dummy_node = malloc(sizeof(s_list_node));
	
	dummy_node->data = NULL;
	dummy->node->next = NULL;
	
	new->head = dummy_node;
	new->tail = dummy_node; 
	
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
	return s_list->next; 	
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
	
	return iter->data;
}

/************************************/


void SListDestroy(s_list_t *s_list)
{
	while (s_list ->next != NULL)
	{
		free(s_list->data);
		size--;
	}
	
	free(s_list->tail);
	free(s_list_node);

}
