#include "memory_mappping_full.h"
#include <stdio.h>

int main(int argc, char **argv, char **envp)
{
	printf("argv address:                 %p\n", &argv);
	printf("envp address:                 %p\n", &envp);
	ExternFunc();
	
	MappingFull(); 
	printf("ex1\n");
	
	return 0;
}

/* STATIC LIBRARY:
**** STACK ****
str address:                  0x7fffffffdf50
heap address:                 0x7fffffffdf40
heap2 address:                0x7fffffffdf48
con_local address:            0x7fffffffdf3c
non_con_local address:        0x7fffffffdf38

**** HEAP ****
heap content:                 0x5555555596b0
heap2 content:                0x5555555596d0

**** BSS ****
non_con_global address:       0x55555555801c
con_static_local address:     0x555555556344
con_global address:           0x555555556058

**** RODATA ****
str content:                  0x555555556071
con_static_global address:    0x55555555605c

**** DATA ****
non_con_static_local address: 0x555555558014
non_con_static_global address:0x555555558010

**** TEXT ****
ExternFunc address:           0x55555555524b
StaticFunc address:           0x555555555240

---------------------------------------------

DYNAMIC LIBRARY - IMPLICIT:
argv address:                 0x7fff52758680
envp address:                 0x7fff52758678

**** STACK ****
str address:                  0x7fff52758650
heap address:                 0x7fff52758640
heap2 address:                0x7fff52758648
con_local address:            0x7fff5275863c
non_con_local address:        0x7fff52758638

<<<<START OF SHARED LIBRARY>>>>
**** BSS ****
non_con_global address:       0x7ff8b6867054
con_static_local address:     0x7ff8b68652ec
con_global address:           0x7ff8b6865000

**** RODATA ****
str content:                  0x7ff8b6865019
con_static_global address:    0x7ff8b6865004

**** DATA ****
non_con_static_local address: 0x7ff8b686704c
non_con_static_global address:0x7ff8b6867048

**** TEXT ****
ExternFunc address:           0x7ff8b68641a4
StaticFunc address:           0x7ff8b6864199
<<<<END OF SHARED LIBRARY>>>>

**** HEAP ****
heap2 content:                0x562aaff22850
heap content:                 0x562aaff226b0


*/


