#include "vector.h"
#include "stdio.h"


int main()
{


	int num = 5;
	int num1 = 3;
	vector_t *vec1 = VectorCreate(10,4);

	printf("capcity is %lu\n",VectorCapacity(vec1));
	VectorPushBack(vec1,&num1);
	VectorPushBack(vec1,&num1);
	VectorPushBack(vec1,&num1);
	VectorPushBack(vec1,&num1);
	VectorPushBack(vec1,&num1);
	VectorPushBack(vec1,&num1);
	printf("size is %lu\n",VectorSize(vec1));		
	VectorShrink(vec1);	
	printf("capcity after shrink from 10 is %lu\n",VectorCapacity(vec1));
	VectorResize(vec1, 3);	
	printf("capcity after resize to 3 is %lu\n",VectorCapacity(vec1));		
	VectorResize(vec1, 20);		
	printf("capcity should be 20 : is %lu\n",VectorCapacity(vec1));	
	printf("size is %lu\n",VectorSize(vec1));		
	VectorShrink(vec1);	
	printf("capcity after shrink from 20 is %lu\n",VectorCapacity(vec1));					
	VectorDestroy(vec1);
	return 0;
	
}

