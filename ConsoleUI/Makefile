CFLAGS = -Wall -ggdb3 -Werror -Wsign-compare -Wwrite-strings -Wtype-limits

ui: main.o ConsoleUI.o DictTree.o
	g++ main.o ConsoleUI.o DictTree.o -o ui
main.o: main.cpp
	g++ -c main.cpp $(CFLAGS)
ConsoleUI.o: ConsoleUI.cpp ConsoleUI.hpp
	g++ -c ConsoleUI.cpp $(CFLAGS)
DictTree.o: DictTree.cpp DictTree.hpp
	g++ -c DictTree.cpp $(CFLAGS)

.PHONY: clean
clean:
	rm  *.o *.c~ *.h~ *.cpp~
