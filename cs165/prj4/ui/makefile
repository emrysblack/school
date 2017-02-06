###################################
# The programs
###################################

out : ship.o uiDraw.o uiInteract.o
	g++ -o out ship.o uiDraw.o uiInteract.o -lglut

uiTest : uiTest.o uiDraw.o uiInteract.o
	g++ -o uiTest uiTest.o uiDraw.o uiInteract.o -lglut

###################################
# The files
###################################

ship.o : ship.cpp point.h uiDraw.h uiInteract.h
	g++ -c ship.cpp

uiTest.o : uiTest.cpp point.h uiDraw.h uiInteract.h
	g++ -c uiTest.cpp

uiDraw.o : uiDraw.cpp uiDraw.h point.h
	g++ -c uiDraw.cpp

uiInteract.o : uiInteract.cpp uiInteract.h point.h
	g++ -c uiInteract.cpp

###################################
# The general rules
###################################
clean:
	rm uiTest out *.o

all: uiTest out