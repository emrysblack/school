###############################################################
# The main programs are:
#    a.out:          The compiled time program
###############################################################
a.out : time.o timeDriver.o
	g++ time.o timeDriver.o

###############################################################
# Individual files
#    timeDriver.o  driver with main 
#    time.o        definitions file 
###############################################################
timeDriver.o : timeDriver.cpp time.h
	g++ -c timeDriver.cpp

time.o : time.cpp time.h
	g++ -c time.cpp

###############################################################
# General rules
###############################################################
clean :
	rm a.out time.o timeDriver.o
