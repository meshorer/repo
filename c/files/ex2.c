#include <stdio.h>  
#include <string.h>  


struct operation{
	
	char * command_name;
	int (*cmp)(char*, char*);
	int (*exec)(char*,char*);
};

int Cmp(char *buffer, char *command_name)
{
	int res;
	res = strcmp(buffer, command_name);
	printf("command is %s , buffer is %s ", command_name, buffer);
	if ( 10 == res)
	{
		printf("match found\n");
		
	}
	else
	{
		printf("no match for strings!\n", buffer, command_name);
		res = 0;
	}
	printf("res in cmp is now %d\n", res);
	printf("\n");
	return res;

}

int Rm(char *buffer, char *file_name)
{
	int res = 0;
	res = remove(file_name);
	if (0 == res)
	{
		printf("file removed\n");
		res = 1;
	}
	return res;	
}

int Esc(char *str1, char *str2)
{
	exit(0);
}

int Count(char *str1, char *str2)
{
	return 1;
}

int Begin(char *str1, char *str2)
{
	return 1;
}

int Exec(char* buffer, char *file_name)
{
	FILE *fp;
	fp = fopen(file_name, "a+");  
	if (NULL == fp)
	{
		printf("error didnt open file\n");
		return;
	}
		
    	
    	fprintf(fp, "%s", buffer);
	fclose(fp);   
       	return;	 	
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
	op[3].cmp = Cmp;
	op[3].exec = Begin;
	op[4].command_name  = "append";
	op[4].cmp = Cmp;
	op[4].exec = Exec;
	printf("ready to start typing? :)\n");
	while ( 1)
	{
		fgets( buffer, 1000, stdin);
		printf("string recieved - %s \n", buffer);
		printf("before cmp loop res is %d\n", res);
			while (0 == res && i < 5)
			{
				printf("send to compare struct number %d \n", i);
				res = op[i].cmp(buffer,op[i].command_name);
				i++;
			}
		i--;
		printf("now i is %d\n", i);
		printf("after second loop\n");
		printf("now res is %d\n", res);
		if ( 0 == res)
		{
		
			op[4].exec(buffer, argv[1]);
		}
		else
		{
			printf("i am here\n");
			res = op[i].exec(buffer,argv[1]); /* remove should include argv[1]*/
		}

		i = 0;
		res = 0;
       	}	
       	
       	

	return 0;
}  

    
    
  
