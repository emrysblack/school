/***********************************************************************
 * Program:
 *    Project 2, Skeet
 *    Brother Boyer, CS165
 * Author:
 *    Brady Field
 * Summary:
 *    A game of skeet based off the pong code from Bro. Helfrich
 ***********************************************************************/
#include <cmath>
#include "ui.h"

/*****************************************
 * SKEET
 * The main pong structure containing everything
 * necessary to plan our beloved game
 ****************************************/
class Bullet
{
public:
   Bullet();
   ~Bullet();
   Point dot;
   bool isDead;
   double dx;
   double dy;
};

struct Skeet
{
   Point bird;   // bird position
   int dx;       // bird horizontal velocity
   int dy;       // vertical velocity
   bool dead;    // is the game over?
   int score;
   int score1;
   Point gun; // location of the gun
   int gAngle;
   Bullet dot[5];
   int delay;
};


// Math functions

/***********************
 * degrees to radians
 ***********************/
float deg2rad(float value)
{
   return (M_PI / 180) * value;
}

/*************************
 * MAX
 *************************/
float max(float a, float b)
{
   if (a >= b)
      return a;
   return b;
}

/*************************
 * MIN
 *************************/
float min(float a, float b)
{
   if (a <= b)
      return a;
   return b;
}

/*******************************************
 * default constructor
 *******************************************/
Bullet :: Bullet()
{
   dot.x = 127;
   dot.y = -127;
   isDead = true;
   dx = 0;
   dy = 0;
}

/*******************************************
 * deconstructor
 *******************************************/
Bullet :: ~Bullet()
{
}

/*******************************************
 * fires a bullet
 *******************************************/
void fireBullet(Bullet *b, int gAngle)
{
   b->dx = 10 * sin(deg2rad(gAngle));
   b->dy = 10 * cos(deg2rad(gAngle));
   b->isDead = false;
}


   
/*********************************************
 * Kill Bird
 *********************************************/
void killBird(Skeet *pSkeet)
{
   pSkeet->dead = true;
   pSkeet->bird.x = 0;
   pSkeet->bird.y = 200; // off screen
   pSkeet->dx = 0;
   pSkeet->dy = 0;
}

/*******************************************
 * away
 ******************************************/
void away(Skeet *pSkeet)
{
   // woops, birds away!
   if ((pSkeet->bird.x > 128) || (pSkeet->bird.y > 128) || (pSkeet->bird.y < -128))
   {
      killBird(pSkeet);
      pSkeet->score1++;
   }
   
}

/******************************************
 * regenerate bird
 ******************************************/
void regenerateBird(Skeet *pSkeet)
{
   //regenerate bird
   pSkeet->bird.x = -128;
   pSkeet->bird.y = random(-128, 128, "Bird regenerate position");
   pSkeet->dx = random(3, 6, "Bird regenerate horizontal velocity");
   pSkeet->dy = random(5, 20, "Bird regenerate vertical velocity / 5");
   if (pSkeet->bird.y > 0)
      pSkeet->dy *= -1;
   pSkeet->dy /= 5;
   pSkeet->dead = false;
   
}


/*******************************************
 * Bullet miss
 ******************************************/
void bulletMiss(Bullet *pDot)
{
   // woops, we missed the bird!
   if ((pDot->dot.x > 128) || (pDot->dot.y > 128) || (pDot->dot.y < -128)
       || (pDot->dot.x < -128))
   {
      pDot->isDead = true;
      pDot->dot.x = 0;
      pDot->dot.y = 200; // off screen
      pDot->dx = 0;
      pDot->dy = 0;

      // regenerate the bullets
       pDot->dot.x = 127;
       pDot->dot.y = -127;
       pDot->dx = 0;
       pDot->dy = 0;
   }

}

/*********************************************
 * kill bullet
 *********************************************/
void killBullet(Bullet *pDot)
{
    pDot->isDead = true;
    pDot->dot.x = 0;
    pDot->dot.y = 200; // off screen
    pDot->dx = 0;
    pDot->dy = 0;

    // regenerate the bullet
    pDot->dot.x = 127;
    pDot->dot.y = -127;
    pDot->dx = 0;
    pDot->dy = 0;
}

/****************************************
 * STRIKE
 * Strike the bird
 ****************************************/
void strike(Skeet *pSkeet, Bullet *b)
{
   killBird(pSkeet);
   killBullet(b);
   pSkeet->score++;
}

/******************************************
 * DELAY
 ******************************************/
void setDelay(Skeet *pSkeet)
{
   pSkeet->delay = random(0,30, "Regenerate bird? 0 == yes: ");
}

/*************************************************
 * calculates minimum distance between two objects
 *************************************************/
float minimumDistance(Skeet *a, Bullet *b)
{
   float top = a->bird.y + 5;
   float bottom = a->bird.y - 5;
   float right = a->bird.x + 5;
   float left = a->bird.x - 5;
   if ((b->dot.y <= top) && (b->dot.y >= bottom))
      if ((b->dot.x <= right) && (b->dot.x >= left))
         strike(a, b);
}

/*********************************************
 * CALLBACK
 * The main interaction loop of the engine.
 *********************************************/
void callBack(const Graphics *pGraphics, void *p)
{
   
   
   bool empty = false;
   Bullet *pDot;
   Skeet *pSkeet = (Skeet *)p;
   const Point SCORE = {-126, 126};
   const Point SCORE1 = {98, 126};
   float distance;
   
   // ready the next bullet to be fired
   if (pSkeet->dot[0].isDead)
      pDot = &pSkeet->dot[0];
   else if (pSkeet->dot[1].isDead)
      pDot = &pSkeet->dot[1];
   else if (pSkeet->dot[2].isDead)
      pDot = &pSkeet->dot[2];
   else if (pSkeet->dot[3].isDead)
      pDot = &pSkeet->dot[3];
   else if (pSkeet->dot[4].isDead)
      pDot = &pSkeet->dot[4];
   else
      empty = true;

   // delay option
   if (pSkeet->dead)
      pSkeet->delay--;

   if (pSkeet->delay == 0)
   {
      regenerateBird(pSkeet);
      setDelay(pSkeet);
   }
   // advance the ball and bullets
   if(!pSkeet->dead)
      away(pSkeet);
   pSkeet->bird.x += pSkeet->dx;
   pSkeet->bird.y += pSkeet->dy;
   

   // check the gun angle
   if ((pGraphics->isUpPress) || (pGraphics->isRightPress))
      if (pSkeet->gAngle > 0)
         pSkeet->gAngle -= 2;
   if ((pGraphics->isDownPress) || (pGraphics->isLeftPress))
      if(pSkeet->gAngle < 90)
         pSkeet->gAngle += 2;
   

   // fire bullets
   if (pGraphics->isSpacePress)
      if (!empty)
         fireBullet(pDot, pSkeet->gAngle);
   
   // advance bullets
   
    for(int i = 0; i < 5; i++)
      if(!pSkeet->dot[i].isDead)      
      {
         pSkeet->dot[i].dot.x -= pSkeet->dot[i].dx;
         pSkeet->dot[i].dot.y += pSkeet->dot[i].dy;
      }
    
    // check bullets relative to bird
    for (int i = 0; i < 5; i++)
       if (!pSkeet->dot[i].isDead)
          minimumDistance(pSkeet, &pSkeet->dot[i]);
       
   // draw the gun
   drawRect(pSkeet->gun, 5, 40, pSkeet->gAngle);

   // draw the bird
   if (!pSkeet->dead)
      drawCircle(pSkeet->bird, 10, 12, 0);

   // draw the bullets and advance them
   for (int i = 0; i < 5; i++)
      if (!pSkeet->dot[i].isDead)
      {
         drawDot(pSkeet->dot[i].dot);
         bulletMiss(&pSkeet->dot[i]);
      }

   // draw the scores, hiits on left, misses on right
   drawNumber(SCORE, pSkeet->score);
   drawNumber(SCORE1, pSkeet->score1);
}

/*********************************
 * Just initialize
 * my skeet type and call the display engine.
 * That is all!
 *********************************/
int main(int argc, char **argv)
{
   Skeet skeet;
   Skeet *pSkeet = &skeet;
   regenerateBird(pSkeet);
   pSkeet->gun.x = 128;
   pSkeet->gun.y = -128;
   pSkeet->gAngle = 45;
   pSkeet->score = 0;
   pSkeet->score1 = 0;
   pSkeet->delay = 1;
   
   initialize(argc, argv, string("Skeet Shoot"),
              callBack, &skeet);
   run();
}
