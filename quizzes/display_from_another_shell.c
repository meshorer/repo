#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>


int main()
{
	while (1)
	{
		printf("process %d is running\n",getpid());
		sleep(1);
		printf("just check\n");
	}
	
	return 0;
}
