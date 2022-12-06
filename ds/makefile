
cc = gcc
CFLAGS = -I include/ 
CPPFLAGS = -ansi -pedantic-errors -Wall -Wextra 
SRC = src/stack.c test/stack_test.c


stack.out: src/stack.c test/stack_test.c include/stack.h
	@$(CC)  $(CPPFLAGS) $(CFLAGS) $(SRC) -o stack.out
	 
obj: src/stack.c test/stack_test.c include/stack.h
	@$(CC) -c $(CPPFLAGS) $(CFLAGS) $(SRC) 


stackdebug.out: src/stack.c test/stack_test.c include/stack.h
	 @$(CC)  $(CPPFLAGS) -g $(CFLAGS) $(SRC) -o stackdebug.out

stack_release.out: src/stack.c test/stack_test.c include/stack.h
	@$(CC)  $(CPPFLAGS) -O3 $(CFLAGS) $(SRC) -o stack_release.out


all: stack.out obj stackdebug.out stack_release.out

clean:
	@rm -f stack.out
	@rm -f stackdebug.out
	@rm -f stack_release.out
	@rm -f stack.o
	@rm -f stack_test.o
