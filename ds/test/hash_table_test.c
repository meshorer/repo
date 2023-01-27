#include <string.h>
#include <stdio.h>
#include "hash_table.h"
#include "slist.h"
#include "utilities.c"

size_t Hashing_function(const void *key)
{
    return strlen(key);
}

int Comparing_func(const void *data1, const void *data2)
{
    return (int*)data1 - (int*)data2;
}

int action_function(void *data, void *parameter)
{
    printf("node\n");
    return 0;
}

int main()
{

    hash_table_t *my_hash_table = NULL;
    char *key1 = "daniel";
    int value1 = 29;
    char *key2 = "yael";
    int value2 = 29;
    char *key3 = "geffen";
    int value3 = 3;
    char *key4 = "ido";
    int value4 = 1;

    my_hash_table = HashCreate(Hashing_function,10,Comparing_func);
    if (1 ==  HashIsEmpty(my_hash_table)){PRINT_TESTS(0);}else{PRINT_TESTS(1);}
    if (0 ==  HashInsert(my_hash_table,&key1,&value1)){PRINT_TESTS(0);}else{PRINT_TESTS(1);}
    if (0 ==  HashIsEmpty(my_hash_table)){PRINT_TESTS(0);}else{PRINT_TESTS(1);}
    if (0 ==  HashInsert(my_hash_table,&key2,&value2)){PRINT_TESTS(0);}else{PRINT_TESTS(1);}
    if (0 ==  HashInsert(my_hash_table,&key3,&value3)){PRINT_TESTS(0);}else{PRINT_TESTS(1);}
    if (0 ==  HashInsert(my_hash_table,&key4,&value4)){PRINT_TESTS(0);}else{PRINT_TESTS(1);}
    if (value1 ==  *(int *)HashFind(my_hash_table, &key1)){PRINT_TESTS(0);}else{PRINT_TESTS(1);}
    if (value2 ==  *(int *)HashFind(my_hash_table, &key2)){PRINT_TESTS(0);}else{PRINT_TESTS(1);}
    if (value3 ==  *(int *)HashFind(my_hash_table, &key3)){PRINT_TESTS(0);}else{PRINT_TESTS(1);}
    
    if (4 ==  HashSize(my_hash_table)){PRINT_TESTS(0);}else{PRINT_TESTS(1);}
    if (0 ==  HashForEach(my_hash_table,action_function,&key1)){PRINT_TESTS(0);}else{PRINT_TESTS(1);}
    if (0 ==  HashRemove(my_hash_table,&key3)){PRINT_TESTS(0);}else{PRINT_TESTS(1);}
    if (1 ==  HashRemove(my_hash_table,&key3)){PRINT_TESTS(0);}else{PRINT_TESTS(1);}
    if (3 ==  HashSize(my_hash_table)){PRINT_TESTS(0);}else{PRINT_TESTS(1);}
    if (NULL == HashFind(my_hash_table, &key3)){PRINT_TESTS(0);}else{PRINT_TESTS(1);}
    


    HashDestroy(my_hash_table);
    return 0;
}

