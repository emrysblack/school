## Compile test only if complexTest.o or complex.o changed
out : assign23.o date.o
	g++ -o out assign23.o date.o 

## Compile complexTest.o only if complex.cpp or complex.h changed
assign23.o : assign23.cpp date.h
	g++ -c assign23.cpp 

## Compile complex.o only if complex.cpp or complex.h changed
date.o : date.cpp date.h
	g++ -c date.cpp