CFLAGS=-Wall -Werror -Wsign-compare -Wwrite-strings -Wtype-limits -ggdb3 -std=c++11
fsm: main.cpp node.h
	g++ $(CFLAGS) -o fsm main.cpp
.PHONY : clean
clean :
	-rm  *.o *~
