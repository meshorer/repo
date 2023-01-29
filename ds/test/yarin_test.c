#include <assert.h> /* assert */
#include <stdio.h> /* printf */
#include <string.h> /* strdup */

#include"hash_table.h"

#define BUFFER_SIZE 128

/*
size_t hash_func(const void *key)
{
    assert(NULL != key);

    return (*(size_t*)key) % 10;
}
*/
size_t HashFunc(const void *key)
{
	char *str = (char*)key;
	size_t sum = 3 * (*str);

	while (*str)
	{
		sum += (size_t)(*str);
		++str;
	}

	/*printf("the hashed value of %s is: %lu\n",(char*)key, sum % 100);*/
	return sum % 10; 
}


int compare_func(const void *data1, const void *data2)
{
    assert(NULL != data1);
    assert(NULL != data2);

    return *(size_t*)data1 - *(size_t*)data2; 
}

int action_func(void *data, void *parameter)
{
    if(NULL == data || NULL == parameter)
    {
        return 1;
    }

    *(int*)data += *(int*)parameter;

    return 0;
}

int main()
{
    extern char* strdup(const char*);

    int chars[] = {'a','b','c','d','e','f','g','h','i'};
    size_t keys1[] = {1,2,5,13,35,94,255,688,1860,35};

    size_t chars_size = sizeof(chars) / sizeof(chars[0]);
    size_t i = 0;
    int param = 1;

    size_t table_size = 10;

    FILE *dictionary_file = NULL;
    char buffer[BUFFER_SIZE] = {'0'};
    char *key = NULL;

    hash_table_t *my_hash_table = HashCreate(&HashFunc, table_size, compare_func);

    printf("\n*******************************************************************************\n");

    printf("The size of the hash table before inserting anything is(should be 0) - %ld\n", HashSize(my_hash_table));
    printf("Checking if the hash table is emtpy before inserting anything is(should be 1) - %d\n",HashIsEmpty(my_hash_table));

    printf("\n*******************************************************************************\n");

    printf("******** FIRST INSERT LOOP *******\n");
    while(i < chars_size)
    {
        HashInsert(my_hash_table, keys1 + i, chars + i);
        ++i;   
    }/*
    HashInsert(my_hash_table, keys1 + i, chars + i);
    ++i;

    HashInsert(my_hash_table, keys1 + i, chars + i);
    ++i;

    HashInsert(my_hash_table, keys1 + i, chars + i);
    ++i;

    HashInsert(my_hash_table, keys1 + i, chars + i);
    ++i;

    HashInsert(my_hash_table, keys1 + i, chars + i);
    ++i;   

    HashInsert(my_hash_table, keys1 + i, chars + i);
    ++i;

    HashInsert(my_hash_table, keys1 + i, chars + i);
    ++i;

    HashInsert(my_hash_table, keys1 + i, chars + i);
    ++i;

    HashInsert(my_hash_table, keys1 + i, chars + i);
    ++i;

    HashInsert(my_hash_table, keys1 + i, chars + i);
    ++i;*/

    printf("\n*******************************************************************************\n");
    
    printf("The size of the hash table after one insert loop is(should be 9) - %ld\n", HashSize(my_hash_table));
    printf("Checking if the hash table is emtpy after one insert loops is(should be 0) - %d\n",HashIsEmpty(my_hash_table));

    printf("\n*******************************************************************************\n");

    HashForEach(my_hash_table, action_func,  &param);

    printf("\n*******************************************************************************\n");

    i = 0;
    while(i < chars_size)
    {
        HashRemove(my_hash_table, keys1 + i);
        ++i;   
    }
   
    printf("The size of the hash table after one remove loop is(should be 0) - %ld\n", HashSize(my_hash_table));
    printf("Checking if the hash table is emtpy after one remove loop is(should be 1) - %d\n",HashIsEmpty(my_hash_table));

    /*
    printf("******** SECOND INSERT LOOP *******\n");
    while(j < chars_size)
    {
        --i;
        HashInsert(my_hash_table, &j, chars + i);
        ++j;
    }
    */
    HashDestroy(my_hash_table);

    printf("\n*******************************************************************************\n");
    printf("************************* Now loading dictionary file *************************\n");
    printf("*******************************************************************************\n\n");

    my_hash_table = HashCreate(&HashFunc, table_size, compare_func);

    dictionary_file = fopen("/etc/dictionaries-common/words","r");
    if(NULL == dictionary_file)
    {
        printf("dictionary file open failed\n");
        return 1;
    }

    while (fgets(buffer, BUFFER_SIZE, dictionary_file)) 
    {
        key = strdup(buffer); 
        HashInsert(my_hash_table, key, chars);
    }

    if(0 != fclose(dictionary_file))
    {
        printf("Couldnt close dictionary file\n");
        return 1;
    }
    
    HashDestroy(my_hash_table);


    return 0;
}
