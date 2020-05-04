CFLAGS = -Wall -ggdb3 -Werror -Wsign-compare -Wwrite-strings -Wtype-limits

ui: main.o
	gcc main.o -o ui
main.o: main.c
	gcc -c main.c $(CFLAGS)

.PHONY: clean
clean:
	rm  *.o *.c~ *.h~ *.cpp~
