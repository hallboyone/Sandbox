CFLAGS = -Wall -Werror -Wsign-compare -Wwrite-strings -Wtype-limits -std=c++11

inputFlags: main.o InputFlags.o
	g++ main.o InputFlags.o -o inputFlags
main.o: main.cpp
	g++ -c main.cpp $(CFLAGS)
InputFlags.o: InputFlags.cpp InputFlags.hpp
	g++ -c InputFlags.cpp $(CFLAGS)

.PHONY: clean
clean:
	rm  *.o *.c~ *.h~ *.cpp~
