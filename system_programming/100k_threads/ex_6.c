#include <pthread.h>
#include <stdio.h>
#include <omp.h>

#define ARG 7611575250

int main()
{

    size_t my_arg = ARG;
    size_t i = 0;
    size_t sum_of_divisors = 0;
    time_t start, end;
    start = time(NULL);
    
    #pragma omp parallel for 
    for (i = 1; i <= my_arg; ++i)
        {
            if (0 == my_arg % i)
            {
                sum_of_divisors += i;
            }
            printf("number of threads is %d\n", omp_get_num_threads());
        }
  
    end = time(NULL);
    
    printf("%lu\n", sum_of_divisors);
    printf("time is %ld\n", end - start);
    
    return 0;
}

/*
    you can set the number of threads manually using the following command:
    #pragma omp parallel for num_threads(8)
*/