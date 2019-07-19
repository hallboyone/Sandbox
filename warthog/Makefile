CFLAGS=-Wall -Werror -Wsign-compare -Wwrite-strings -Wtype-limits -ggdb3 -std=c++11
#read_bmp: read_bmp.o area_map.o
#	g++ -o read_bmp read_bmp.o area_map.o 
#read_bmp.o: read_bmp.cpp area_map.h
#	g++ $(CFLAGS) -c read_bmp.cpp area_map.h
#area_map.o: area_map.cpp area_map.h
#	g++ $(CFLAGS) -c area_map.cpp area_map.h
test: main.o area_map.o pixel_.o
	g++ -o test main.o area_map.o pixel_.o
main.o: main.cpp area_map.h
	g++ $(CFLAGS) -c main.cpp area_map.h
area_map.o: area_map.cpp area_map.h
	g++ $(CFLAGS) -c area_map.cpp area_map.h
pixel_.o: pixel_.cpp area_map.h
	g++ $(CFLAGS) -c pixel_.cpp area_map.h
.PHONY : clean
clean :
	-rm  *.o *~
