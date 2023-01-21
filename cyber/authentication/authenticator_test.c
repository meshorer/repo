#include <stdio.h>

#include "authenticator.h"




/* while copiling use  -lcrypt at the end of line
*/

int main(void) 
{
	
	/*AuthAddUser("","1234");
	AuthAddUser("","1234");
	AuthAddUser("","1234");
	AuthAddUser("sdfds","123345erg4");
	AuthAddUser("user1","123345erg4");
	AuthAddUser("user2","123345erg4");
	AuthAddUser("user3","123345erg4");
	AuthAddUser("user4","123345erg4");
	AuthAddUser("user0","1233dfgdfgrg4");
	AuthAddUser("user5","123345erg4");
	AuthAddUser("YaeL","dadadadida");
	AuthAddUser("","1234");
	AuthAddUser("user43","123345erg4");
	AuthAddUser("daniel","123345erg4");
	AuthAddUser("daniela","123345erg4");
	AuthAddUser("","1234");*/
	
	
	printf("result is : %d\n",AuthDeleteUser(""));
	printf("result is : %d\n",AuthDeleteUser(""));
	printf("result is : %d\n",AuthDeleteUser(""));
	printf("result is : %d\n",AuthDeleteUser(""));
	printf("result is : %d\n",AuthDeleteUser("sdfds"));
	printf("result is : %d\n",AuthDeleteUser("daniela"));
	printf("result is : %d\n",AuthDeleteUser("sdfds"));
	printf("result is : %d\n",AuthAuthenticator("daniel", "123345erg4"));
	    return 0;
}

