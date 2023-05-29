#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
    to compile with clang (including fuzzing) - different options:

    clang -g -fsanitize=fuzzer exc2.c -o exc2

    clang -g -fsanitize=fuzzer,memory exc2.c -o exc2

    clang -g -fsanitize=fuzzer,address exc2.c -o exc2
*/


int DoSomethingWithData(const char *Data, size_t Size)  /* the function to test   */
{
    char *buffer = calloc(64, sizeof(*buffer));

    if (!buffer)
    {
        printf("Allocation failed\n");
        return -1;
    }

    strcpy(buffer, Data);

    printf("%s\n", buffer);

    return 0;
}

int LLVMFuzzerTestOneInput(const char *Data, size_t Size) /* wrapper to main: data/size as argv/argc  */
{
    DoSomethingWithData(Data, Size);
    return 0;
}