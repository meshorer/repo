#include <stdio.h>

/* function to Swap two elements in the array */
void Swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

/* Partition function to find the pivot and sort elements around it */
int Partition(int *arr, int start, int end)
{
    int pivot = arr[end];		                        /* pivot is the last element in the array */
    int i = (start - 1);			                    /* index of the smaller element */
    int j = 0;
    /* loop through all elements from start to end-1 */
    for (j = start; j <= end - 1; j++)
    {
                                                        
        if (arr[j] < pivot)                             /* if current element is smaller than the pivot */
        {
            i++;						                /* increment index of smaller element */
            Swap(&arr[i], &arr[j]);	                    /* Swap the current element with the smaller element */
        }
    }
    Swap(&arr[i + 1], &arr[end]);	                    /* Swap the pivot with the smaller element */
    return (i + 1);					                    /* return the pivot index */
}

/* main quick sort function */
void QuickSort(int *arr, int start, int end)
{
    int pivot = 0;
    /* if start is smaller than end, perform quick sort */
    if (start < end)
    {
        pivot = Partition(arr, start, end);		    /* find pivot */
        QuickSort(arr, start, pivot - 1);				/* sort elements on the left of pivot */
        QuickSort(arr, pivot + 1, end);			        /* sort elements on the right of pivot */
    }
}

int main()
{
    int arr[] = {10, 7, 8, 32, 1, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    int i = 0;
    QuickSort(arr, 0, n - 1);						

    for (i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    return 0;
}