#ifndef __FILES_H__
#define __FILES_H__


#include <stdio.h>  
#include <string.h>  /* for strcmp*/
#include <stdlib.h>  /* for exit*/

enum test {FAIL, SUCCESS};

struct operation{
	
	char * command_name;
	int (*cmp)(char*, char*);
	enum test (*exec)(char*,char*);
};


int Cmp(char *buffer, char *command_name);
enum test Rm(char *buffer, char *file_name);
enum test Esc(char *str1, char *str2);
enum test Count(char *buffer, char *file_name);
int Cmp_begin(char *buffer, char *file_name);
enum test Begin(char *str1, char *str2);
enum test Exec(char* buffer, char *file_name);


#endif
