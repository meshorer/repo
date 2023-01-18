 #include <crypt.h>
#include <stdio.h>
#include "authenticator.h"

int CheckConditions(const char *username, const char *password);
int CheckIfUsernameExists(const char *username);


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

	FILE *fp = NULL;
	char *user_name = NULL;
	char *next_character = NULL;
	
	char *hashed_password = NULL;
	int result = 0;
	
	
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


	return 0;
}




int CheckConditions(const char *username, const char *password)
{
	
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



int CheckIfUsernameExists(const char *username)
{




	return 0;
}


int AppendUserToFile(const char *username,const char *hashed_password)
{

	FILE *fp = NULL;
	
	fp = fopen(USERS_DB, "a");  
	if (NULL == fp)
	{
		return -1;
	}
	
	fprintf(fp, "%s", username);
	fprintf(fp, "%s", ":");
	fprintf(fp, "%s\n", hashed_password);
	
	fclose(fp);
	
return 0;
}
