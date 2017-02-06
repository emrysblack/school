###############################################################
# Program:
#     Lesson 01, SET
#     Brother Helfrich, CS265
# Author:
#     <your name here>
# Summary:
#     <put a description here>
###############################################################

##############################################################
# The main rule
##############################################################
a.out: set.h lesson01.o goFish.o card.o
	g++ -o a.out lesson01.o goFish.o card.o
	tar -cf lesson01.tar *.h *.cpp makefile

##############################################################
# The individual components
#      lesson01.o     : the driver program
#      goFish.o       : the logic for the goFish game
#      card.o         : a single playing card
##############################################################
lesson01.o: set.h goFish.h lesson01.cpp
	g++ -c lesson01.cpp

goFish.o: set.h goFish.h goFish.cpp card.h
	g++ -c goFish.cpp

card.o: card.h card.cpp
	g++ -c card.cpp
clean:
	rm -f a.out lesson01.o goFish.o card.o