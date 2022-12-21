#include <stdio.h>
#include "printingnums.h"

int main()
{

	int num =4;

	Printnum(num);
	printf("%d",3);

	return 0;
}


 /* impilicit: export LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH  
 or:
 -Wl,-rpath,/home/daniel/git/system_programming/libraries/ libdyn.so  */  
