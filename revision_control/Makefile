CFLAGS = -Wall -ggdb3 -Werror -Wsign-compare -Wwrite-strings -Wtype-limits

money_tracker: main.o 
	g++  main.o -o rev_cntl -lm
main.o: main.cpp 
	g++ -c  main.cpp $(CFLAGS)
.PHONY: clean
clean:
	rm -f money_tracker *.o *.c~ *.h~ *.cpp~
