#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#define NUM 100000

size_t arr[NUM] = {0};

void *routine(void *arg)
{
    size_t i = (size_t)arg;
    arr[i] = i;

    return NULL;
}

int main()
{
    pthread_t id[NUM];
    size_t i;
    time_t start, end;
    int count = 0;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    start = time(NULL);
    for (i = 0; i < NUM; i++)
    {
        if (pthread_create(&id[i], &attr, routine, (void *)i) != 0)
        {
            perror("pthread_create");
        }
        
    }
    
    end = time(NULL);
   
    for (i = 0; i < NUM; i++)
    {
        if (arr[i] == i)
        {
            count++;
        }
    }

    printf("count = %d\n", count);
    printf("total time = %ld\n", end - start);
    return 0;
}
