## Compile test only if complexTest.o or complex.o changed
out : assign24.o date.o
	g++ -o out assign24.o date.o 

## Compile complexTest.o only if complex.cpp or complex.h changed
assign24.o : assign24.cpp date.h
	g++ -c assign24.cpp 

## Compile complex.o only if complex.cpp or complex.h changed
date.o : date.cpp date.h
	g++ -c date.cpp