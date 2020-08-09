CFLAGS=-Wall -Werror -Wsign-compare -Wwrite-strings -Wtype-limits -ggdb3 -std=c++11
test: main.o
	g++ -o test main.o
main.o: main.cpp MooType.hpp MergeSet.hpp
	g++ $(CFLAGS) -c main.cpp
.PHONY : clean
clean :
	-rm  *.o *~
