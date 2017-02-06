###############################################################
# The main programs are:
#    pong:         The playable game
#    out:          The text-only interface for debugging
#    testGraphics: Test uiGraphics.cpp
#    testText:     Test uiText.cpp
###############################################################
game : game.o uiGraphics.o
	g++ -o game game.o uiGraphics.o -lglut

out : game.o uiText.o
	g++ -o out game.o uiText.o

testGraphics : test.o uiGraphics.o
	g++ -o testGraphics test.o uiGraphics.o -lglut

testText : test.o uiText.o 
	g++ -o testText test.o uiText.o 



###############################################################
# Individual files
#    uiGraphics.o  Draw polygons on the screen and do all OpenGL graphics
#    uiText.o      Same interfaces as uiGraphics except using iostream
#    test.o        Test the UI interfaces
#    pong.o        Only the greatest game every (and it was for 20 years)  
###############################################################
uiGraphics.o : uiGraphics.cpp ui.h
	g++ -c uiGraphics.cpp

uiText.o : uiText.cpp ui.h
	g++ -c uiText.cpp

test.o : test.cpp ui.h
	g++ -c test.cpp

game.o : game.cpp ui.h
	g++ -c game.cpp


###############################################################
# General rules
###############################################################
clean :
	rm testGraphics testText game out *.o

all :  testGraphics testText game out

###############################################################
# Ref: http://www.gnu.org/software/make/manual/make.html
###############################################################