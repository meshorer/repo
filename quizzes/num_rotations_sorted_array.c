#include <stddef.h>
#include <stdio.h>

int IterBinarySearch(int *arr,int value,size_t size)
{
    size_t i = 0;
    while (0 < size)
    {
        i = size/2;
        if (value == arr[i])
        {
            return i;
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

int main()
{
    int arr[] ={7,8,11,1,4,5};
    printf("num rotations is %lu\n",IterBinarySearch(arr,1,6));

    return 0;

}