#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "hash_table.h"
#include "slist.h"


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
 
    index_table = malloc(sizeof(s_list_t*) * table_size);

    my_hash_table = malloc(sizeof(struct hash_table));

    my_hash_table->compare_func_t = compare_func;
    my_hash_table->hash_func_t = hash_func;
    my_hash_table->table = index_table;
    my_hash_table->table_size = table_size;

    for ( i = 0; i < table_size; i++)
    {
        index_table[i] = SListCreate();
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

   for (i = 0; i < hash_table->table_size; i++)
   {
        /*FreeHashNode(hash_table->table[i]);*/
        SListDestroy(hash_table->table[i]);
   }

   free(hash_table->table);
   free (hash_table);
   
}

int HashIsEmpty(const hash_table_t *hash_table)
{
    size_t i = 0;
    for (i = 0; i < hash_table->table_size; i++)
    {
        if (0 < SListSize(hash_table->table[i]))
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

    for (i = 0; i < hash_table->table_size; i++)
    {
        sum+= SListSize(hash_table->table[i]);
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
    struct hash_node* my_data;
    
    hash_node = malloc(sizeof(struct hash_node));
    if (NULL == hash_node)
    {
        return 1;
    }
    printf("here, key is: %d\n",*(int*)key);
    hash_node->key = (void *)key;
    hash_node->value = (void *)value;
    i = hash_table->hash_func_t(key);
    printf("index hash is: %lu\n",i);
    if (i > hash_table->table_size)
    {
        return 1;
    }
    list = hash_table->table[i];
    if (NULL == list)
    {
        return 1;
    }

    first_node = SListBegin(list);
    if (NULL == first_node)
    {
        return 1;
    }
    
    first_node = SListAdd(list,first_node,hash_node);
    if (NULL == first_node)
    {
        return 1;
    }
    my_data = (struct hash_node*)SListGet(list,first_node);
    printf("the key inserted is: %d\n", *(int*)my_data->key);
    printf("the value inserted is: %lu\n", *(int*)my_data->value);
    return 0;
}
/*void FreeHashNode(struct s_list* list)
{
   struct s_list_node *first_node = SListBegin(list);
   

}*/
    