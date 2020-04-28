CFLAGS = -Wall -ggdb3 -Werror -Wsign-compare -Wwrite-strings -Wtype-limits -std=c++11

config: main.o 
	g++ main.o -o config
main.o: main.cpp 
	g++ -c main.cpp $(CFLAGS)
.PHONY: clean
clean:
	rm -f money_tracker *.o *.c~ *.h~ *.cpp~
