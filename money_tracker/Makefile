money_tracker: main.o parseInput.o fileIO.o
	gcc main.o parseInput.o  fileIO.o -o money_tracker -lm
main.o: main.c function_decl.h
	gcc -c  main.c -Wall -Werror -Wsign-compare -Wwrite-strings -Wtype-limits
parse.o: parseInput.c function_decl.h
	gcc  -c parseInput.c -Wall -Werror -Wsign-compare -Wwrite-strings -Wtype-limits
fileIO.o: fileIO.c function_decl.h
	gcc  -c fileIO.c -Wall -Werror -Wsign-compare -Wwrite-strings -Wtype-limits
