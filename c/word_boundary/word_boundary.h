#include <stdio.h>
#include <string.h>
#include <assert.h>


#define WORD_SIZE sizeof(void *)

void *Memset(void *s, int c, size_t n);
void *Memcpy(void *dest, const void *src, size_t n);
void *Memmove(void *dest, const void *src, size_t n);
