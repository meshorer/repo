#include <dlfcn.h>
#include "multiple_instances.h"
#include <stdio.h>

int main ()
{
	printf("part a:\n");
	PrintGlobalVariablesAddress();
	
	printf("part b:\n");
	
	/*void (*func1)();
	void *handler1 = dlopen("/home/daniel/git/system_programming/multiple_instances/libfoo1.so" , RTLD_LAZY);
	
	void (*func2)();
	void *handler2 = dlopen("/home/daniel/git/system_programming/multiple_instances/libfoo2.so" , RTLD_LAZY);
	
	func1 = dlsym(handler1,"Foo1");
	func1();
	
	
	
	func2 = dlsym(handler2,"Foo2");
	func2();
	
	
	dlclose(handler1);
	dlclose(handler2); */
	
	Foo1();
	Foo2();
	
	
	return 0;
}
