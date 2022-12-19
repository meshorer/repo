#include <dlfcn.h>


int main()
{
	
	void (*func)(int);
	int num =4;
	
	void *handler = dlopen("/home/daniel/git/system_programming/libraries/ldynlib.so" , RTLD_LAZY);
	
	/*func = dlsym(handler,"Printnum"); */
	func = dlsym(handler,"Printnum");
	func(num);
	
	dlclose(handler);
	
	return 0;
	
}
