#include <string.h>
#include <stdio.h>
#include "hash_table.h"
#include "slist.h"
#include "utilities.c"

size_t Hashing_function(const void *key)
{
    /*return (size_t)key % 10 */
    printf("in function, key is: %lu\n",*(size_t*)key);
    return 2;
}

int Comparing_func(const void *data1, const void *data2)
{
    return (int*)data1 - (int*)data2;
}

int main()
{

    hash_table_t *my_hash_table = NULL;
    int key1 = 3;
    int value1 = 6;

    my_hash_table = HashCreate(Hashing_function,10,Comparing_func);
    if (1 ==  HashIsEmpty(my_hash_table)){PRINT_TESTS(0);}else{PRINT_TESTS(1);}
    if (0 ==  HashInsert(my_hash_table,&key1,&value1)){PRINT_TESTS(0);}else{PRINT_TESTS(1);}
    if (0 ==  HashIsEmpty(my_hash_table)){PRINT_TESTS(0);}else{PRINT_TESTS(1);}

    HashDestroy(my_hash_table);
    return 0;
}

