#include "vector.h"
#include "stdio.h"


int main()
{


	int num = 5;
	int num1 = 3;
	vector_t *vec1 = VectorCreate(10,4);


	printf("size is %lu\n",VectorSize(vec1));
	printf("capcity is %lu\n",VectorCapacity(vec1));

	printf("capcity is %lu\n",VectorCapacity(vec1));
	VectorPushBack(vec1,&num1);
	printf("capcity is %lu\n",VectorCapacity(vec1));
	VectorPushBack(vec1,&num1);
	printf("capcity is %lu\n",VectorCapacity(vec1));
	VectorPushBack(vec1,&num1);
	printf("access is %ld\n",*(int *)VectorAccess(vec1,2));	
	printf("capcity is %lu\n",VectorCapacity(vec1));
	VectorPushBack(vec1,&num1);
	printf("capcity is %lu\n",VectorCapacity(vec1));
	VectorPushBack(vec1,&num1);
	printf("capcity is %lu\n",VectorCapacity(vec1));
	VectorPushBack(vec1,&num1);
	printf("size is %lu\n",VectorSize(vec1));

	printf("size is %lu\n",VectorSize(vec1));
	printf("capcity is %lu\n",VectorCapacity(vec1));
	
	VectorResize(vec1, 20);
	printf("capcity is %lu\n",VectorCapacity(vec1));

	printf("access is %d\n",*(int *)VectorAccess(vec1,1));
	VectorShrink(vec1);
	printf("capcity after shrink is %lu\n",VectorCapacity(vec1));	
	VectorDestroy(vec1);
	return 0;
	
}

