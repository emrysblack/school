###############################################################
# Program:
#     Lesson 00, Container
#     Brother Helfrich, CS265
# Author:
#     <your name here>
# Summary:
#     <put a description here>
###############################################################

##############################################################
# The main rule
##############################################################
a.out: container.h lesson00.o
	g++ -o a.out lesson00.o
	tar -cf lesson00.tar container.h lesson00.cpp makefile

##############################################################
# The individual components
#      lesson00.o     : the driver program
##############################################################
lesson00.o: container.h lesson00.cpp
	g++ -c lesson00.cpp
