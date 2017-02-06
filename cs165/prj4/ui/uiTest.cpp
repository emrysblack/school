/****************************************
 * UI TEST
 * Just a simple program to test the user
 * interface consisting of uiDraw and uiInteract
 ***************************************/


#include "point.h"
#include "uiInteract.h"
#include "uiDraw.h"
using namespace std;

/************************************
 * Test structure to capture the ball
 * that I will move around the screen
 ***********************************/
class Ball
{
public:
   Ball() : sides(3), rotation(0) { };
   Point pt;
   int sides;
   int rotation;
};

/*************************************
 * All the interesting work happens here, when
 * I get called back from OpenGL to draw a frame.
 * When I am finished drawing, then the graphics
 * engine will wait until the proper amount of
 * time has passed and put the drawing on the screen.
 **************************************/
void callBack(const Interface *pUI, void *p)
{
   Ball *pBall = (Ball *)p;
   
   if (pUI->isRight())
      pBall->pt.addX(1);
   if (pUI->isLeft())
      pBall->pt.addX(-1);
   if (pUI->isUp())
      pBall->pt.addY(1);
   if (pUI->isDown())
      pBall->pt.addY(-1);
   
   // use the space bar to change the number os sides.
   if (pUI->isSpace())
      pBall->sides++;
   if (pBall->sides == 12)
      pBall->sides = 3;

   // rotate constantly
   pBall->rotation++;
   
   // draw
   drawCircle(pBall->pt, /*position*/
              20, /* radius */
              pBall->sides /*segments*/,
              pBall->rotation /*rotation*/);
}



/*********************************
 * Main is pretty sparse.  Just initialize
 * my ball type and call the display engine.
 * That is all!
 *********************************/
int main(int argc, char **argv)
{
   Interface ui(argc, argv, "Test");
   Ball ball;
   ui.run(callBack, &ball);

   return 0;
}
