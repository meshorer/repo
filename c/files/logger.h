#ifndef __FILES_H__
#define __FILES_H__


#include <stdio.h>  
#include <string.h>  /* for strcmp*/
#include <stdlib.h>  /* for exit*/



struct operation{
	
	char * command_name;
	int (*cmp)(char*, char*);
	int (*exec)(char*,char*);
};


int Cmp(char *buffer, char *command_name);
int Rm(char *buffer, char *file_name);
int Esc(char *str1, char *str2);
int Count(char *buffer, char *file_name);
int Cmp_3(char *buffer, char *file_name);
int Begin(char *str1, char *str2);
int Exec(char* buffer, char *file_name);


#endif
