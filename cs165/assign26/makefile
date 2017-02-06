## Compile test only if complexTest.o or complex.o changed
out : assign26.o date.o
	g++ -o out assign26.o date.o 

## Compile complexTest.o only if complex.cpp or complex.h changed
assign26.o : assign26.cpp date.h
	g++ -c assign26.cpp 

## Compile complex.o only if complex.cpp or complex.h changed
date.o : date.cpp date.h
	g++ -c date.cpp