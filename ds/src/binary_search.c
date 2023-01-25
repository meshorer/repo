#include "binary_search.h"

/*Implement an recursive binary search of a given integer in an array of integers.*/
int RecBinarySearch(int *arr,int value,size_t size)
{
    size_t i = size/2;
    if (arr[i] == value)
    {
        return 1; 
    }
    
    if (1 == size)
    {
        return 0;
    }
    
    return value < arr[i] ? RecBinarySearch(arr,value,i) : RecBinarySearch(arr+i,value,i+(size%2));
}

int IterBinarySearch(int *arr,int value,size_t size)
{
    size_t i = 0;
    while (0 < size)
    {
        i = size/2;
        if (value == arr[i])
        {
            return 1;
        }
        
        if (value  > arr[i] && size != 1)
        {
            size = i + (size%2);
            arr = arr + i;
        }
        else
        {
            size = size/2;
        }
        
        
    }

    return 0;
    
}
