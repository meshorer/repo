
#include <stdio.h>

void swap (int *x,int *y)
{
    int tmp = *x;
    *x=*y;
    *y=tmp;
    
}

int main()
{
    
    int x,y;
    printf("enter first number\n");
    scanf("%d", &x);
    printf("enter second number\n");
    scanf("%d", &y);
    swap(&x, &y);
    
    printf("%d , %d\n", x,y);

    return 0;
}



