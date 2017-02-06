 #######################################################################
 # Program:
 #    Unit 4, homograph search
 #    Brother Smithb, CS470
 # Author:
 #    Brady Field
 # Homograph
 #    This program will search a file for a keyword and return number
 #    of hits including homographs of the keyword
 #######################################################################

a.out : homographTest.o homograph.o
	g++ -o a.out homographTest.o homograph.o
	tar -cf unit4.tar *.cpp *.h makefile

homograph.o : homograph.cpp homograph.h
	g++ -c homograph.cpp

homographTest.o : homographTest.cpp homograph.h
	g++ -c homographTest.cpp

########
clean :
	rm a.out *.o *.tar
