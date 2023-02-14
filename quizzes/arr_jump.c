#include <stdio.h> /* printf */

#define MAX_SIZE 100


int ArrJump(int *arr, int size, int index, int *visited) 
{
	if (index < 0 || index > size-1)		/* index is out of bounds */
	{
		return 0;
	}

	if (1 == visited[index]) 			/* index already visited */
	{
		return 0;
	}

	if (index == size - 1)				/* if index is the last index */
	{
		return 1;
	}
	visited[index] = 1;				/* we don't want to visit the same index more than once cause we might end up with an infinite loop */

	if(ArrJump(arr, size, index + arr[index], visited) == 1 || ArrJump(arr, size, index - arr[index], visited) == 1)	
	{
		return 1;
	}
	visited[index] = 0;				/* when returning from recursion, if an index was visited, it's being unvisited and therefore set to 0 */
	return 0;		
}



int main()
{

    int arr[9] = {2, 15, 1, 6, 37, 2, 4, 3, 5};
    int arr2[6] = {1, 3, 2, 1, 4, 3};
    int arr3[9] = {2,4,1,6,4,2,4,3,5};
    int visited[MAX_SIZE] = {0};

    if (1 == (ArrJump(arr, 9, 0, visited)))
    {
        printf("A path from the start to the end of the array was found.\n");
    }
    else
    {
        printf("No path from the start to the end of the array was found.\n");
    }

    if (1 == (ArrJump(arr2, 6, 0, visited)))
    {
        printf("A path from the start to the end of the array was found.\n");
    }
    else
    {
        printf("No path from the start to the end of the array was found.\n");
    }
	
	 if (1 == (ArrJump(arr3, 9, 0, visited)))
    {
        printf("A path from the start to the end of the array was found.\n");
    }
    else
    {
        printf("No path from the start to the end of the array was found.\n");
    }
    return 0;
}


int ArrJumpe(int *arr, int size, int index, int *visited)
{
     int canReachRight, canReachLeft;
     int jump = arr[index];
    /* Check if the current index is out of bounds */
    if (index < 0 || index >= size)
    {
        return 0;
    }

    /* Check if the current index has already been visited */
    if (visited[index] == 1)
    {
        return 0;
    }

    /* Check if the current index is the last index */
    if (index == size - 1)
    {
        return 1;
    }

    /* Mark the current index as visited */
    visited[index] = 1;

    /* Recursively check if it is possible to reach the end from the current index by jumping to the right or left */
   
    canReachRight = ArrJump(arr, size, index + jump, visited);
    canReachLeft = ArrJump(arr, size, index - jump, visited);

    /* Unmark the current index as visited */
    visited[index] = 0;

    /* Return true if it is possible to reach the end from the current index by jumping to the right or left */
    if (canReachRight || canReachLeft)
    {
        return 1;
    }

    return 0;
}

 
