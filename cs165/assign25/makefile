## Compile test only if complexTest.o or complex.o changed
out : assign25.o date.o
	g++ -o out assign25.o date.o 

## Compile complexTest.o only if complex.cpp or complex.h changed
assign25.o : assign25.cpp date.h
	g++ -c assign25.cpp 

## Compile complex.o only if complex.cpp or complex.h changed
date.o : date.cpp date.h
	g++ -c date.cpp