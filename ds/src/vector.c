
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
/*date: Dec 7
description: initialize the vecetor 
status: done
Reviewer: 
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
 
 /*date: Dec 7
description: peak the element by particular index
status: done
Reviewer: 
*/

void *VectorAccess(vector_t *vec, size_t index)
{
	return (char *)vec->data +((index)*vec->elem_size);
}

/************************************/

/*date: Dec 7
description: resize the capacity of the vector
status: done
Reviewer: 
*/

void VectorResize(vector_t *vec, size_t size)
{
	vec->data = realloc (vec->data,size);
	if (NULL == vec)
	{
		printf("allocation failed!\n");
	}
	
	vec->capacity = size;
}

/************************************/

/*date: Dec 7
description: free the vector from the memory (allocated memory) 
status: done
Reviewer: 
*/

void VectorDestroy(vector_t *vec)
{
	free(vec->data);
	free(vec);
}
	
/************************************/

/*date: Dec 7
description: add element to the back of the vector
status: done
Reviewer: 
*/

void VectorPushBack(vector_t *vec, const void *data)
{
	if (vec->total_elem == vec->capacity)
	{
		vec->data = realloc (vec->data,((vec->capacity*2))*vec->elem_size);
		vec->capacity*=2;
	}
	memcpy((char *)vec->data +(vec->total_elem*vec->elem_size),data, vec->elem_size) ;
	vec->total_elem++;
	
}

/************************************/

/*date: Dec 7
description: pop - erase the back element from vector
status: done
Reviewer: 
*/

void VectorPopBack(vector_t *vec)
{
	vec->data = '\0';
	vec->total_elem--;
}

/************************************/

/*date: Dec 7
description: shrink the capacity of the vector to the number of elements + additional 10% memory of the previous size  
status: done
Reviewer: 
*/

void VectorShrink(vector_t *vec) 
{
	vec->data = realloc (vec->data,(vec->total_elem + (vec->capacity/10))*vec->elem_size);
	if (NULL == vec)
	{
		printf("allocation failed!\n");
	}
	vec->capacity = vec->total_elem + (vec->capacity/10);
}	

/************************************/

/*date: Dec 7
description: returns how many elements are in the vector
status: done
Reviewer: 
*/

size_t VectorSize(const vector_t *vec)
{
	return vec->total_elem;

}

/************************************/

/*date: Dec 7
description: returns the capacity in the vector
status: done
Reviewer: 
*/

size_t VectorCapacity(const vector_t *vec)
{
	return vec->capacity;

}

/************************************/
