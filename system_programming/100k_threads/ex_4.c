#include <pthread.h>
#include <stdio.h>

#define NUM_OF_THREADS 8 /* optimal number of threads */
#define ARG  7611575250


/* to measure the statistics with perf, use:
    sudo perf stat ./a.out
*/

size_t range_size =  ARG / NUM_OF_THREADS;  /* fix size of range  that every thread gets to calculate */

void *routine(void *arg)
{
    size_t my_arg = (size_t)arg;
    size_t i = 0;
    size_t sum_of_divisors = 0;
    
    for(i = my_arg ; i < my_arg + range_size; ++i)
    {
          if (0 == ARG % i)
          {
              sum_of_divisors += i;
          }
    } 
 
    return (void*)sum_of_divisors;
}

int main()
{
    pthread_t id[NUM_OF_THREADS];
    size_t i = 0;
    time_t start, end;
    size_t arg = 1;                 /* we start with 1 because 0 cannot be divided  */
    void *ret_val = 0;              /* return value from the routine function */
    size_t sum = 0;
   
    start = time(NULL);
    
    if (ARG %NUM_OF_THREADS != 0)   /* solve the raemainder issue */
    {
        range_size+=1;
    }
    for (i = 0; i < NUM_OF_THREADS; i++)
    {
       if (0 != pthread_create(&id[i], NULL, routine, (void*)(arg)))
       {
            perror("pthread_create");      
       }
       arg += range_size;        /* increment arg every time by range_size so the thread will calculate it's own numbers */
    }
    
    for (i = 0; i < NUM_OF_THREADS; i++)
    {
        if (0 != pthread_join(id[i], &ret_val))
        {
            perror("pthread_join");
        }
        sum+=(size_t)ret_val;      /* sum all the returning values from the threads routine function */
    }
    end = time(NULL);
    printf("sum = %lu\n", sum);
    printf("total time = %ld\n", end - start);
   
    return 0;
}
