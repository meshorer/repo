#ifndef __HASH_TABLE_H__ILRD__CR3_
#define __HASH_TABLE_H__ILRD__CR3_

#include <stddef.h> /* size_t */

typedef struct hash_table hash_table_t;

/* returns hashed key */
typedef size_t (*hash_func_t)(const void *key);

/* returns an integer if action succeeded for all elements
return value:
    0 - success
    1 - failure
*/
typedef int (*action_func_t)(void *data, void *parameter);

/*returns an integer indicating the result of the comparison, as follows:

        0 - if the data1 and data2 are equal;
        negative value - if data1 is less than data2;
        positive value - if data1 is greater than data2.
*/
typedef int (*compare_func_t)(const void *data1, const void *data2);

/* Create a hash table, receives a compare function to compare between elements and hash function to hash the key*/
hash_table_t *HashCreate(hash_func_t hash_func,size_t table_size,compare_func_t compare_func);

/* Destroy the hash table */
void HashDestroy(hash_table_t *hash_table);

/* remove node in the hash table, 
return value:
    0 - success
    1 - failure
*/
int HashRemove(hash_table_t *hash_table, const void *key);


/* insert node in the hash table, 
return value:
    0 - success
    1 - failure
 */
int HashInsert(hash_table_t *hash_table, const void *key,const void *value);


/* return the sum of nodes in the hash table */
size_t HashSize(const hash_table_t *hash_table);

/* check if the hash table contains any nodes
return value:
    0 - NotEmpty
    1 - Empty
*/
int HashIsEmpty(const hash_table_t *hash_table);

/* traverse through the hash table with a given key and return a void * (value), NULL if does not exist */
void *HashFind(const hash_table_t *hash_table, const void *key);

/* traverse through the hash table and using action_func on each node, keeping certain data in parameter if needed, return :
0 - if action_func succeeded,
not 0 - if failed */
int HashForEach(hash_table_t *hash_table, action_func_t action_func, void *param);

#endif /*__HASH_TABLE_H__ILRD__CR3_*/