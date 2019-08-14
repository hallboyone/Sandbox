money_tracker: main.o parseInput.o
	gcc main.o parseInput.o -o money_tracker
main: main.c function_decl.h
	gcc -c  main.c -Wall -Werror -Wsign-compare -Wwrite-strings -Wtype-limits
parse: parseInput.c function_decl.h
	gcc  -c parseInput.c -Wall -Werror -Wsign-compare -Wwrite-strings -Wtype-limits
