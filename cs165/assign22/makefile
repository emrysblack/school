## Compile test only if complexTest.o or complex.o changed
out : assign22.o date.o
	g++ -o out assign22.o date.o 

## Compile complexTest.o only if complex.cpp or complex.h changed
assign22.o : assign22.cpp date.h
	g++ -c assign22.cpp 

## Compile complex.o only if complex.cpp or complex.h changed
date.o : date.cpp date.h
	g++ -c date.cpp