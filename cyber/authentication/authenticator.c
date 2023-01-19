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
int IterateUsers(FILE *fp,char current_character,char *username);
int DeleteUser(int i,int num_users);

int CopyAuthDeleteUser(const char *username);

#define MAX_LENGTH 32
#define USERS_DB "/home/daniel/git/cyber/authentication/db_file.txt"
#define USERS_TMP "/home/daniel/git/cyber/authentication/tmp.txt"


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
	if (0 != result)      							
	{
		return result;
	}		
	
	result = CheckIfUsernameExists(username);
	if (0 != result)     							
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
	/*
		1. check that a user exists at all 
		2. if exists, remember the "i" because this is the line number it stoped.
		3. create tmp file and append the lines from 1 to i(exclude),and from i+1 to num
		4. now rewrite yout original file with the content of tmp
		5. remove the tmp
	*/
	int result = 0;
	int num_users = 0;
	int i = 0;
	
	char current_character = '0';
	FILE *fp = NULL;
	
	
	assert(NULL != username);
	
	if (0 != result)      							/* check for invalid chars, too long */	
	{
		return result;
	}
	
	fp = fopen(USERS_DB, "r");  
	if (NULL == fp)
	{
		
		return -1;
	}
	
	current_character = getc(fp);
	
	num_users = CountUsers();
	if( 0 == num_users)
	{	
		return 1;
	}
	
	for (i = 0; i < num_users; ++i)
	{
		result = IterateUsers(fp,current_character,(char *)username);
		if (10 == result && EOF == current_character)
		{
			return 1;
		}
		
		if(0 == result)
		{
			break;
		}
	}
	
	/*if (EOF == current_character)   
	{
		return 1;
	}*/
	
	if (0 != result)
	{
		return result;
	}		
	
	current_character = getc(fp);
	fclose(fp);
	result = DeleteUser(i,num_users);
	printf("the result for delete is: %d",result);

	
	return result;
}






int AuthAuthenticator(const char *username, const char *password)
{
	int result = 0;
	int num_users = 0;
	int i = 0;
	
	char current_character = '0';
	FILE *fp = NULL;
	
	
	assert(NULL != username);
	assert(NULL != password);
	
	result = CheckConditions(username,password);
	if (0 != result)      							/* check for invalid chars, too long */	
	{
		
		return result;
	}
	
	fp = fopen(USERS_DB, "r");  
	if (NULL == fp)
	{
		
		return -1;
	}
	
	current_character = getc(fp);
	
	num_users = CountUsers();
	if( 0 == num_users)
	{	
		return 1;
	}
	
	
	if (EOF == current_character)   /* didnt find  any user name with that name */
	{
		
		return 1;
	}
	
	if (0 != result)
	{
		
		printf("problem\n");
		return result;
	}		
	printf("proceed to compare hashes\n");
	current_character = getc(fp);
	result = ComparePasswords(fp,(char *)password);
	printf("comparison works:\n");
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
			free(check_password_hash);
			return 2;
	}
	printf("file hash is: %s\n",file_hash);
	len = strlen(file_hash);
	
	while (NULL != strchr(file_hash,'$'))
	{
		++file_hash;
		++counter_salt;
	}
	salt = malloc(counter_salt +1);
	file_hash-=counter_salt;
	memcpy(salt,file_hash,counter_salt);
		
	check_password_hash = crypt(password, salt);
	
	printf("file hash is: %s\n",file_hash);
	printf("check_password_hash is: %s\n",check_password_hash);
	if (0 != strncmp(check_password_hash,file_hash,len -1))
	{
		free(file_hash);
		free(salt);
		return 3;
	}
	free(file_hash);
	printf("checking: check_password_hash is:%s\n",check_password_hash);
	free(salt);
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


int IterateUsers(FILE *fp,char current_character,char *username)
{
	int count_username = 0;
	char *check_user_name = NULL;
	int offset_fd = 0;
	int k = 0;
	
	check_user_name = malloc(MAX_LENGTH);
	
	count_username = ExtractUsernameFromFile(fp,current_character);
	
	if(fseek(fp,-(count_username+1),SEEK_CUR) != 0)			/* return to the begining | +1 because of the ':' */
	{
		printf("balagan1\n");
		free(check_user_name);
		return 2;
	}
	
	check_user_name = realloc(check_user_name,count_username+1);    			
	
	if(NULL == fgets(check_user_name,count_username+1,fp))
	{
		printf("balagan2\n");
		free(check_user_name);
		return 2;
	}
	printf("check_user_name is %s\n",check_user_name);
	printf("username is %s\n",username);
	if (0 == strncmp(check_user_name,username,count_username) && count_username == (int)strlen(username))
	{
		printf("found match for :%s\n",check_user_name);
		free(check_user_name);
		return 0;
	}
	printf("balagan3\n");
	while(current_character != '\n')
	{
		current_character = getc(fp);
		offset_fd++;
	}
	
	current_character = getc(fp);
	free(check_user_name);
	offset_fd+=count_username;
	printf("offset_fd is: %d",offset_fd);
	for (k = 0; k < offset_fd; ++k)
	{
		if(fseek(fp,1,SEEK_CUR) != 0)			
		{
			printf("balagan1\n");
			free(check_user_name);
			return 2;
		}
	}
	printf("done iterating\n");
	
	
	return 10;
}



int DeleteUser(int i,int num_users)
{
/*
	a. create tmp file and append the lines from 1 to i(exclude),and from i+1 to num
	b. now rewrite yout original file with the content of tmp
	c. remove the tmp
*/
	
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


int CopyAuthDeleteUser(const char *username)
{

	char *check_user_name = NULL;
	char current_character = '0';
	int count_username = 0;
	FILE *fp = NULL;
	int num_users = 0;
	int i = 0;
	int found_match = 0;
	int result = 0;
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
		/*free(check_user_name);*/
		return 0;
	}
	
	for (i = 0; i < num_users; ++i)
	{
	
		num_users = CountUsers();
		count_username = ExtractUsernameFromFile(fp,current_character);
		
		if(fseek(fp,-(count_username+1),SEEK_CUR) != 0)			/* return to the begining | +1 because of the ':' */
		{
			/*free(check_user_name);*/
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
	
	if ( 1 == found_match)
	{
		
		result = DeleteUser(i,num_users);
		printf("the result for delete is: %d\n",result);
	}		
	
	/*current_character = getc(fp);*/
	
	fclose(fp);
		
	/*free(check_user_name);*/
	

	return 3;







}
