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

#include <cmath>
#include "uiDraw.h"

/************************************
 * Test structure to capture the ball
 * that I will bounce around the screen
 ***********************************/
struct Ship
{
   Point point;
   int   sides;
   int   angle;
   double dx;
   double dy;
   double speed;
};

// Math functions

/***********************
 * degrees to radians
 ***********************/
float deg2rad(float value)
{
   return (M_PI / 180) * value;
}

/*************************************
 * All the interesting work happens here, when
 * I get called back from OpenGL to draw a frame.
 * When I am finished drawing, then the graphics
 * engine will wait until the proper amount of
 * time has passed and put the drawing on the screen.
 **************************************/
void callBack(const Graphics *pGraphics, void *p)
{
  Ship *pShip = (Ship *)p;
   double speed = pShip->speed;
   int gAngle = pShip->angle;

   if (pGraphics->isUpPress)
   {
      speed += 0.2;
   }
   else if (pGraphics->isDownPress)
   {
   }
   pShip->dx = speed * sin(deg2rad(gAngle));
   pShip->dy = speed * cos(deg2rad(gAngle));
   //pShip->point.y -= pShip->dy;
   pShip->point.y += pShip->dy;
   //pShip->point.x += pShip->dx;
   pShip->point.x -= pShip->dx;

   // use the space bar to change the number os sides.
   // if (pGraphics->isSpacePress)
   //   pShip->sides++; change to fire
   
   if (pGraphics->isLeftPress)
      pShip->angle += 10;
   if (pGraphics->isRightPress)
      pShip->angle -= 10;
   
   drawCircle(pShip->point,
              10, /* radius */
              pShip->sides /*segments*/,
              pShip->angle /*rotation*/);
}

/*********************************
 * Main is pretty sparse.  Just initialize
 * my ball type and call the display engine.
 * That is all!
 *********************************/
int main(int argc, char **argv)
{
   Ship ball;
   ball.point.x = 0;
   ball.point.y = 0;
   ball.sides = 3;
   ball.angle = 0;
   ball.dx = 0;
   ball.dy = 0;
   ball.speed = 0;
   initialize(argc, argv, string("Test"),
              callBack, &ball);
   run();
}
