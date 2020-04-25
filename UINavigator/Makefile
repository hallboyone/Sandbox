CFLAGS = -Wall -ggdb3 -Werror -Wsign-compare -Wwrite-strings -Wtype-limits

ui: main.o UINavigator.o
	g++ main.o UINavigator.o -o ui
main.o: main.cpp
	g++ -c main.cpp $(CFLAGS)
UINavigator.o: UINavigator.cpp UINavigator.hpp
	g++ -c UINavigator.cpp $(CFLAGS)
.PHONY: clean
clean:
	rm  *.o *.c~ *.h~ *.cpp~
