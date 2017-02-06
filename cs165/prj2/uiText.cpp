/***********************************************************************
 * Program:
 *    Project 2, Text version of the UI
 *    Brother Helfrich, CS165
 * Author:
 *    Br. Helfrich
 * Summary:
 *    This is the text version of the graphics.h library.  It will
 *    Allow the user to verify the physics of the game with testbed.
 ************************************************************************/

#include <cmath>      // for M_PI, sin() and cos()
#include <string>     // need you ask?
#include <iostream>   // we use streams here, not OpenGL
#include <sstream>    // convert an integer into text
#include <cassert>    // I feel the need... the need for asserts

#include "ui.h"

using namespace std;

/*************************************************
 * GRAPHIC STATE
 * Can you imagine!  A global variable!  At this point
 * in time we have no choice.  The graphics library GLUT
 * gives us a callback without a void pointer.  This means
 * that they do not give us any chance to pass our state
 * back to our callback functions.  There are only one
 * way to get around this: a friend function.
 *
 * A better solution would be for the GLUT library to
 * allow us to register a void pointer ( a pointer to
 * whatever we want ) and, when they call us back, to hand
 * it to us.  We could then cast it back to our display
 * structure and be happy.  Because they failed to do this,
 * we must use a global to work around it.  Notice how we
 * only reference this in our callbacks and, as soon as we
 * get it, we immediately pass it by parameter.  This will
 * minimize the damage.
 ****************************************************/
Graphics graphicGlobal;

/**************************************************
 * INITIALIZE GRAPHIC GLOBAL
 * Because we are denied the dignity of initializing our
 * graphic state as a local variable, we must write a function
 * to do this.  This function is called from initialize()
 **************************************************/
void initializeGraphicGlobal(void (*callBack)(const Graphics *, void *),
                             void *p)
{
   cout.setf(ios::fixed);
   cout.precision(0);
   
   // set up the default state
   graphicGlobal.timePeriod = 1.0 / 30; // default to 30 frames/second
   graphicGlobal.nextTick   = 0;        // redraw now please

   // no input events right now
   graphicGlobal.isUpPress    = 0;
   graphicGlobal.isDownPress  = 0;
   graphicGlobal.isLeftPress  = 0;
   graphicGlobal.isRightPress = 0;

   // setup the callbacks
   graphicGlobal.p = p;
   graphicGlobal.callBack = callBack;
}

/************************************************************************
 * INITIALIZE
 * Normally we would initialize our drawing window here.   Instead, we will
 * just call initializeGraphicsGlobal() and call it good.
 *  INPUT    argc:       unused
 *           argv:       unused
 *           title:      unused
 *           callBack:   Callback function.  Every time we are beginning
 *                       to draw a new frame, we first callback to the client
 *                       to see if he wants to do anything, such as move
 *                       the game pieces or respond to input
 *           p:          Void point to whatever the caller wants.  You
 *                       will need to cast this back to your own data
 *                       type before using it.
 *************************************************************************/
void initialize(int argc, char* argv[], string title,
                void (*callBack)(const Graphics *, void *), void *p)
{
   initializeGraphicGlobal(callBack, p);
   return;
}

/***************************************************************
 * KEY EVENT
 * Either set the up or down event for a given key
 *   INPUT   key     which key is pressed
 *           fDown   down or brown
 ****************************************************************/
void keyEvent(int key, bool fDown)
{
   if (!fDown)
   {
      switch(key)
      {
         case 'd':
            graphicGlobal.isDownPress = fDown;
            break;
         case 'u':
            graphicGlobal.isUpPress = fDown;
            break;
         case 'r':
            graphicGlobal.isRightPress = fDown;
            break;
         case 'l':
            graphicGlobal.isLeftPress = fDown;
            break;
         case 's':
            graphicGlobal.isSpacePress = fDown;
            break;
      }
   }
   else
   {
      switch(key)
      {
         case 'd':
            graphicGlobal.isDownPress++;
            break;
         case 'u':
            graphicGlobal.isUpPress++;
            break;
         case 'r':
            graphicGlobal.isRightPress++;
            break;
         case 'l':
            graphicGlobal.isLeftPress++;
            break;
         case 's':
            graphicGlobal.isSpacePress++;
            break;
      }
   }
}


/************************************************************************
 * DRAW CALLBACK
 * OpenGL owns the message loop.  In the text debug version, the message
 * loop is here in the callback.
 *************************************************************************/
void drawCallback()
{
   //calls the programmers display function
   assert(graphicGlobal.callBack != NULL);

   bool done = false;
   while (!done)
   {
      graphicGlobal.callBack(&graphicGlobal, graphicGlobal.p);
      
      // When the user gives us input, we will continue.
      string s;
      cout << "> ";
      getline(cin, s);

      // quit event
      if (s.find('q') != string::npos)
         done = true;

      // possible commands
      char *commands = "sudlr";
      for (char *p = commands; *p; p++)
         keyEvent(*p, s.find(*p) != string::npos);

      // menu
      if (s.find('?') != string::npos)
         cout << "Available options:\n"
              << "\tu  Up keyboard key pressed\n"
              << "\td  Down keyboard key pressed\n"
              << "\tr  Right keyboard key pressed\n"
              << "\tl  Left keyboard key pressed\n"
              << "\ts  Space bar pressed\n"
              << "\tq  Quit the program\n"
              << "\t?  Get this menu\n";
   }
}

/************************************************************************
 * RUN
 * Set the game in action.  We will get control back in our drawCallback
 *************************************************************************/
void run()
{
   drawCallback();
}

/************************************************************************
 * DEG 2 RAD
 * Converts degrees (0 .. 360) to radians (-PI .. PI)
 *************************************************************************/
inline float deg2rad(float value)
{
   return (M_PI / 180) * value;
}

/************************************************************************
 * IS TIME TO DRAW
 * Have we waited long enough to draw swap the background buffer with
 * the foreground buffer?
 *   INPUT  graphics    the main display structure
 *************************************************************************/
bool isTimeToDraw(Graphics &graphics)
{
   return (clock() >= graphics.nextTick);
}

/************************************************************************
 * SET NEXT DRAW TIME
 * What time should we draw the buffer again?  This is a function of
 * the current time and the frames per second.
 *   INPUT  graphics   The main display structure
 *************************************************************************/
void setNextDrawTime(Graphics &graphics)
{
   graphics.nextTick = clock()
      + static_cast<int> (graphics.timePeriod * CLOCKS_PER_SEC);
}

/************************************************************************
 * SET FRAMES PER SECOND
 * The frames per second dictates the speed of the game.  The more frames
 * per second, the quicker the game will appear to the user.  We will default
 * to 30 frames/second but the client can set this at will.
 *    INPUT  graphics     The main display structure
 *           value        The number of frames per second.  30 is default
 *************************************************************************/
void setFramesPerSecond(Graphics &graphics, double value)
{
    graphics.timePeriod = (1 / value);
}

/************************************************************************
 * DRAW DIGIT
 * Draw a single digit in the old school line drawing style.  The
 * size of the glyph is 8x11 or x+(0..7), y+(0..10)
 *   INPUT  topLeft   The top left corner of the character
 *          digit     The digit we are rendering: '0' .. '9'
 *************************************************************************/
void drawDigit(const Point &topLeft, char digit)
{
   cout << "digit: " << digit
        << " (" << topLeft.x << "," << topLeft.y << ")\n";
}

/*************************************************************************
 * DRAW NUMBER
 * Display an positive integer on the screen using the 7-segment method
 *   INPUT  topLeft   The top left corner of the character
 *          digit     The digit we are rendering: '0' .. '9'
 *************************************************************************/
void drawNumber(const Point &topLeft, unsigned int number)
{
   cout << "number: " << number
        << " (" << topLeft.x << "," << topLeft.y << ")\n";
}

/************************************************************************
 * ROTATE
 * Rotate a given point (point) around a given origin (center) by a given
 * number of degrees (angle).
 *    INPUT  point    The point to be moved
 *           center   The center point we will rotate around
 *           rotation Rotation in degrees
 *    OUTPUT point    The new position
 *************************************************************************/
void rotate(Point &point, const Point &origin, int rotation)
{
   // because sine and cosine are expensive, we want to call them only once
   double cosA = cos(deg2rad(rotation));
   double sinA = sin(deg2rad(rotation));

   // remember our original point
   Point tmp;
   tmp.x = point.x - origin.x;
   tmp.y = point.y - origin.y;

   // find the new values
   point.x = static_cast<int> (tmp.x * cosA - tmp.y * sinA) + origin.x;
   point.y = static_cast<int> (tmp.x * sinA + tmp.y * cosA) + origin.y;
}

/************************************************************************
 * DRAW RECTANGLE
 * Draw a rectangle on the screen centered on a given point (center) of
 * a given size (width, height), and at a given orientation (rotation)
 *  INPUT  center    Center of the rectangle
 *         width     Horizontal size
 *         height    Vertical size
 *         rotation  Orientation
 *************************************************************************/
void drawRect(const Point &center, char width, char height, int rotation)
{
   cout << "Rectangle: "
        << "(" << center.x << "," << center.y << ") "
        << (int)width << "x" << (int)height << " "
        << rotation << "degrees\n";
}

/************************************************************************
 * DRAW CIRCLE
 * Draw a circle from a given location (center) of a given size (radius).
 *  INPUT   center   Center of the circle
 *          radius   Size of the circle
 *          points   How many points will we draw it.  Larger the number,
 *                   the more line segments we will use
 *          rotation True circles are rotation independent.  However, if you
 *                   are drawing a 3-sided circle (triangle), this matters!
 *************************************************************************/
void drawCircle(const Point &center, char radius, int points, int rotation)
{
   cout << "Circle: "
        << "(" << center.x << "," << center.y << ")"
        << " radius=" << (int)radius
        << " points=" << (int)points << " "
        << rotation << " degrees\n";
}

/************************************************************************
 * DRAW LINE
 * Draw a line on the screen from the beginning to the end.
 *   INPUT  begin     The position of the beginning of the line
 *          end       The position of the end of the line
 *************************************************************************/
void drawLine(const Point &begin, const Point &end)
{
   cout << "Line: "
        << "(" << begin.x << "," << begin.y << ")"
        << " "
        << "(" << end.x << "," << end.y << ")\n";
}

/************************************************************************
 * DRAW DOT
 * Draw a single point on the screen, 2 pixels by 2 pixels
 *  INPUT point   The position of the dow
 *************************************************************************/
void drawDot(const Point &point)
{
   cout << "Dot: "
        << "(" << point.x << "," << point.y << ")\n";
}

/******************************************************************
 * RANDOM
 * This function generates a random number.  The user specifies
 * The parameters and the use for the number.
 *
 * Note that the uiGraphics.cpp version will simply call rand.
 * The uiText.cpp version will prompt the user so we can have
 * predictable "random" numbers.
 *    INPUT:   min, max : The number of values (min <= num <= max)
 *             use :      Text description of what the number is used for
 *    OUTPUT   <return> : Return the integer
 ****************************************************************/
int random(int min, int max, char *use)
{
   assert(min <= max);
   int num = min - 1;
   while (min > num || num > max)
   {
      cout << use << ": ";
      cin  >> num;
   }

   cin.ignore();
   return num;
}
