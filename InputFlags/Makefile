CFLAGS = -Wall -Werror -Wsign-compare -Wwrite-strings -Wtype-limits -std=c++11

inputFlags: main.o CmdLnFlags.o
	g++ main.o CmdLnFlags.o -o inputFlags
main.o: main.cpp
	g++ -c main.cpp $(CFLAGS)
CmdLnFlags.o: CmdLnFlags.cpp CmdLnFlags.hpp
	g++ -c CmdLnFlags.cpp $(CFLAGS)

.PHONY: clean
clean:
	rm  *.o *.c~ *.h~ *.cpp~
