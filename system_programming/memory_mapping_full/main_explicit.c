#include <dlfcn.h>
#include <stdio.h>

int main(int argc, char **argv, char **envp)
{
	printf("argv address:                 %p\n", &argv);
	printf("envp address:                 %p\n", &envp);
	
	void (*func1)();
	void *handler1 = dlopen("./libdynamic.so" , RTLD_LAZY);

	func1 = dlsym(handler1,"MappingFull");
	func1();
	printf("\nfunc1 address:                %p\n", &func1);
	
	dlclose(handler1);
 
	printf("ex1\n");
	
	return 0;
}

/*

DYNAMIC LIBRARY - EXPLICIT:
argv address:                 0x7ffccfde1bf0
envp address:                 0x7ffccfde1be8

**** STACK ****
str address:                  0x7ffccfde1bc0
heap address:                 0x7ffccfde1bb0
heap2 address:                0x7ffccfde1bb8
con_local address:            0x7ffccfde1bac
non_con_local address:        0x7ffccfde1ba8

<<<<START OF SHARED LIBRARY>>>>
**** BSS ****
non_con_global address:       0x7f796e6e1054
con_static_local address:     0x7f796e6df2ec
con_global address:           0x7f796e6df000

**** RODATA ****
str content:                  0x7f796e6df019
con_static_global address:    0x7f796e6df004

**** DATA ****
non_con_static_local address: 0x7f796e6e104c
non_con_static_global address:0x7f796e6e1048

**** TEXT ****
ExternFunc address:           0x7f796e6de1a4
StaticFunc address:           0x7f796e6de199
<<<<END OF SHARED LIBRARY>>>>

**** HEAP ****
heap2 content:                0x556c129bfce0
heap content:                 0x556c129c0610

 
*/
