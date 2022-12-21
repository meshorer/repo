#include <stdio.h>
#include <stdlib.h> /* for malloc */

static int static_foo()
{
	return 0;
}

int extern_foo()
{
	return 1;
}


int sum_func(num)
{

	char *heap_var = malloc(10);
	
	const int const_local_var = 3;
	int non_const_local_var = 3;
	
	int local_var = 5;
	
	const static int const_static_local_var = 5;
	static int non_const_static_local_var = 5;
	
	char string_literal[] = "how are you?";
	
	if (num > 0)
	{
		return num + sum_func(num-1);
	}
	else
	{
		return 0;
	}
	
	
}


int const const_global_var = 5;
int  non_const_global_var = 5;

static int non_const_static_global_var = 5;
static const int const_static_global_var = 5;

int main(int argc, char *argv[],char * envp[])
{

	
	int result = sum_func(10);
	printf("%d\n", result);
	
	sleep(300);
	
	return 0;



}

