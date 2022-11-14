
#include <stdio.h>

void swap (size_t *x,size_t *y)
{
	size_t tmp = *x;
	*x = *y;
	*y = tmp;
}

void swap_2(size_t **x,size_t **y)

{

    size_t *tmp = *x;
    *x=*y;
    *y=tmp;
}


int main()
{
    size_t x,y;
    printf("enter first number\n");
    scanf("%zu", &x);
    printf("enter second number\n");
    scanf("%zu", &y);
    swap(&x, &y);
    printf("%zu , %zu\n", x,y);
    size_t *adr =  &x;
    size_t *sec_adr = &y;
    printf("%p , %p\n", adr, sec_adr);
    swap_2(&adr, &sec_adr);
    printf("%p , %p", adr, sec_adr);
    return 0;
}
