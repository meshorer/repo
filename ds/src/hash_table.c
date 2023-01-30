#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "hash_table.h"
#include "slist.h"

void FreeHashNode(s_list_t *s_list);
struct hash_table
{
    size_t (*hash_func_t)(const void *key);
    int (*compare_func_t)(const void *data1, const void *data2);
    s_list_t **table;
    size_t table_size;
}; 

struct hash_node
{
    void *value;
    void *key;
};


hash_table_t *HashCreate(hash_func_t hash_func,size_t table_size,compare_func_t compare_func)
{
    /*  
        1. create array of nodes pointers with malloc(according to size)
        2. create managing struct with malloc
        3. assign to it the functions pointers and the table
        4. create s_list in each element in the array (for loop)
        5. mark 'check' in BD
    */
    s_list_t **index_table = NULL;
    hash_table_t *my_hash_table = NULL;
    size_t i = 0;
 
    assert(hash_func);
    assert(table_size > 0);
    assert(compare_func);
 
    index_table = malloc(sizeof(s_list_t*) * table_size);   /* allocate memory for the table: each element should contain a list managing struct  */

    my_hash_table = malloc(sizeof(struct hash_table));      /* managing struct for the hash table */

    my_hash_table->compare_func_t = compare_func;
    my_hash_table->hash_func_t = hash_func;
    my_hash_table->table = index_table;
    my_hash_table->table_size = table_size;

    for ( i = 0; i < table_size; i++)
    {
        index_table[i] = SListCreate();                     /* assign each element a pointer to list (seperate chaining) */
    }
    
    return my_hash_table ;
    
}

void HashDestroy(hash_table_t *hash_table)
{
    /*  1. for loop until table size
        2. in every iteration. call slistDestroy
        3. free the managing struct
        4. free the array of structs 
    */
    size_t i = 0;
    struct s_list* list = NULL;
    assert(hash_table);
    for (i = 0; i < hash_table->table_size; i++)            /* run thruogh the indices  */
    {
        list = hash_table->table[i];
        FreeHashNode(list);                                 /* in each list, free the hash-node(key-value)  */
        SListDestroy(list);                                 /* destroy each list  */
    }

    free(hash_table->table);                                
    free (hash_table);
   
}

int HashIsEmpty(const hash_table_t *hash_table)
{
    size_t i = 0;
    assert(hash_table);
    for (i = 0; i < hash_table->table_size; i++)            
    {
        if (0 < SListSize(hash_table->table[i]))            /* stop if you find at least non-empty list  */
        {
            return 0;
        }
    }
    return 1;
}

size_t HashSize(const hash_table_t *hash_table)
{
    size_t i = 0;
    size_t sum = 0;
    assert(hash_table);
    for (i = 0; i < hash_table->table_size; i++)
    {
        sum+= SListSize(hash_table->table[i]);              /*sum all the nodes in each list  */
    }
    return sum;
}

int HashInsert(hash_table_t *hash_table, const void *key,const void *value)
{
    /*
        1. check with Find Function that it is not exist.
        2. create a hash-node struct pointer and assign the value and key to it    
        3. hash the key - get the number of index
        4. go to that index and add a new list-node, that it's data point to the hash-node struct pointer we created
        5. return success.
        return value:
    0 - success
    1 - failure
    */
    struct hash_node* hash_node = NULL;
    size_t i = 0;
    struct s_list* list = NULL;
    struct s_list_node *first_node = NULL;
    /*struct hash_node* my_data;*/
    
    assert(hash_table);
    assert(key);
    assert(value);
    if (NULL != HashFind(hash_table,key))                   /* check that the key is not already exist  */
    {
        return 1;
    }
 
    hash_node = malloc(sizeof(struct hash_node));           /* allocate space for the hash-node(key-value) */
    if (NULL == hash_node)
    {
        return 1;
    }
    
    hash_node->key = (void *)key;                           /* assign the key-value in the hash-node  */
    hash_node->value = (void *)value;
    i = hash_table->hash_func_t(key);                       /* get the index number according to the hash-function  */
    
    list = hash_table->table[i];                            /* get the list from the specific index  */
    if (NULL == list)
    {
        return 1;
    }

    first_node = SListBegin(list);                          /* get the first node in the list  */
    if (NULL == first_node)
    {
        return 1;
    }
    
    first_node = SListAdd(list,first_node,hash_node);       /* add a new node and assign to it's data the pointer to the key-value hash node  */
    if (NULL == first_node)
    {
        return 1;
    }
    
    return 0;
}

void *HashFind(const hash_table_t *hash_table, const void *key)
{
    /*  1. hash the key with hash function. 
        2.  go to the relevant index and extract the list from there
        3. iterate each node in the list and send the data to the compare function
    */
    size_t index = 0;
    struct s_list* list = NULL;
    s_list_iterator_t iter = NULL;
    struct hash_node* my_data = NULL;

    assert(hash_table);
    assert(key);
    index = hash_table->hash_func_t(key);                   /* get the index number according to the hash-function  */

    list = hash_table->table[index];
    iter = SListBegin(list);                                /*get the first node in the list*/    
    while (NULL != iter)
    {
        my_data = (struct hash_node*)SListGet(list,iter);    /*get the data of the list (which is the pointer to the hash-node)*/   
        if (NULL == my_data)
        {
            return NULL;
        }
        if (0 == hash_table->compare_func_t(my_data->key,(void *)key))  /*check if the key recieved matches the data from the user*/ 
        {
            return my_data->value;
        }
        iter = SListNext(iter);	
    }
    return NULL;
}


void FreeHashNode(s_list_t *s_list)
{

	s_list_iterator_t iter = SListBegin(s_list);
	
	while (NULL != iter)
	{
        free(SListGet(s_list,iter));
		iter = SListNext(iter);	
	}
	
}

/* remove node in the hash table, 
return value:
    0 - success
    1 - failure
*/
int HashRemove(hash_table_t *hash_table, const void *key)
{
    /*  1. hash the key with hash function. 
        2.  go to the relevant index and extract the list from there
        3. iterate each node in the list until the relevant node is found
        4. use SlistREmove
    */
    size_t index = 0;
    struct s_list* list = NULL;
    s_list_iterator_t iter = NULL;
    struct hash_node* my_data = NULL;
    

    assert(hash_table);
    assert(key);
    index = hash_table->hash_func_t(key);

    list = hash_table->table[index];                                    
    iter = SListBegin(list);                                            /*get the first node in the list*/ 
    while (NULL != iter)
    {
        my_data = (struct hash_node*)SListGet(list,iter);
        if (NULL == my_data)
        {
            return 1;
        }
        
        if (0 == hash_table->compare_func_t(my_data->key,(void *)key))  
        {
            free(my_data);                                              /*free the data (was allocated in the insert function)*/ 
            SListRemove(list,iter);
            return 0;
        }
        iter = SListNext(iter);	
    }
    
        return 1;
}

/* traverse through the hash table and using action_func on each node, keeping certain data in parameter if needed, return :
0 - if action_func succeeded,
not 0 - if failed */
int HashForEach(hash_table_t *hash_table, action_func_t action_func, void *param)
{
    size_t i = 0;
    struct s_list* list = NULL;
    
    assert(hash_table);
    assert(action_func);
    assert(param);

    for (i = 0; i < hash_table->table_size; i++)
    {
        list = hash_table->table[i];
        if (0 != SListForEach(list,SListBegin(list),SListEnd(list),action_func,param))          /*use slistforeach  for every list in the hash-table*/ 
        {
            return 1;
        }
    }
    return 0;
}

