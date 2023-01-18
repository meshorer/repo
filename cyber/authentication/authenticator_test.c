#include <stdio.h>

#include "authenticator.h"




/* while copiling use  -lcrypt at the end of line
*/

int main(void) 
{
	
	AuthAddUser("","1234");
	AuthAddUser("","1234");
	AuthAddUser("","1234");
	AuthAddUser("sdfds","123345erg4");
	AuthAddUser("user1","123345erg4");
	AuthAddUser("user2","123345erg4");
	AuthAddUser("user3","123345erg4");
	AuthAddUser("user4","123345erg4");
	AuthAddUser("user5","123345erg4");
	AuthAddUser("user43","123345erg4");
	AuthAddUser("daniel","123345erg4");
	AuthAddUser("daniela","123345erg4");
	
	
	printf("result is : %d\n",AuthAuthenticator("", "1234"));

	    return 0;
}

