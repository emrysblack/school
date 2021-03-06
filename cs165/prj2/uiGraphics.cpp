/***********************************************************************
 * Program:
 *    Project 2, Graphics code
 *    Brother Helfrich, CS165
 * Author:
 *    Br. Helfrich
 * Summary:
 *    This is the procedural code necessary to draw on the screen. While
 *    this works, you will need to make an Object Oriented version of
 *    this code for Project 2
 ************************************************************************/

#include <cmath>      // for M_PI, sin() and cos()
#include <string>     // need you ask?
#include <sstream>    // convert an integer into text
#include <cassert>    // I feel the need... the need for asserts
#include <GL/gl.h>    // Main OpenGL library
#include <GL/glut.h>  // Second OpenGL library
#include <GL/glu.h>
#include <time.h>     // for clock
#include <stdlib.h>   // for rand()

#include "ui.h"


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
 * DRAW CALLBACK
 * This is the main callback from OpenGL. It gets called constantly by
 * the graphics engine to refresh and draw the window.  Here we will
 * clear the background buffer, draw on it, and send it to the forefront
 * when the appropriate time period has passsed.
 *
 * Note: This and all other callbacks can't be member functions, they must
 * have global scope for OpenGL to see them.
 *************************************************************************/
void drawCallback()
{
   // Prepare the background buffer for drawing
   glClear(GL_COLOR_BUFFER_BIT); //clear the screen
   glColor3f(1,1,1);
   
   //calls the programmers display function
   assert(graphicGlobal.callBack != NULL);
   graphicGlobal.callBack(&graphicGlobal, graphicGlobal.p);
   
   //loop until the timer runs out
   while(!isTimeToDraw(graphicGlobal))
      ;

   // from this point, set the next draw time
   setNextDrawTime(graphicGlobal);

   // bring forth the background buffer
   glutSwapBuffers();

   // clear the space key event; we don't get key-up like the arrow keys!
   graphicGlobal.isSpacePress = false;

   // if the keyboard press flag is set, then add one to it with
   // every frame so we can know how long it has been pressed.  This
   // is only important if we want to do keyboard acceleration.  Note
   // that the keyRepeat event will occur in about .5 seconds (system
   // setting which you can modify in the control panel), which
   // will cancel this out.  At that point, a keyUpCallback() event will
   // occur and we will loose our acceleration. At this point, it will
   // stop moving.  I wish we could fix this.
   if (graphicGlobal.isUpPress)
      graphicGlobal.isUpPress++;
   if (graphicGlobal.isDownPress)
      graphicGlobal.isDownPress++;
   if (graphicGlobal.isLeftPress)
      graphicGlobal.isLeftPress++;
   if (graphicGlobal.isRightPress)
      graphicGlobal.isRightPress++;
}

/************************************************************************
 * KEY DOWN CALLBACK
 * When a key on the keyboard has been pressed, we need to pass that
 * on to the client.  Currnetly, we are only registering the arrow keys
 *   INPUT   key:   the key we pressed according to the GLUT_KEY_ prefix
 *           x y:   the position in the window, which we ignore
 *************************************************************************/
void keyDownCallback(int key, int x, int y)
{
   // Remember of a key is pressed
   switch(key)
   {
      case GLUT_KEY_DOWN:
         graphicGlobal.isDownPress = 1;
         break;
      case GLUT_KEY_UP:
         graphicGlobal.isUpPress = 1;
         break;
      case GLUT_KEY_RIGHT:
         graphicGlobal.isRightPress = 1;
         break;
      case GLUT_KEY_LEFT:
         graphicGlobal.isLeftPress = 1;
         break;
   }
}

/************************************************************************
 * KEY UP CALLBACK
 * When the user has released the key, we need to reset the pressed flag
 *   INPUT   key:   the key we pressed according to the GLUT_KEY_ prefix
 *           x y:   the position in the window, which we ignore
 *************************************************************************/
void keyUpCallback(int key, int x, int y)
{
   // forget if a key was pressed
   switch(key)
   {
      case GLUT_KEY_DOWN:
         graphicGlobal.isDownPress = 0;
         break;
      case GLUT_KEY_UP:
         graphicGlobal.isUpPress = 0;
         break;
      case GLUT_KEY_RIGHT:
         graphicGlobal.isRightPress = 0;
         break;
      case GLUT_KEY_LEFT:
         graphicGlobal.isLeftPress = 0;
         break;
   }
}

/***************************************************************
 * KEYBOARD CALLBACK
 * Generic callback to a regular ascii keyboard event, such as
 * the space bar or the letter 'q'
 ***************************************************************/
void keyboardCallback(unsigned char key, int x, int y)
{
   switch (key)
   {
      case ' ':
         graphicGlobal.isSpacePress = true;
         break;
   }
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
   // we better be only drawing digits
   assert(isdigit(digit));
   if (!isdigit(digit))
      return;

   // compute the row as specified by the digit
   int r = digit - '0';
   assert(r >= 0 && r <= 9);

   // go through each segment.
   for (int c = 0; c < 20 && NUMBER_OUTLINES[r][c] != -1; c += 4)
   {
      assert(NUMBER_OUTLINES[r][c    ] != -1 &&
             NUMBER_OUTLINES[r][c + 1] != -1 &&
             NUMBER_OUTLINES[r][c + 2] != -1 &&
             NUMBER_OUTLINES[r][c + 3] != -1);

      //Draw a line based off of the num structure for each number
      Point start;
      start.x = topLeft.x + NUMBER_OUTLINES[r][c];
      start.y = topLeft.y - NUMBER_OUTLINES[r][c + 1];
      Point end;
      end.x = topLeft.x + NUMBER_OUTLINES[r][c + 2];
      end.y = topLeft.y - NUMBER_OUTLINES[r][c + 3];
         
      drawLine(start, end);
   }
}

/*************************************************************************
 * DRAW NUMBER
 * Display an positive integer on the screen using the 7-segment method
 *   INPUT  topLeft   The top left corner of the character
 *          digit     The digit we are rendering: '0' .. '9'
 *************************************************************************/
void drawNumber(const Point &topLeft, unsigned int number)
{
   // render the number as text
   ostringstream sout;
   sout << number;
   string text = sout.str();

   // walk through the text one digit at a time
   Point point = topLeft;
   for (const char *p = text.c_str(); *p; p++)
   {
      assert(isdigit(*p));
      drawDigit(point, *p);
      point.x += 11;
   }
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
   // a few variables for convenience
   Point center2; // 2x center for scaling
   center2.x = center.x * MULTIPLIER;
   center2.y = center.y * MULTIPLIER;
   int w = width  * MULTIPLIER;
   int h = height * MULTIPLIER;

   Point tl; // top left
   Point tr; // top right 
   Point bl; // bottom left
   Point br; // bottom right

   //Top Left point
   tl.x = center2.x - (w / 2);
   tl.y = center2.y + (h / 2);

   //Top right point
   tr.x = center2.x + (w / 2);
   tr.y = center2.y + (h / 2);

   //Bottom left point
   bl.x = center2.x - (w / 2);
   bl.y = center2.y - (h / 2);

   //Bottom right point
   br.x = center2.x + (w / 2);
   br.y = center2.y - (h / 2);

   //Rotate all points the given degrees
   rotate(tl, center2, rotation);
   rotate(tr, center2, rotation);
   rotate(bl, center2, rotation);
   rotate(br, center2, rotation);

   //Finally draw the rectangle
   glBegin(GL_LINE_STRIP);
   glVertex2f(tl.x, tl.y);
   glVertex2f(tr.x, tr.y);
   glVertex2f(br.x, br.y);
   glVertex2f(bl.x, bl.y);
   glVertex2f(tl.x, tl.y);
   glEnd();
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
   // begin drawing
   glBegin(GL_LINE_LOOP);

   //loop around a circle the given number of times drawing a line from
   //one point to the next
   Point center2;
   center2.x   = center.x * MULTIPLIER; // for speed
   center2.y   = center.y * MULTIPLIER;
   float r = radius * 2; 
   for (double i = 0; i < 2 * M_PI; i += (2 * M_PI) / points)
   {
      Point temp;
      temp.x = center2.x + static_cast<int>(r * cos(i));
      temp.y = center2.y + static_cast<int>(r * sin(i));
      rotate(temp, center2, rotation);
      glVertex2f(temp.x, temp.y);
   }
   
   // complete drawing
   glEnd();

}

/************************************************************************
 * DRAW LINE
 * Draw a line on the screen from the beginning to the end.
 *   INPUT  begin     The position of the beginning of the line
 *          end       The position of the end of the line
 *************************************************************************/
void drawLine(const Point &begin, const Point &end)
{
   // Get ready...
   glBegin(GL_LINES);

   // Note how we scale the lines by a factor of two
   glVertex2f(begin.x * MULTIPLIER, begin.y * MULTIPLIER);
   glVertex2f(end.x   * MULTIPLIER, end.y   * MULTIPLIER);

   // complete drawing.
   glEnd();
}

/************************************************************************
 * DRAW DOT
 * Draw a single point on the screen, 2 pixels by 2 pixels
 *  INPUT point   The position of the dow
 *************************************************************************/
void drawDot(const Point &point)
{
   // Get ready, get set...
   glBegin(GL_POINTS);

   // Go...
   glVertex2f(point.x * MULTIPLIER,     point.y * MULTIPLIER   );
   glVertex2f(point.x * MULTIPLIER + 1, point.y * MULTIPLIER   );
   glVertex2f(point.x * MULTIPLIER + 1, point.y * MULTIPLIER + 1);
   glVertex2f(point.x * MULTIPLIER,     point.y * MULTIPLIER + 1);

   // Done!  OK, that was a bit too dramatic
   glEnd();
}

/************************************************************************
 * RUN
 * Set the game in action.  We will get control back in our drawCallback
 *************************************************************************/
void run()
{
    glutMainLoop();
}

/************************************************************************
 * INITIALIZE
 * Initialize our drawing window.  This will set the size and position,
 * get ready for drawing, set up the colors, and everything else ready to
 * draw the window.  All these are part of initializing Open GL.
 *  INPUT    argc:       Count of command-line arguments from main
 *           argv:       The actual command-line parameters
 *           title:      The text for the titlebar of the window
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
   // seed the random number
   srand(atoi(*argv));

   // the indignity!
   initializeGraphicGlobal(callBack, p);
   
   // create the window
   glutInit(&argc, argv);
   glutInitWindowSize(512,512);                  // size of the window
   glutInitWindowPosition(10,50);                // initial position 
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);  // double buffering
   glutCreateWindow(title.c_str());              // text on titlebar

   // set up the drawing style: B/W and 2D
   glClearColor(0,0,0,0);          // Black is the background color
   gluOrtho2D(-256,256,-256,256);  // 2D environment

   // register the callbacks so OpenGL knows how to call us
   glutDisplayFunc(drawCallback);
   glutIdleFunc(drawCallback);
   glutSpecialFunc(keyDownCallback);
   glutSpecialUpFunc(keyUpCallback);
   glutKeyboardFunc(keyboardCallback);

   return;
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
   int num = (rand() % (max - min)) + min;
   assert(min <= num && num <= max);

   return num;
}

