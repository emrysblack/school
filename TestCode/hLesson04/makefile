###############################################################
# Program:
#     Lesson 04, DEQUE
#     Brother Helfrich, CS235
# Author:
#     <your name here>
# Summary:
#     <put a description here>
# Time:
#     <how long did it take to complete this program>?
###############################################################

##############################################################
# The main rule
##############################################################
a.out: deque.h lesson04.o nowServing.o
	g++ -o a.out lesson04.o nowServing.o
	tar -cf lesson04.tar *.h *.cpp makefile
test.out: dequeTest.cpp deque.h
	g++ -o test.out dequeTest.cpp

##############################################################
# The individual components
#      lesson04.o     : the driver program
#      nowServing.o   : the logic for the now serving program
##############################################################
lesson04.o: deque.h lesson04.cpp
	g++ -c lesson04.cpp

nowServing.o: nowServing.h nowServing.cpp deque.h
	g++ -c nowServing.cpp