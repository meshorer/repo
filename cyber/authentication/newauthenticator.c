 #include <crypt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "authenticator.h"

int CheckConditions(const char *username, const char *password);
int CheckIfUsernameExists(const char *username);
int AppendUserToFile(const char *username,const char *hashed_password);
int ExtractUsernameFromFile(FILE *fp,char current_character);
int CountUsers();
int ComparePasswords(char *password,int i,int num_users);
int IterateUsers(FILE *fp,char current_character,char *username);
int DeleteUser(int i,int num_users);
int CheckUser(FILE *fp,const char *username);

#define MAX_LENGTH 32
#define USERS_DB "/home/daniel/git/cyber/authentication/db_file.txt"
#define USERS_TMP "/home/daniel/git/cyber/authentication/tmp.txt"

int AuthAddUser(const char *username, const char *password)
{
	
	char *hashed_password = NULL;	
	int result = 0;
	FILE *fp = NULL;
	
	
	assert(NULL != username);
	assert(NULL != password);
	
	result = CheckConditions(username,password);
	if (0 != result)      							
	{
		return result;
	}		
	
	fp = fopen(USERS_DB, "r");  
	if (NULL == fp)
	{
		return -1;
	}
	
	/*result = CheckUser(fp,username);*/
	result = CheckIfUsernameExists(username);
	if ( 0 != result)     							
	{
		return result;
	}	
	
	hashed_password = crypt(password, "$1$salt");				
	
	result = AppendUserToFile(username,hashed_password);
	if (0 != result)     							/* check that appends user worked */	
	{
		
		return result;
	}		
	
	fclose(fp);
	return 0;
}

int CheckConditions(const char *username, const char *password)
{
	
	if (31 < strlen(username) || 31 < strlen(password))				/* strlen doesn't include the null-terminator  */
	{
		return 4;
	}
	
	while (*username)
	{
		if(' ' == *username || '\n' == *username || ':' == *username)
		{
			return 3;
		}
		
		++username;
	}
	
	while (*password)
	{
		if(' ' == *password || '\n' == *password || ':' == *password)
		{
			return 3;
		}
		
		++password;
	}
	
	return 0;
}


int AppendUserToFile(const char *username,const char *hashed_password)
{

	FILE *fp = NULL;
	
	fp = fopen(USERS_DB, "a");  
	if (NULL == fp)
	{
		return 2;
	}
	
	fprintf(fp, "%s", username);
	fprintf(fp, "%s", ":");
	fprintf(fp, "%s\n", hashed_password);
	
	fclose(fp);
	
	return 0;
}

int ExtractUsernameFromFile(FILE *fp,char current_character)
{
	
	int count_username = 0;
	
	while (':' != current_character)
	{
		++count_username;
		current_character = getc(fp);
	}
	
	return count_username;

}

int CountUsers()      				/*  Basically count lines.. */
{
	FILE *fp = NULL;
	char chr;
	int count_lines = 0;
	fp = fopen(USERS_DB,"r");
	if (fp == NULL)
    	{
        	return 2;
    	}
    	chr = getc(fp);
    	while (chr != EOF)
    	{
    		if (chr == '\n')
    		{
    			count_lines+=1;
    		}
    		chr = getc(fp);
    	}
    	
    	return count_lines;
	fclose(fp);	
}


int DeleteUser(int i,int num_users)
{

	int j = 0;
	FILE * tmp_fp = NULL;
	FILE *fp = NULL;
	char *line = NULL;
	tmp_fp = fopen(USERS_TMP, "a+");
	fp = fopen(USERS_DB,"a+");
	line = malloc(100);
	
	printf("in delete function, i is : %d and num_users is %d\n",i,num_users);
	
	
	for (j = 0; j < num_users; ++j)
	{
		if(NULL == fgets(line,100,fp))
		{
			return 2;
		}
		if(j != i)
		{
			fprintf(tmp_fp, "%s", line);
		}
	}
	free(line);
	
	fclose(fp);
	printf("check or\n");
	if (0 != remove(USERS_DB))
	{
		fclose(tmp_fp);
		return 2;
	}
	
	fclose(tmp_fp);
	if (0 != rename(USERS_TMP,USERS_DB))
	{
		return 2;
	}
	
	printf("check free\n");
	
	return 0;
}


int AuthDeleteUser(const char *username)
{

	int index_user = 0;
	int result = 0;
	int num_users = 0;
	FILE *fp = NULL;
	fp = fopen(USERS_DB, "r");  
	if (NULL == fp)
	{
		return -1;
	}
	
	num_users = CountUsers();
	index_user = CheckUser(fp,username);
	if ( 0 <= index_user)
	{
		result = DeleteUser(index_user,num_users);
		if (0 == result)
		{
			fclose(fp);
			return 0;
		}
	}		
		
	fclose(fp);	
	return 3;
}


int AuthAuthenticator(const char *username, const char *password)
{
	int index_user = 0;
	int result = 0;
	int num_users = 0;
	FILE *fp = NULL;
	fp = fopen(USERS_DB, "r");  
	if (NULL == fp)
	{
		return -1;
	}
	
	num_users = CountUsers();
	index_user = CheckUser(fp,username);
	if ( 0 <= index_user)
	{
		result = ComparePasswords((char *)password,index_user,num_users);
		if (0 == result)
		{
			fclose(fp);
			return 0;
		}
	}		
		
	fclose(fp);	
	return 3;
}

int ComparePasswords(char *password, int i,int num_users)
{

	int j = 0;
	FILE *fp = NULL;
	
	char *file_hash = NULL;
	char *check_password_hash = NULL;
	
	int counter_salt = 0;
	char *salt = NULL;
	size_t len = 0;
	fp = fopen(USERS_DB,"r");
	
	printf("in compare function, i is : %d and num_users is %d\n",i,num_users);
	
	file_hash = malloc(100);
	for (j = 0; j < num_users; ++j)
	{
		if(j == i)
		{
			break;
		}
		
		if(NULL == fgets(file_hash,100,fp))
		{
			return 2;
		}	
	}
	
	if(NULL == fgets(file_hash,100,fp))
	{
		free(file_hash);
		free(check_password_hash);
		return 2;
	}
	printf("file hash is: %s\n",file_hash);
	
	
	while (NULL != strchr(file_hash,':'))
	{
		++file_hash;
	}
	printf("file after while hash is: %s\n",file_hash);
	while (NULL != strchr(file_hash,'$'))
	{
		++file_hash;
		++counter_salt;
	}
	
	salt = malloc(counter_salt +1);
	file_hash-=counter_salt;
	printf("file with salt is: %s\n",file_hash);
	/*memcpy(salt,file_hash,counter_salt);*/
	strncpy(salt,file_hash,counter_salt);
	
	printf("salt is : %s\n",salt);	
	check_password_hash = crypt(password, salt);
	len = strlen(file_hash);
	
	printf("check_password_hash is: %s\n",check_password_hash);
	if (0 != strncmp(check_password_hash,file_hash,len -1))
	{
		/*free(file_hash);*/
		printf("enter?\n");
		free(salt);
		return 3;
	}
	/*free(file_hash);*/
	printf("checking: check_password_hash is:%s\n",check_password_hash);
	free(salt);
	return 0;
}

int CheckUser(FILE *fp,const char *username)
{

	char *check_user_name = NULL;
	char current_character = '0';
	int count_username = 0;
	
	int num_users = 0;
	int i = 0;
	int found_match = 0;
	check_user_name = malloc(MAX_LENGTH);
	
	current_character = getc(fp);
	
	num_users = CountUsers();
	if( 0 == num_users)
	{
		/*free(check_user_name);*/
		return 0;
	}
	
	for (i = 0; i < num_users; ++i)
	{
	
		num_users = CountUsers();
		count_username = ExtractUsernameFromFile(fp,current_character);
		
		if(fseek(fp,-(count_username+1),SEEK_CUR) != 0)			/* return to the begining | +1 because of the ':' */
		{
			free(check_user_name);
			return 2;
		}
		
		check_user_name = realloc(check_user_name,count_username+1);    			
		
		if(NULL == fgets(check_user_name,count_username+1,fp))
		{
			/*free(check_user_name);*/
			return 2;
		}
	
		if (0 == strncmp(check_user_name,username,count_username) && count_username == (int)strlen(username))
		{
			found_match = 1;
			/*free(check_user_name);*/
			break;
		}
		
		while(current_character != '\n')
		{
			current_character = getc(fp);
		}
		
		current_character = getc(fp);
	}
	
	free(check_user_name);
	if (1 == found_match)
	{
		return i;
	}
	else
	{
		return -1;
	}
	
}

int CheckIfUsernameExists(const char *username)
{
	
	char *check_user_name = NULL;
	char current_character = '0';
	int count_username = 0;
	FILE *fp = NULL;
	int num_users = 0;
	int i = 0;
	
	check_user_name = malloc(MAX_LENGTH);
	
	fp = fopen(USERS_DB, "r");  
	if (NULL == fp)
	{
		return -1;
	}
	
	current_character = getc(fp);
	
	num_users = CountUsers();
	if( 0 == num_users)
	{
		free(check_user_name);
		return 0;
	}
	
	for (i = 0; i < num_users; ++i)
	{
	
		num_users = CountUsers();
		count_username = ExtractUsernameFromFile(fp,current_character);
		
		if(fseek(fp,-(count_username+1),SEEK_CUR) != 0)			/* return to the begining | +1 because of the ':' */
		{
			free(check_user_name);
			return 2;
		}
		
		check_user_name = realloc(check_user_name,count_username+1);    			
		
		if(NULL == fgets(check_user_name,count_username+1,fp))
		{
			free(check_user_name);
			return 2;
		}
	
		if (0 == strncmp(check_user_name,username,count_username) && count_username == (int)strlen(username))
		{
			free(check_user_name);
			return 1;
		}
		
		while(current_character != '\n')
		{
			current_character = getc(fp);
		}
		
		current_character = getc(fp);
	
	}
		
	free(check_user_name);
	fclose(fp);

	return 0;
}

