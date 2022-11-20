#include "logger.h"

int Cmp(char *buffer, char *command_name)
{
	int res;
	res = strcmp(buffer, command_name);
	if ( 10 != res)
	{
		res = 0;
		
	}
	return res;

}

int Rm(char *buffer, char *file_name)
{
	int res = 0;
	res = remove(file_name);
	if (0 == res)
	{
		res = 1;
	}
	return res;	
}

int Esc(char *str1, char *str2)
{
	exit(0);
}

int Count(char *buffer, char *file_name)
{
	FILE *fp = NULL;
	char chr;
	int count = 0;
	fp = fopen(file_name,"r");
	if (fp == NULL)
    	{
        	printf("Could not open file %s", file_name);
        	return 1;
    	}
    	chr = getc(fp);
    	while (chr != EOF)
    	{
    		if (chr == '\n')
    		{
    			count+=1;
    		}
    		chr = getc(fp);
    	}
	fclose(fp);
	printf("the file has %d lines\n", count);
	return 1;
}

int Cmp_3(char *buffer, char *command_name)
{

	int res;
	char chr;
	chr = buffer[0];
    	if ('<' == chr)
    	{
    		res = 1;
    		
    	}
	else
	{
		res = 0;
	}
	return res;

}


int Begin(char* buffer, char *file_name)
{
	FILE *fp = NULL;
	FILE * tmp_fp = fopen("tmp.txt", "a+");
	char chr;
	fp = fopen(file_name,"r");
	
	if (fp == NULL)
    	{
        	printf("Could not open file %s\n", file_name);
        	return 1;
    	}
    	++buffer;
    	fprintf(tmp_fp, "%s", buffer);
    	
    	chr = fgetc(fp);
    	while (chr != EOF)
    	{
    		fputc(chr,tmp_fp);
    		chr = fgetc(fp);
    	}
    	Rm(buffer, file_name);
    	rename("tmp.txt",file_name);
	fclose(fp);  
	fclose(tmp_fp);    
	return 1;
}

int Exec(char* buffer, char *file_name)
{

	FILE *fp = NULL;
	fp = fopen(file_name, "a+");  
	if (NULL == fp)
	{
		printf("error didnt open file\n");
		return 1 ;
	}
	
    	fprintf(fp, "%s", buffer);
	fclose(fp);   
       	return 1;	 	
}


int main(int argc, char *argv[])
{  

    	char buffer[1000];
	int res = 0;
	int i = 0;
	struct operation op[5];
	op[0].command_name  = "-remove";
	op[0].cmp = Cmp;
	op[0].exec = Rm;
	op[1].command_name  = "-escape";
	op[1].cmp = Cmp;
	op[1].exec = Esc;
	op[2].command_name  = "-count";
	op[2].cmp = Cmp;
	op[2].exec = Count;
	op[3].command_name  = "<";
	op[3].cmp = Cmp_3;
	op[3].exec = Begin;
	op[4].command_name  = "append";
	op[4].cmp = Cmp;
	op[4].exec = Exec;
	printf("ready to start typing? :)\n");
	while ( 1)
	{
		fgets( buffer, 1000, stdin);

			while (0 == res && i < 5)
			{
				res = op[i].cmp(buffer,op[i].command_name);
				i++;
			}
		i--;
		/*if ( 0 == res)
		{
		
			op[4].exec(buffer, argv[1]);
		}
		else
		{
			res = op[i].exec(buffer,argv[1]); 
		}
*/
		res = op[i].exec(buffer,argv[1]);
		i = 0;
		res = 0;
       	}	
       	
       	

	return 0;
}  

