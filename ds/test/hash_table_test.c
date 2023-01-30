#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "hash_table.h"
#include "slist.h"
#include "utilities.c"

int Comparing_func(const void *data1, const void *data2)
{
    return strcmp(data1,data2);
}

size_t Hashing_function(const void *key)
 {
    char *str = (char*)key;
	size_t sum = 3 * (*str);

	while (*str)
	{
		sum += (size_t)(*str);
		++str;
	}
	return sum % 1000; 
 }


int main()
{

    hash_table_t *my_hash_table = NULL;
    
    int i = 0;
    FILE *fp = NULL;
    char *line[104334];
	
    char word[20] = {0};
   
    my_hash_table = HashCreate(Hashing_function,1000,Comparing_func);
 
    fp = fopen("/etc/dictionaries-common/words","r");
	if (fp == NULL)
	{
		return 1;
   	}
    for (i = 0; i < 104334; ++i)
    {
        line[i] = malloc(46);
    }
    i = 0;
    while(NULL != fgets(line[i],100,fp))
    {
        
        line[i][strcspn(line[i],"\r\n")] = 0;
        if (0 ==  HashInsert(my_hash_table,line[i],line[i]))
        {
            printf("success in word %s\n",line[i]);
        }  
        ++i;
        if (i == 104334)
        {
            break;
        }
     
    }
    
	printf("number of words is: %lu\n",HashSize(my_hash_table));
   
    if(NULL != HashFind(my_hash_table, "zoos")){PRINT_TESTS(0);}else{PRINT_TESTS(1);}
    if (0 == strcmp("zoos",HashFind(my_hash_table, "zoos"))){PRINT_TESTS(0);}else{PRINT_TESTS(1);}
    printf("enter word\n");
    while(1)
    {
        scanf("%s",(char*)&word);
        if (0 == strcmp("exit",word))
        {
            break;
        }
        if(NULL != HashFind(my_hash_table, &word))
        {
            printf("in dictionary\n");
        }
        else
        {
            printf("not in dictionary!\n");
        }
    }
	fclose(fp);
		
    for (i = 0; i < 104334; ++i)
    {
        free(line[i]);
    }
    
    /* if (0 ==  HashInsert(my_hash_table,&line,&line)){PRINT_TESTS(0);}else{PRINT_TESTS(1);}*/

    /*if (1 ==  HashIsEmpty(my_hash_table)){PRINT_TESTS(0);}else{PRINT_TESTS(1);}
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
    if (NULL == HashFind(my_hash_table, &key3)){PRINT_TESTS(0);}else{PRINT_TESTS(1);}*/
    


    HashDestroy(my_hash_table);
   
    return 0;
}

