
cc = gcc
CFLAGS = -I include/ 
CPPFLAGS = -ansi -pedantic-errors -Wall -Wextra 
SRC = src/stack.c test/stack_test.c

out:
	 @$(CC)  $(CPPFLAGS) $(CFLAGS) $(SRC) -o stack.out
	 
obj:
	@$(CC) -c $(CPPFLAGS) $(CFLAGS) $(SRC) 


debug:
	 @$(CC)  $(CPPFLAGS) -g $(CFLAGS) $(SRC) -o stackdb.out

release:
	@$(CC)  $(CPPFLAGS) -O3 $(CFLAGS) $(SRC) -o stack_release.out


all: out obj debug release

clean:
	@rm stack.out
	@rm stackdb.out
	@rm stack_release.out
	@rm stack.o
	@rm stack_test.o
