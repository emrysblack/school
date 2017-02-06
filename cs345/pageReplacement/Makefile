#
# Makefile for the Page Replacement Algorithm Lab
# Created by Daniel Purcell, 18 Mar 2004
#
 
CC=g++
CFLAGS=-O2
 
OBJS=LRU.o RANDOM.o FIFO.o CLOCK.o main.o
 
all: vmalgorithm
 
vmalgorithm: $(OBJS) LRU.cpp RANDOM.cpp FIFO.cpp CLOCK.cpp main.cpp
	$(CC) $(CFLAGS) $(OBJS) -o vmalgorithm

clean:
	rm *.o vmalgorithm

submit:
	tar cvf $(USER).tar LRU.cpp FIFO.cpp CLOCK.cpp
	submit $(USER).tar 

test:
	runTests.pl test-files
