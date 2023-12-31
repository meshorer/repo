#include <stddef.h> /* size_t */
#include <assert.h> /* assert */
#include <stdio.h> 
#include <stdlib.h>
#include <string.h> /* strncmp */
#include <stdlib.h> /* malloc */
#include "stack.h"

typedef struct node Node;



int Fibonacci(int element_index);
int FibonacciRecursion(int element_index);
int Fibonacciyar(int element_index);

Node *FlipList(Node *node);
size_t StrlenRecursion(const char *s);
int StrcmpRecursion(const char *s1, const char *s2);
char *StrcpyRecursion(char *dest, const char *src);
char *StrcatRecursion(char *dest, const char *src);
char *StrstrRecursion(const char *haystack, const char *needle);
char *StrstrRecursionWIthSize(const char *haystack, const char *needle, size_t size);
stack_t *CheckStack(stack_t *stack, size_t size);
stack_t *SortRecursive(stack_t *stack);
