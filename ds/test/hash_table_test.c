#include <string.h>
#include "hash_table.h"
#include "slist.h"

size_t Hashing_function(const void *key)
{
    return (size_t)key % 100;
}

int Comparing_func(const void *data1, const void *data2)
{
    return (int)data1 - (int)data2;
}

int main()
{

    hash_table_t *my_hash_table = NULL;
    my_hash_table = HashCreate(Hashing_function,10,Comparing_func);

    HashDestroy(my_hash_table);
    return 0;
}

