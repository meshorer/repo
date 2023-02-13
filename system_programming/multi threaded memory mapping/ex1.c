#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int global_var = 8;


void *routine(void *arg)
{
    int i = 0;
    char *str = (char *)malloc(50);
    sleep(2);
    printf(" i am a thread %p\n", &global_var);

    return 0;
}

int main()
{
    char *str_main = (char *)malloc(50);
    pthread_t id = 0;
    pthread_create(&id,NULL,routine,NULL);
    pthread_join(id,NULL);

    return 0;
}