/***********************************************************************
 * Program:
 *    Project 2, Pong
 *    Brother Helfrich, CS165
 * Author:
 *    Br. Helfrich
 * Summary:
 *    This program is designed to have a shape move around the
 *    screen according the the user's arrow keys and space bar.
 *    The space bar will change the number of sides to our polygon
 ***********************************************************************/

#include "ui.h"

/************************************
 * Test structure to capture the ball
 * that I will bounce around the screen
 ***********************************/
struct Ball
{
   Point point;
   int   sides;
   int   angle;
};

/*************************************
 * All the interesting work happens here, when
 * I get called back from OpenGL to draw a frame.
 * When I am finished drawing, then the graphics
 * engine will wait until the proper amount of
 * time has passed and put the drawing on the screen.
 **************************************/
void callBack(const Graphics *pGraphics, void *p)
{
   Ball *pBall = (Ball *)p;

   pBall->point.y -= (pGraphics->isDownPress + 3) / 4;
   pBall->point.y += (pGraphics->isUpPress + 3) / 4;
   pBall->point.x += (pGraphics->isRightPress + 3) / 4;
   pBall->point.x -= (pGraphics->isLeftPress + 3) / 4;

   // use the space bar to change the number os sides.
   if (pGraphics->isSpacePress)
      pBall->sides++;
   if (pBall->sides == 12)
      pBall->sides = 3;

   // rotate constantly
   pBall->angle++;
   
   drawCircle(pBall->point,
              30, /* radius */
              pBall->sides /*segments*/,
              pBall->angle /*rotation*/);
}

/*********************************
 * Main is pretty sparse.  Just initialize
 * my ball type and call the display engine.
 * That is all!
 *********************************/
int main(int argc, char **argv)
{
   Ball ball;
   ball.point.x = 0;
   ball.point.y = 0;
   ball.sides = 3;
   ball.angle = 0;
   initialize(argc, argv, string("Test"),
              callBack, &ball);
   run();
}
