#include <stdio.h>
#include <stdlib.h>  /* malloc */
#include <pthread.h> /* pthread_create */
#include <errno.h>

#define THREADS_COUNT 3

int global_var = 5;
char global_str[] = "hello from global str";

void *RoutineFunc(void *arg)
{
    static __thread int tls_var;
    int local_thread_int = 3;
    char local_thread_str[] = "hello from thread";
    int *dynamic_int = (int *)malloc(sizeof(int));
    if (dynamic_int == NULL)
    {
        perror("malloc-failed");
    }

    *dynamic_int = 20;

    while (local_thread_int > 0)
    {
        printf("%d\n", --local_thread_int);
    }

    printf("\nthe address of tls_var is:                    %p\n", &tls_var);
    printf("the address of local_thread_int is:           %p\n", (void*)&local_thread_int);
    printf("the address of local_thread_str is:           %p\n", (void*)&local_thread_str);
    printf("the address of dynamic_int(var in stack) is:  %p\n", (void*)&dynamic_int);
    printf("the address of dynamic_int(bytes in heap) is: %p\n", dynamic_int);
    printf("the address of routine func is:               %p\n", &RoutineFunc);
    return arg;

    free(dynamic_int);
}

int main()
{
    int local_main = 10;
    pthread_t tid[3] = {0};
    size_t i = 0;

    for (i = 0; i < THREADS_COUNT; i++)
    {
        pthread_create(&tid[i], NULL, RoutineFunc, NULL);
        printf("thread %ld id is: %d\n", i, tid[i]);
    }

    for (i = 0; i < THREADS_COUNT; i++)
    {
        pthread_join(tid[i], NULL);
    }

    puts("\n*********************************************************************\n");
    printf("the address of global_str is:                 %p\n", (void*)&global_str);
    printf("the address of global_var is:                 %p\n", (void*)&global_var);
    printf("the address of main func is:                  %p\n", &main);
    printf("the address of local main var is:             %p\n", (void*)&local_main);
    printf("the address of tid arr is:                    %p\n", (void*)&tid)       ;       
    printf("the address of local size_t i is:             %p\n", (void*)&i);


    return 0;
}



