#include <assert.h>
#include <stdlib.h>
#include "hash_table.h"
#include "slist.h"


struct hash_table
{
    size_t (*hash_func_t)(const void *key);
    int (*compare_func_t)(const void *data1, const void *data2);
    s_list_t **table;
    size_t table_size;
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
        SListDestroy(hash_table->table[i]);
   }

   free(hash_table->table);
   free (hash_table);
   
}