## Compile test only if complexTest.o or complex.o changed
out : complexTest.o complex.o
	g++ -o out complexTest.o complex.o 

## Compile complexTest.o only if complex.cpp or complex.h changed
ComplexTest.o : complexTest.cpp complex.h
	g++ -c complexTest.cpp 

## Compile complex.o only if complex.cpp or complex.h changed
complex.o : complex.cpp complex.h
	g++ -c complex.cpp