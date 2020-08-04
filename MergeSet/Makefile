CFLAGS=-Wall -Werror -Wsign-compare -Wwrite-strings -Wtype-limits -ggdb3 -std=c++11
test: main.o
	g++ -o test main.o
main.o: main.cpp MooType.hpp
	g++ $(CFLAGS) -c main.cpp MooType.hpp
.PHONY : clean
clean :
	-rm  *.o *~
