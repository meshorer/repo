#include <assert.h>
#include <stdlib.h>     /* malloc */
#include "hash_table.h"
#include "slist.h"

struct hash_table       /* management struct */
{
    s_list_t **hash_array;
    size_t arr_size;
    size_t (*hash_func_t)(const void *);
    int (*compare_func_t)(const void *, const void *);  
};

struct key_value
{
    void *key;
    void *value;
};

hash_table_t *HashCreate(hash_func_t hash_func, size_t table_size, compare_func_t compare_func)
{
    hash_table_t *management = NULL;
    s_list_t **hash_arr = NULL;
    size_t i = 0;

    assert(hash_func);
    assert(compare_func);
    assert(table_size);

    management = malloc(sizeof(struct hash_table));     /* allocate space to management struct */
    if (NULL == management)
    {
        return NULL;
    }

    hash_arr = malloc(table_size * sizeof(s_list_t*));  /* allocate space to array */
    if (NULL == hash_arr)
    {
        return NULL;
    }

    management->hash_array = hash_arr;                  /* fill management members */
    management->arr_size = table_size;
    management->hash_func_t = hash_func;
    management->compare_func_t = compare_func;

    for(i = 0; i < table_size; i++)                     /* create slist management struct for every array index */
    {
        hash_arr[i] = SListCreate();
    }

    return management;
}

static void FreeKeyValue(struct s_list *current_list)
{
    s_list_iterator_t slist_begin = SListBegin(current_list);   /* get first node in slist */
    s_list_iterator_t slist_end = SListEnd(current_list);       /* get last node in slist */
    
    while(slist_begin < slist_end)
    {
        free(SListGet(current_list, slist_begin));              /* free key_value struct */
        slist_begin = SListNext(slist_begin);
    }
}

void HashDestroy(hash_table_t *hash_table)
{
    size_t i = 0;

    assert(hash_table);

    for(i = 0; i < hash_table->arr_size; i++)                   
    {
        FreeKeyValue(hash_table->hash_array[i]);                /* free key_value struct */
        SListDestroy(hash_table->hash_array[i]);                /* free slist */
    }

    free(hash_table->hash_array);                            
    free(hash_table);
}

size_t HashSize(const hash_table_t *hash_table)
{
    size_t i = 0;
    size_t total_size = 0;
    
    assert(hash_table);

    for(i = 0; i < hash_table->arr_size; i++)
    {
        total_size += SListSize(hash_table->hash_array[i]);     /* calculate every slist size and sum */
    }
    return total_size;
}

int HashIsEmpty(const hash_table_t *hash_table)
{
    assert(hash_table);

    if(0 != HashSize(hash_table))
    {
        return 0;
    }
    return 1;
}

int HashInsert(hash_table_t *hash_table, const void *key, const void *value)
{
    size_t hashed_key = 0;
    s_list_iterator_t slist_begin = NULL;
    struct key_value *key_value_pair = NULL;

    assert(hash_table);
    assert(key);
   
    if(NULL != HashFind(hash_table, key))
    {
        return 1;
    } 
    hashed_key = hash_table->hash_func_t(key);

    slist_begin = SListBegin(hash_table->hash_array[hashed_key]);

    key_value_pair = malloc(sizeof(struct key_value));
    if(NULL == key_value_pair)
    {
        return 1;
    }

    key_value_pair->key = (void*)key;
    key_value_pair->value = (void*)value;

    if(NULL == SListAdd(hash_table->hash_array[hashed_key], slist_begin, key_value_pair))
    {
        return 1;
    }

    return 0;
}
static struct s_list_node *GetSlistNode(const hash_table_t *hash_table, size_t hashed_key, void *key)
{
    struct s_list *current_list = NULL;
    struct key_value *key_value_pair = NULL;
    s_list_iterator_t slist_end = NULL;
    s_list_iterator_t slist_begin = NULL;

    current_list = hash_table->hash_array[hashed_key];

    slist_begin = SListBegin(current_list);
    slist_end = SListEnd(current_list);

    while(slist_begin != slist_end)
    {
        key_value_pair = SListGet(current_list, slist_begin);
        if(0 == (hash_table->compare_func_t(key_value_pair->key, (void*)key)))
        {
            return slist_begin;
        }
        slist_begin = SListNext(slist_begin);
    }
    return NULL;
}
static struct key_value *GetKeyValue(const hash_table_t *hash_table, struct s_list_node *current_node, size_t hashed_key)
{   
    struct s_list *current_list = hash_table->hash_array[hashed_key];

    return SListGet(current_list, current_node);
}

void *HashFind(const hash_table_t *hash_table, const void *key)
{
    size_t hashed_key = 0;
    struct s_list_node *current_node = NULL;
    struct key_value *key_value_pair = NULL;

    assert(hash_table);
    assert(key);

    hashed_key = hash_table->hash_func_t(key);
    
    current_node = GetSlistNode(hash_table, hashed_key, (void*)key);
    if(NULL == current_node)
    {
        return NULL;
    }

    key_value_pair = GetKeyValue(hash_table, current_node, hashed_key);

    return key_value_pair->value;
}

int HashForEach(hash_table_t *hash_table, action_func_t action_func, void *param)
{
    size_t i = 0;
    struct s_list *current_list = NULL;
    s_list_iterator_t slist_begin = NULL;
    s_list_iterator_t slist_end = NULL;
    struct key_value *key_value_pair = NULL;

    assert(hash_table);
    assert(action_func);

    for(i = 0; i < hash_table->arr_size; i++)
    {
        current_list = hash_table->hash_array[i];
        slist_begin = SListBegin(current_list);
        slist_end = SListEnd(current_list);
        
        while(slist_begin < slist_end)
        {
            key_value_pair = SListGet(current_list, slist_begin);
            if(0 != action_func(key_value_pair->value, param))
            {
                return -1;
            }
            slist_begin = SListNext(slist_begin);
        }
    }
    return 0;
}

int HashRemove(hash_table_t *hash_table, const void *key)
{
    size_t hashed_key = 0;
    struct s_list_node *current_node = NULL;
    struct key_value *key_value_pair = NULL;

    hashed_key = hash_table->hash_func_t(key);
    current_node = GetSlistNode(hash_table, hashed_key, (void*)key);
    if(NULL == current_node)                                    /* if key doesn't exist - there's nothing to remove */
    {
        return 1;
    }
    key_value_pair = GetKeyValue(hash_table, current_node, hashed_key);

    free(key_value_pair);                                       /* free key value node */
    if(NULL == SListRemove(hash_table->hash_array[hashed_key], current_node))
    {
        return 1;
    }
    return 0;
}
