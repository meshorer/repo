#include <stdio.h>
#include <string.h>
#include <stdlib.h>

size_t StrLen(const char *s);
char *StrCpy(char *dest, const char *src);
char *StrNcpy(char *dest, const char *src, size_t n);
int StrCmp (const char* str1, const char* str2);
int StrNcmp(const char *s1, const char *s2, size_t n);
int StrCasecmp(const char *str1, const char *str2);
char *StrChr(const char *s, int c);
char *StrDup(const char *s);
char *StrCat(char *dest, const char *src);
char *StrNcat(char *dest, const char *src, size_t n);
char *StrStr(const char *haystack, const char *needle);
