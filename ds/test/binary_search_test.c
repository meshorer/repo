#include <stdio.h>
#include "binary_search.h"


int main()
{

    int arr[] = {1,2,3,4,5,6,7,8,9};
    int arr2[] = {1,2,3,4,5,6,7,8,9,11,32,45,52,60,62,63,84};
    size_t size2 = sizeof(arr2) / sizeof(arr2[0]);

    printf("\nindex of 6 is: %d\n",RecBinarySearch(arr,1,9));
    printf("iter: \n");
    printf("index of 6 is: %d\n",IterBinarySearch(arr,1,9));

    printf("\nindex of 6 is: %d\n",RecBinarySearch(arr2,45,size2));
    printf("iter: \n");
    printf("index of 6 is: %d\n",IterBinarySearch(arr2,45,size2));

    printf("\nindex of 6 is: %d\n",RecBinarySearch(arr2,43,size2));
    printf("iter: \n");
    printf("index of 6 is: %d\n",IterBinarySearch(arr2,43,size2));

    printf("\nindex of 1 is: %d\n",RecBinarySearch(arr2,1,size2));
    printf("iter: \n");
    printf("index of 1 is: %d\n",IterBinarySearch(arr2,1,size2));

    printf("\nindex of 6 is: %d\n",RecBinarySearch(arr2,84,size2));
    printf("iter: \n");
    printf("index of 6 is: %d\n",IterBinarySearch(arr2,84,size2));

    printf("\nindex of 6 is: %d\n",RecBinarySearch(arr2,0,size2));
    printf("iter: \n");
    printf("index of 6 is: %d\n",IterBinarySearch(arr2,0,size2));

    return 0;
}