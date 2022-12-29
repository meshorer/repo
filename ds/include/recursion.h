#include <stddef.h> /* size_t */
#include <assert.h> /* assert */
#include <stdio.h> 
#include <stdlib.h>
#include <stdlib.h> /* malloc */

typedef struct node Node;

int Fibonacci(int element_index);
int FibonacciRecursion(int element_index);
int Fibonacciyar(int element_index);

Node *FlipList(Node *node);
size_t StrlenRecursion(const char *s);
int StrcmpRecursion(const char *s1, const char *s2);
char *strcpyRecursion(char *dest, const char *src);
char *strcatRecursion(char *dest, const char *src);
