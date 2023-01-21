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
#define INDEX_CHECK 10
#define USER_NOT_EXIST 1
#define MAX_SIZE 100

int AuthAddUser(const char *username, const char *password)
{
	
	char *hashed_password = NULL;	
	int result = 0;
	
	assert(NULL != username);
	assert(NULL != password);
	
	result = CheckConditions(username,password);
	if (0 != result)      							
	{
		return result;
	}		
	
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
	
	return 0;
}

int AuthDeleteUser(const char *username)
{

	int index_user = 0;
	int result = 0;
	int num_users = 0;

	assert(NULL != username);
	
	num_users = CountUsers();

	index_user = CheckIfUsernameExists(username);			/* if user exists, get it's line number in the file */	
	
	if(0 == index_user)
	{
		return USER_NOT_EXIST;
	}
	if (index_user < INDEX_CHECK)					/* INDEX_CHECK is to check whether the result is a line number or an error value */	
	{
		return index_user;
	}
	index_user-=INDEX_CHECK;
	result = DeleteUser(index_user,num_users);
	
	return result;
}


int AuthAuthenticator(const char *username, const char *password)
{

	int index_user = 0;
	int result = 0;
	int num_users = 0;

	assert(NULL != username);
	
	num_users = CountUsers();

	index_user = CheckIfUsernameExists(username);
	
	if(0 == index_user)
	{
		return USER_NOT_EXIST;
	}
	
	if (index_user < INDEX_CHECK)					/* INDEX_CHECK is to check whether the result is a line number or an error value */	
	{
		return index_user;
	}
	index_user-=INDEX_CHECK;
	result = ComparePasswords((char *)password,index_user,num_users);
	
	return result;
	
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


int CountUsers()      									/*  function to count lines in the file */
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

int CheckIfUsernameExists(const char *username)
{
	
	char *check_user_name = NULL;
	char current_character = '0';
	int count_username = 0;
	FILE *fp = NULL;
	int num_users = 0;
	int i = 0;
	
	fp = fopen(USERS_DB, "r");  
	if (NULL == fp)
	{
		return 2;
	}
	
	current_character = getc(fp);
	
	num_users = CountUsers();							/* get the number of users in the file */
	if( 0 == num_users)
	{
		return 0;
	}
	check_user_name = malloc(MAX_LENGTH);
	for (i = 0; i < num_users; ++i)							/* iterate for each line */
	{
	
		num_users = CountUsers();
		count_username = ExtractUsernameFromFile(fp,current_character); 
		
		if(fseek(fp,-(count_username+1),SEEK_CUR) != 0)				/* rewind to the begining of line | +1 because of the ':' */
		{
			free(check_user_name);
			return 2;
		}
		
		check_user_name = realloc(check_user_name,count_username+1);    	/* +1 for null-terminator */		
		
		if(NULL == fgets(check_user_name,count_username+1,fp))
		{
			free(check_user_name);
			return 2;
		}
	
		if (0 == strncmp(check_user_name,username,count_username) && count_username == (int)strlen(username))   /* compare usernames */
		{
			printf("found match for user %s\n",username);
			free(check_user_name);
			return i + INDEX_CHECK;						/* INDEX_CHECK will be discriminated in the caller function */
		}
		
		while(current_character != '\n')					/*  get to the end of the line */
		{
			current_character = getc(fp);
		}
		
		current_character = getc(fp);						/*  one more getc to go to next line */
	
	}
		
	free(check_user_name);
	fclose(fp);

	return 0;
}

int ExtractUsernameFromFile(FILE *fp,char current_character) 				/*  function to count the numer of lettes in username */
{
	
	int count_username = 0;
	
	while (':' != current_character)
	{
		++count_username;
		current_character = getc(fp);
	}
	
	return count_username;

}

int DeleteUser(int i,int num_users)
{

	int j = 0;
	FILE * tmp_fp = NULL;
	FILE *fp = NULL;
	char *line = NULL;
	tmp_fp = fopen(USERS_TMP, "a+");
	fp = fopen(USERS_DB,"a+");
	
	line = malloc(MAX_SIZE);
		
	for (j = 0; j < num_users; ++j)
	{
		if(NULL == fgets(line,MAX_SIZE,fp))					/* fgets will stop at end of line, because MAX_SIZE is bigger */
		{
			free(line);
			return 2;
		}
		if(j != i)								/*  print all the lines to the tmp file, except the recieved index line */	
		{
			fprintf(tmp_fp, "%s", line);
		}
	}
	free(line);
	
	fclose(fp);
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
	
	return 0;
}

int ComparePasswords(char *password, int i,int num_users)
{

	int j = 0;
	FILE *fp = NULL;
	
	char *file_hash = NULL;
	char *begin_line = NULL;
	char *check_password_hash = NULL;
	
	int counter_salt = 0;
	char *salt = NULL;
	
	fp = fopen(USERS_DB,"r");
	file_hash = malloc(MAX_SIZE);
	begin_line = file_hash;								/*  because we advance the file_hash, to later on free it we need to save its starting point */
	for (j = 0; j < num_users; ++j)
	{
		if(j == i)
		{
			break;
		}
		
		if(NULL == fgets(file_hash,MAX_SIZE,fp))
		{
			free(file_hash);
			return 2;
		}	
	}
	
	if(NULL == fgets(file_hash,100,fp))
	{
		free(file_hash);
		return 2;
	}
	
	file_hash = strchr(file_hash, ':') + 1;						/*  skip the username */
	while (NULL != strchr(file_hash,'$'))         					/*  extract number of letters of the salt */
	{
		++file_hash;
		++counter_salt;
	}
	salt = malloc(counter_salt+1);							/*  allocate for sait it's exact size + null terminator */
	file_hash-=counter_salt;							/*  rewind the pinter to include the salt */
	memcpy(salt,file_hash,counter_salt);
	salt+=counter_salt;
	*salt = '\0';									/* make sure salt will end with null-terminator ( Johnny - it didnt work without it) */
	salt-=counter_salt;

	check_password_hash = crypt(password, salt);					/* crypt the password recieved to function with the extracted salt */
	
	if (0 != strncmp(check_password_hash,file_hash,strlen(file_hash) -1)) 		/* -1 because of the '/n' at the end of the line */
	{
		file_hash = begin_line;							/*  get file_hash to it's starting point in order to free it */
		free(file_hash);
		free(salt);
		return 3;
	}
	file_hash = begin_line;
	free(file_hash);

	free(salt);
	return 0;
}


