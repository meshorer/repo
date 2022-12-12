
cc = gcc
CFLAGS = -I include/ 
CPPFLAGS = -ansi -pedantic-errors -Wall -Wextra 
SRC_STACK = src/stack.c test/stack_test.c
SRC_VECTOR = src/vector.c test/vector_test.c
SRC_SINGLY = src/singly_linked_list.c test/singly_linked_list_test.c


singly_list.out: $(SRC_SINGLY)
		@$(CC) $(CPPFLAGS) -g $(CFLAGS) $(SRC_SINGLY) -o singly_list.out

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
