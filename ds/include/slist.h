#ifndef __SINGLE_LINKED_LIST_H__ILRD__CR3_

#define __SINGLE_LINKED_LIST_H__ILRD__CR3_

#include <stddef.h> /* size_t */ 

typedef struct s_list s_list_t;

typedef struct s_list_node *s_list_iterator_t;

typedef int (*action_function_t)(void *data, void *parameter);

typedef int (*match_function_t)(const void *data, void *parameter);


s_list_t *SListCreate(); 

void SListDestroy(s_list_t *s_list); 

s_list_iterator_t SListAdd(s_list_t *s_list, s_list_iterator_t position, const void *data); 

s_list_iterator_t SListRemove(s_list_t *s_list, s_list_iterator_t iter); 

void SListSet(s_list_t *s_list, s_list_iterator_t iter, const void *data); 

void *SListGet(s_list_t *s_list, s_list_iterator_t iter); 

size_t SListSize(const s_list_t *s_list); 


int SListForEach(s_list_t *s_list, s_list_iterator_t iter_from, s_list_iterator_t iter_to, action_function_t action_func, void *parameter); /*  runs through the SList in certain range including the edges using action_func on each node, keeping certain data in parameter if needed, return 0 if action_func succeeded, not 0 if failed */

s_list_iterator_t SListFind(s_list_iterator_t iter_from, s_list_iterator_t iter_to, match_function_t match_func, void *parameter); /* runs through the SList in certain range including the edges, matching parameter to each node in the range using match_function, return the iterator to the matching node if found, NULL if wasnt found    */

s_list_iterator_t SListBegin(const s_list_t *s_list); 

s_list_iterator_t SListNext(const s_list_iterator_t iter); 

s_list_iterator_t SListEnd(const s_list_t *s_list); 

int IterCmp(s_list_iterator_t iter1,s_list_iterator_t iter2);



#endif  /* __SINGLE_LINKED_LIST_H__ILRD__CR3_ */ 
