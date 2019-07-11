CFLAGS=-Wall -Werror -Wsign-compare -Wwrite-strings -Wtype-limits -ggdb3
read_bmp: read_bmp_2.o area_map.o
	g++ -o read_bmp read_bmp_2.o area_map.o 
read_bmp_2.o: read_bmp_2.cpp area_map.h
	g++ $(CFLAGS) -c read_bmp_2.cpp area_map.h
area_map.o: area_map.cpp area_map.h
	g++ $(CFLAGS) -c area_map.cpp area_map.h
