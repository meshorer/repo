
#include "vector.h"

#include <stdio.h> /* for print */
#include <stdlib.h>  /* for malloc, realloc */
#include <assert.h>  /* for asserts */
#include <string.h>  /* for memcpy */

struct vector{
	size_t capacity; /* how many members the vector can contain     */
	size_t elem_size;
	void *data;
	size_t total_elem; /* how many members there are currently    */
};

/************************************/
/*Date: Dec 7
Description: initialize the vecetor 
Status: done
Reviewer :Or 
*/


vector_t *VectorCreate(size_t capacity, size_t elem_size)
{
	vector_t *ptr = malloc(sizeof(vector_t));
	assert (NULL != ptr);
	
	ptr->capacity = capacity;
	ptr->elem_size = elem_size;
	
	ptr->data = malloc(capacity * elem_size);
	assert (NULL != ptr);
	
	ptr->total_elem = 0; 
	
	return ptr;
}
	
/************************************/
 
 /*Date: Dec 7
Description: peak the element by particular index
Status: done
Reviewer :Or 
*/

void *VectorAccess(vector_t *vec, size_t index)
{
	return (char *)vec->data +((index)*vec->elem_size);
}

/************************************/

/*Date: Dec 7
Description: resize the capacity of the vector
Status: done
Reviewer :Or 
*/

int VectorResize(vector_t *vec, size_t size)
{
	int res = 0;
	vec->data = realloc (vec->data, size * vec->elem_size);
	if (NULL == vec->data)
	{
		res =  1;
	}
	else
	{
		vec->capacity = size;
	}  
	
	return res;
}

/************************************/

/*Date: Dec 7
Description: free the vector from the memory (allocated memory) 
Status: done
Reviewer :Or 
*/

void VectorDestroy(vector_t *vec)
{
	free(vec->data);
	free(vec);
}
	
/************************************/

/*
Date: Dec 7
Description: add element to the back of the vector
Status: done
Reviewer :Or 
*/

void VectorPushBack(vector_t *vec, const void *data)
{
	if (vec->total_elem == vec->capacity)
	{
		VectorResize(vec->data, vec->capacity*2);
	}
	memcpy((char *)vec->data +(vec->total_elem*vec->elem_size),data, vec->elem_size) ;
	vec->total_elem++;
	
}

/************************************/

/*Date: Dec 7
Description: pop - erase the back element from vector
Status: done
Reviewer :Or 
*/

void VectorPopBack(vector_t *vec)
{
	vec->total_elem--;
}

/************************************/

/*Date: Dec 7
Description: shrink the capacity of the vector to the number of elements + additional 10% memory of the previous size  
Status: done
Reviewer :Or 
*/

void VectorShrink(vector_t *vec) 
{
	VectorResize(vec,(vec->total_elem + (vec->capacity/10)));  
}	

/************************************/

/*Date: Dec 7
Description: returns how many elements are in the vector
Status: done
Reviewer :Or 
*/

size_t VectorSize(const vector_t *vec)
{
	return vec->total_elem;
}

/************************************/

/*Date: Dec 7
Description: returns the capacity in the vector
Status: done
Reviewer :Or 
*/

size_t VectorCapacity(const vector_t *vec)
{
	return vec->capacity;
}

/************************************/
