CC		= gcc
CFLAGS 	= -g -Wall -std=c99

.SUFFIXES: .c .o
.PHONY: all clean

all: traversals

traversals: traversals.o queue.o graph_structs.o
test: queue.o test.o
queue.o: queue.h queue.c
traversals.o: traversals.c
graph_structs.o: graph_structs.h graph_structs.c
test.o: test.c


clean:
	rm -f $(wildcard *.o)
	rm -f traversals 
	rm -f test
	

