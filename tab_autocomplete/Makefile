CFLAGS = -Wall -ggdb3 -Werror -Wsign-compare -Wwrite-strings -Wtype-limits

autocomplete: main.o 
	g++ main.o -o autocomplete -lm -lreadline
main.o: main.cpp 
	g++ -c main.cpp $(CFLAGS) -lreadline
.PHONY: clean
clean:
	rm -f money_tracker *.o *.c~ *.h~ *.cpp~
