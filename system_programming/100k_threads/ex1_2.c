#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#define NUM 100000

size_t arr[NUM] = {0};

void *routine(void *arg)
{
    size_t i = (size_t)arg;
    arr[i] = i;

    return 0;
}

int main()
{
    pthread_t id[NUM];
    size_t i, j = 0;
    time_t start, end;
    int count = 0;
    start = time(NULL);
    for (i = 0; i < NUM; i++)
    {
        while (pthread_create(&id[i], NULL, routine, (void *)i) != 0)
        { 
            pthread_join(id[j], NULL);
            ++j;
        }
    }
    
    end = time(NULL);
    sleep(5);
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
