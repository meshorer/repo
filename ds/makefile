
cc = gcc
CFLAGS = -I include/ 
UTIL =  /home/daniel/git/ds/include/utilities.c
CPPFLAGS = -ansi -pedantic-errors -Wall -Wextra 
SRC_STACK = src/stack.c test/stack_test.c
SRC_VECTOR = src/vector.c test/vector_test.c
SRC_SINGLY = src/slist.c test/slist_test.c
SRC_FSA = src/fsa.c test/fsa_test.c
SRC_COMP_SORTS = src/comparison_sort.c test/comparison_sort_test.c
SRC_RECURSION = src/recursion.c test/recursion_test.c
SRC_VSA = src/vsa.c test/vsa_test.c

vsa.out: $(SRC_VSA)
		@$(CC) $(CPPFLAGS) -g $(CFLAGS) $(SRC_VSA) -o vsa.out

recursion.out: $(SRC_RECURSION)
		@$(CC) $(CPPFLAGS) -g $(CFLAGS) $(SRC_RECURSION) -o recursion.out
		
comp_sorts.out: $(SRC_COMP_SORTS)
		@$(CC) $(CPPFLAGS) -g $(CFLAGS) $(SRC_COMP_SORTS) -o comp_sorts.out

fsa.out: $(SRC_FSA)
		@$(CC) $(CPPFLAGS) -g $(CFLAGS) $(SRC_FSA) -o fsa.out

slist.out: $(SRC_SINGLY)
		@$(CC) $(CPPFLAGS) -g $(CFLAGS) $(SRC_SINGLY) -o slist.out

vector.out: $(SRC_VECTOR)
	@$(CC) $(CPPFLAGS) -g $(CFLAGS) $(SRC_VECTOR) -o vector.out

stack.out: src/stack.c test/stack_test.c include/stack.h
	@$(CC)  $(CPPFLAGS) $(CFLAGS) $(SRC_STACK) -o stack.out
	 
obj: src/stack.c test/stack_test.c include/stack.h
	@$(CC) -c $(CPPFLAGS) $(CFLAGS) $(SRC_STACK) 


stackdebug.out: src/stack.c test/stack_test.c include/stack.h
	 @$(CC)  $(CPPFLAGS) -g $(CFLAGS) $(SRC_STACK) -o stackdebug.out

stack_release.out: src/stack.c test/stack_test.c include/stack.h
	@$(CC)  $(CPPFLAGS) -O3 $(CFLAGS) $(SRC_STACK) -o stack_release.out


all: stack.out obj stackdebug.out stack_release.out

clean:
	@rm -f stack.out
	@rm -f stackdebug.out
	@rm -f stack_release.out
	@rm -f stack.o
	@rm -f stack_test.o
