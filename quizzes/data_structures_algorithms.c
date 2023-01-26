#include <stdio.h>

int find(char *arr, int size, char number)
{
    
    while (size--)
    {
        if(*arr ^ number)
        {
            return 1;
        }
        arr++;
    }
    return 0;
}


void ReverseArray(char *arr, int start, int end)    
{ 
	while (start < end) 
	{ 
		char temp = arr[start]; 
		arr[start] = arr[end]; 
		arr[end] = temp; 
		start++; 
		end--; 
	} 
}     
void CircularShift(char *arr, int shifts, int arr_size)      
{ 
	ReverseArray(arr, 0, arr_size - 1); 
	ReverseArray(arr, 0, shifts - 1); 
	ReverseArray(arr, shifts, arr_size - 1); 
}     

int main()
{
    char string[] = {'d','a','n','i','e','l','m','e','s','h','o'};


    printf("is e exists? %d\n",find(string,11,'x'));

    return 0;
}