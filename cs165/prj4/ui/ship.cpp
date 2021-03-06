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
class Bullet
{
public:
   Bullet() : speed(0), rotation(0), dx(0), dy(0) { isDead = true; };
   Point pt;
   int rotation;
   float dx;
   float dy;
   float speed;
   bool isDead;
};

class Ship
{
public:
   Ship() : speed(0), rotation(0), dx(0), dy(0) { };
   void fireBullet (Point *pt, Bullet *b, float gAngle);
   Point pt;
   int rotation;
   float dx;
   float dy;
   float speed;
   Bullet dot[10];
};



/***********************
 * degrees to radians
 ***********************/
float deg2rad(float value)
{
   return (M_PI / 180) * value;
}

/*******************************************
 * fires a bullet
 *******************************************/
void Ship::fireBullet(Point *pt, Bullet *b, float gAngle)
{
   b->pt.setX(pt->getX());
   b->pt.setY(pt->getY());
   b->dx = 10 * sin(deg2rad(gAngle));
   b->dy = 10 * cos(deg2rad(gAngle));
   b->isDead = false;
}

/*************************************
 * All the interesting work happens here, when
 * I get called back from OpenGL to draw a frame.
 * When I am finished drawing, then the graphics
 * engine will wait until the proper amount of
 * time has passed and put the drawing on the screen.
 **************************************/
void callBack(const Interface *pUI, void *p)
{
   Ship *pShip = (Ship *)p;
   bool empty = false;
   Bullet *pDot;
   
   // ready the next bullet to be fired
   bool found = false;
   int i;
   for (i = 0; i < 10 || !found; i++)
      if (pShip->dot[i].isDead)
        found = true;
   if (found)
      pDot = &pShip->dot[i];
   else
      empty = true;

   
   
   if (pUI->isRight())
      pShip->rotation -= 10;
   if (pUI->isLeft())
      pShip->rotation += 10;
   if (pUI->isUp())
      pShip->speed += 0.2;
   if (pUI->isDown())
      if (pShip->speed > 0)
         pShip->speed -= 0.2;
      else
         pShip->speed = 0;
   
   pShip->dx = pShip->speed * sin(deg2rad(pShip->rotation));
   pShip->dy = pShip->speed * cos(deg2rad(pShip->rotation));
   // use the space bar to fire bullets
   if (pUI->isSpace())
      if (!empty)
         pShip->fireBullet(&pShip->pt, &pShip->dot[i], pShip->rotation);
   
   // move ship and bullets
   pShip->pt.addY (pShip->dy);
   pShip->pt.addX (-pShip->dx);
   for(int i = 0; i < 10; i++)
      if(!pShip->dot[i].isDead)      
      {
         pShip->dot[i].pt.addX (-pShip->dot[i].dx);
         pShip->dot[i].pt.addY (pShip->dot[i].dy);
      }

   // draw
   drawShip(pShip->pt, /*position*/
              pShip->rotation - 90 /*rotation*/);
   // draw the bullets
   for (int i = 0; i < 10; i++)
      drawDot(pShip->dot[i].pt);
   //  if (pShip->dot[i].isDead)
   // {
   //    drawDot(pShip->dot[i].pt);
   // }
}



/*********************************
 * Main is pretty sparse.  Just initialize
 * my ball type and call the display engine.
 * That is all!
 *********************************/
int main(int argc, char **argv)
{
   Interface ui(argc, argv, "Asteroids");
   Ship ball;
   ui.run(callBack, &ball);

   return 0;
}
