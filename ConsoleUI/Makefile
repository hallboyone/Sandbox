CFLAGS = -Wall -ggdb3 -Werror -Wsign-compare -Wwrite-strings -Wtype-limits

ui: main.o ConsoleUI.o
	g++ main.o ConsoleUI.o -o ui
main.o: main.cpp
	g++ -c main.cpp $(CFLAGS)
ConsoleUI.o: ConsoleUI.cpp ConsoleUI.hpp
	g++ -c ConsoleUI.cpp $(CFLAGS)
.PHONY: clean
clean:
	rm  *.o *.c~ *.h~ *.cpp~
