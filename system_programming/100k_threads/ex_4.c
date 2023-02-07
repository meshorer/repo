#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <ulimit.h>
#include <sys/time.h>
#include <sys/resource.h>

#define NUM_OF_THREADS 32753
#define ARG  2222222224

size_t range_size =  ARG / NUM_OF_THREADS;

void *routine(void *arg)
{
    size_t my_arg = (size_t)arg;
    size_t i = 0;
    size_t sum_of_divisors = 0;
    size_t end = my_arg + range_size;
    
    for(i = my_arg ; i < end; ++i)
    {
          if (0 == ARG % i)
          {
              sum_of_divisors += i;
          }
    } 
    if (sum_of_divisors!= 0) 
    {
         printf("sum of divisors is %ld\n", sum_of_divisors);
    }
   
    return (void*)sum_of_divisors;
}

int main()
{
    pthread_t id[NUM_OF_THREADS];
    size_t i = 0;
    time_t start, end;
    size_t arg = 1;
    void *ret_val = 0;
    size_t sum = 0;
   
    start = time(NULL);
    
    if (ARG %NUM_OF_THREADS != 0) /* solve the raemainder issue */
    {
        range_size+=1;
    }
    for (i = 0; i < NUM_OF_THREADS; i++)
    {
       pthread_create(&id[i], NULL, routine, (void*)(arg));
       arg += range_size;
       
    }
    
    
    for (i = 0; i < NUM_OF_THREADS; i++)
    {
        pthread_join(id[i], &ret_val);
        sum+=(size_t)ret_val;
    }
    end = time(NULL);
    printf("sum = %lu\n", sum);
    printf("total time = %ld\n", end - start);
    return 0;
}
