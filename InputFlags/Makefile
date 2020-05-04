CFLAGS = -Wall -ggdb3 -Werror -Wsign-compare -Wwrite-strings -Wtype-limits -std=c++11

inputFlags: main.o
	g++ main.o -o inputFlags
main.o: main.cpp
	g++ -c main.cpp $(CFLAGS)

.PHONY: clean
clean:
	rm  *.o *.c~ *.h~ *.cpp~
