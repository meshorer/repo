/* reviewer : Daniel*/
#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */
#include <string.h>
#include "hash_table.h"
#include "slist.h"

/* need to complie with slist*/
struct hash_table

{
    int (*compare_func_t)(const void *, const void *);
    size_t (*hash_func_t)(const void *);
    size_t table_size;
    s_list_t **arr;
};

typedef struct key_value
{
    void *key;
    void *value;
} pairs;

/* Create a hash table, receives a compare function to compare between elements and hash function to hash the key*/
hash_table_t *HashCreate(hash_func_t hash_func, size_t table_size, compare_func_t compare_func)
{
    hash_table_t *hash_table = NULL;
    s_list_t **arr = NULL;
    size_t i = 0;

    assert(hash_func);
    assert(table_size);
    assert(compare_func);

    hash_table = malloc(sizeof(struct hash_table));
    if (NULL == hash_table)
    {
        return NULL;
    }

    arr = malloc(table_size * sizeof(s_list_t *));
    if (NULL == arr)
    {
        return NULL;
    }

    hash_table->arr = arr;
    hash_table->compare_func_t = compare_func;
    hash_table->hash_func_t = hash_func;
    hash_table->table_size = table_size;

    for (; i < table_size; i++)
    {
        arr[i] = SListCreate();
    }

    return hash_table;
}

/* insert node in the hash table,
return value:
    0 - success
    1 - failure
 */
int HashInsert(hash_table_t *hash_table, const void *key, const void *value)
{
    size_t hashkey = 0;
    struct s_list_node *first_node = NULL;
    pairs *key_value = NULL;

    assert(hash_table);
    assert(key);

    hashkey = hash_table->hash_func_t(key);

    if ( NULL != HashFind(hash_table, key))
    {
    	
   	return 1;
    }
    
    first_node = SListBegin(hash_table->arr[hashkey]);

    key_value = malloc(sizeof(pairs));
    if (NULL == key_value)
    {

        return 1;
    }

    key_value->key = (void *)key;
    key_value->value = (void *)value;

    if (NULL == SListAdd(hash_table->arr[hashkey], first_node, key_value))
    {
        return 1;
    }

    return 0;
}
/* traverse through the hash table with a given key and return a void * (value), NULL if does not exist */
void *HashFind(const hash_table_t *hash_table, const void *key)
{
    pairs *key_value = NULL;
    struct s_list_node *slist_node = NULL;
    size_t hashkey = 0;
    struct s_list *list = NULL;
    s_list_iterator_t iter_start = NULL;
    s_list_iterator_t iter_end = NULL;

    assert(hash_table);
    assert(key);

    hashkey = hash_table->hash_func_t(key);
    list = hash_table->arr[hashkey];
    iter_start = SListBegin(list);
    iter_end = SListEnd(list);

    while (iter_start != iter_end)
    {
        key_value = SListGet(list, iter_start);

        if (0 == (hash_table->compare_func_t(key_value->key, (void *)key)))
        {
            slist_node = iter_start;
            break;
        }

        iter_start = SListNext(iter_start);
    }

    if (NULL == slist_node)
    {
        return NULL;
    }

    key_value = SListGet(list, slist_node);

    return key_value->value;
}

/* return the sum of nodes in the hash table */
size_t HashSize(const hash_table_t *hash_table)
{
    size_t i = 0;
    size_t size = 0;

    assert(hash_table);

    for (i = 0; i < hash_table->table_size; i++)
    {
        size += SListSize(hash_table->arr[i]);
    }

    return size;
}

/* check if the hash table contains any nodes
return value:
    0 - NotEmpty
    1 - Empty
*/
int HashIsEmpty(const hash_table_t *hash_table)
{
    size_t i = 0;

    for (i = 0; i < hash_table->table_size; i++)
    {
        if (0 < SListSize(hash_table->arr[i]))
        {
            return 0;
        }
    }

    return 1;
}

/* traverse through the hash table and using action_func on each node, keeping certain data in parameter if needed, return :
0 - if action_func succeeded,
not 0 - if failed */
int HashForEach(hash_table_t *hash_table, action_func_t action_func, void *param)
{
    size_t i = 0;
    struct s_list *list = NULL;
    s_list_iterator_t iter_start = NULL;
    s_list_iterator_t iter_end = NULL;
    pairs *key_value = NULL;

    assert(hash_table);
    assert(action_func);

    for (i = 0; i < hash_table->table_size; i++)
    {
        list = hash_table->arr[i];
        iter_start = SListBegin(list);
        iter_end = SListEnd(list);

        while (iter_start != iter_end)
        {
            key_value = SListGet(list, iter_start);

            if (0 != action_func(key_value->value, param))
            {
                return 1;
            }

            iter_start = SListNext(iter_start);
        }
    }

    return 0;
}

/* remove node in the hash table,
return value:
    0 - success
    1 - failure
*/
int HashRemove(hash_table_t *hash_table, const void *key)
{
    pairs *key_value = NULL;
    struct s_list_node *slist_node = NULL;
    size_t hashkey = 0;
    s_list_iterator_t iter = NULL;
    struct s_list *list = NULL;

    hashkey = hash_table->hash_func_t(key);
    list = hash_table->arr[hashkey];
    iter = SListBegin(list);

    while (NULL != iter)
    {
        key_value = SListGet(list, iter);

        if (0 == (hash_table->compare_func_t(key_value->key, (void *)key)))
        {
            slist_node = iter;
            break;
        }

        iter = SListNext(iter);
    }
    if (slist_node)
    {
        key_value = SListGet(list, slist_node);
        free(key_value); 
        if (NULL == SListRemove(hash_table->arr[hashkey], slist_node))
        {
            return 1;
        }
    }
    return 0;
}

/* Destroy the hash table */
void HashDestroy(hash_table_t *hash_table)
{
    size_t i = 0;
    assert(hash_table);

    for (; i < hash_table->table_size; i++)
    {
        s_list_iterator_t iter = SListBegin(hash_table->arr[i]);

        while (NULL != iter)
        {
            free(SListGet(hash_table->arr[i], iter));
            iter = SListNext(iter);
        }

        SListDestroy(hash_table->arr[i]);
    }

    free(hash_table->arr);
    free(hash_table);
}
