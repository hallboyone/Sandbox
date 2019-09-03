money_tracker: main.o parseInput.o fileIO.o printFun.o mkenvl.o
	gcc  -ggdb3 main.o parseInput.o  fileIO.o printFun.o mkenvl.o -o money_tracker -lm
main.o: main.c function_decl.h
	gcc -c  main.c -Wall -ggdb3 -Werror -Wsign-compare -Wwrite-strings -Wtype-limits
parse.o: parseInput.c function_decl.h
	gcc  -c parseInput.c -Wall -ggdb3 -Werror -Wsign-compare -Wwrite-strings -Wtype-limits
fileIO.o: fileIO.c function_decl.h
	gcc  -c fileIO.c -Wall -Werror -ggdb3 -Wsign-compare -Wwrite-strings -Wtype-limits
printFun.o: printFun.c function_decl.h
	gcc  -c printFun.c -Wall -Werror -ggdb3 -Wsign-compare -Wwrite-strings -Wtype-limits
mkenvl.o: mkenvl.c function_decl.h
	gcc  -c mkenvl.c -Wall -Werror -ggdb3 -Wsign-compare -Wwrite-strings -Wtype-limits
