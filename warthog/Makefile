CFLAGS=-Wall -Werror -Wsign-compare -Wwrite-strings -Wtype-limits -ggdb3 -std=c++11
test: main.o area_map.o pixel.o
	g++ -o test main.o area_map.o pixel.o
area_map.o: area_map.cpp area_map.h
	g++ $(CFLAGS) -c area_map.cpp area_map.h
pixel.o: pixel.cpp area_map.h
	g++ $(CFLAGS) -c pixel.cpp area_map.h
main.o: main.cpp area_map.h
	g++ $(CFLAGS) -c main.cpp area_map.h
.PHONY : clean
clean :
	-rm  *.o *~
