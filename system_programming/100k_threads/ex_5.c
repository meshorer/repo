#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#define ARG 7611575250


int main()
{

    size_t my_arg = ARG;
    size_t i = 0;
    size_t sum_of_divisors = 0;
    time_t start, end;
    start = time(NULL);
    for (i = 1; i <= my_arg; ++i)
    {
        if (0 == my_arg % i)
        {
            sum_of_divisors += i;
        }
    }
    end = time(NULL);
    printf("%lu\n", sum_of_divisors);
    printf("timr is %ld\n", end - start);
    return 0;
}
