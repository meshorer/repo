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
int ComparePasswords(FILE *fp,char *password);

#define MAX_LENGTH 32
#define USERS_DB "/home/daniel/git/cyber/authentication/db_file.txt"


/*
	function AuthAddUser:
	1. check for invalid chars, too long
	2. open the file for reading and appending ("a+")
	3. check if the username does not already exist. - username max size is MAX_LENGTH, 
	
	a while not at the EOF
	b use fgets for 32 to get the user name
	c check lentgh of the user-name until ':'
	d memcpy the user-name to a different buffer
	e now compare the user-name recieved and the user-name from the file
	f if thereis a match - break and send error that username exists.
	g else - go to next line (with getc until '\' - next line)
	h repeat from b
	
	
	4. append the username and password in a new line at the end of the file (seperated with ':')
	5. close the file and returns success
*/
int AuthAddUser(const char *username, const char *password)
{
	
	char *hashed_password = NULL;
	int result = 0;
	
	assert(NULL != username);
	assert(NULL != password);
	
	
	result = CheckConditions(username,password);
	if (0 != result)      							/* check for invalid chars, too long */	
	{
		return result;
	}		
	
	result = CheckIfUsernameExists(username);
	if (0 != result)     							/* check if user name exists */	
	{
		return result;
	}		
	

	hashed_password = crypt(password, "$1$salt");				/* hash the password with this hash */	
	
	result = AppendUserToFile(username,hashed_password);
	if (0 != result)     							/* check that appends user worked */	
	{
		return result;
	}		
	

	return 0;
}





int AuthDeleteUser(const char *username)
{


	return 0;
}






int AuthAuthenticator(const char *username, const char *password)
{
	char *hashed_password = NULL;
	int result = 0;
	int num_users = 0;
	int i = 0;
	int is_found = 0;
	
	char *check_user_name = NULL;
	char current_character = '0';
	int count_username = 0;
	FILE *fp = NULL;
	
	assert(NULL != username);
	assert(NULL != password);
	
	result = CheckConditions(username,password);
	if (0 != result)      							/* check for invalid chars, too long */	
	{
		return result;
	}
	
	check_user_name = malloc(MAX_LENGTH);
	
	fp = fopen(USERS_DB, "r");  
	if (NULL == fp)
	{
		return -1;
	}
	
	current_character = getc(fp);
	
	num_users = CountUsers();
	for (i = 0; i < num_users; ++i)
	{
		num_users = CountUsers();
		count_username = ExtractUsernameFromFile(fp,current_character);
		
		if (0 == count_username &&  0 == num_users)
		{
			free(check_user_name);
			return 1;
		}
		
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
			is_found = 1;
			break;
		}
		
		while(current_character != '\n')
		{
			current_character = getc(fp);
		}
		
		current_character = getc(fp);
	}		
	if (0 == is_found)
	{
		return 1;
	}
	
	current_character = getc(fp);
	result = ComparePasswords(fp,(char *)password);
	free(check_user_name);
	fclose(fp);
	return result;
}




int CheckConditions(const char *username, const char *password)
{
	char *begin_username = (char *)username;
	char *begin_password = (char *)password;
	
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
	
	username = begin_username;
	password = begin_password;
	
	return 0;
}


/*     */
int CheckIfUsernameExists(const char *username)
{
	
	char *check_user_name = NULL;
	char current_character = '0';
	int count_username = 0;
	FILE *fp = NULL;
	int num_users = 0;
	check_user_name = malloc(MAX_LENGTH);
	

	fp = fopen(USERS_DB, "r");  
	if (NULL == fp)
	{
		return -1;
	}
	
	current_character = getc(fp);
	
	while (current_character != EOF)
	{
	
		num_users = CountUsers();
		count_username = ExtractUsernameFromFile(fp,current_character);
		
		if (0 == count_username &&  0 == num_users)
		{
			free(check_user_name);
			return 0;
		}
		
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


int ComparePasswords(FILE *fp,char *password)
{
	
	char *file_hash = NULL;
	char *check_password_hash = NULL;
	
	int counter_salt = 0;
	char *salt = NULL;
	size_t len = 0;
	file_hash = malloc(MAX_LENGTH);
	if(NULL == fgets(file_hash,MAX_LENGTH,fp))
	{
			free(file_hash);
			return 2;
	}
	len = strlen(file_hash);
	check_password_hash = malloc(len+1);
	salt = malloc(MAX_LENGTH);
	while (NULL != strchr(file_hash,'$'))
	{
		*salt = *file_hash;
		++salt;
		++file_hash;
		++counter_salt;
	}
	salt-=counter_salt;
	
	check_password_hash = crypt(password, salt);
	check_password_hash+=counter_salt;
	if (0 != strncmp(check_password_hash,file_hash,len - counter_salt-1))
	{
		return 3;
	}

	return 0;
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
