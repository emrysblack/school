/***********************************************************************
 * Program:
 *    Project 2, UI header
 *    Brother Helfrich, CS165
 * Author:
 *    Br. Helfrich
 * Summary:
 *    This is the header for the user interface.  Note that both
 *    the OpenGL version (uiGraphics.cpp) and the text version (uiText.cpp)
 *    implement these interfaces.
 ************************************************************************/

#include <string>
using namespace std;

// ratio between board size and screen size
#define MULTIPLIER 2

/*********************************************
 * POINT
 * A single position.  
 *********************************************/
struct Point
{
   float x;
   float y;
};

/********************************************
 * GRAPHICS
 * All the data necessary to keep our graphics
 * state in memory
 ********************************************/
struct Graphics
{
   double timePeriod;         // interval between frame draws
   unsigned int nextTick;     // time (from clock()) of our next draw

   int isDownPress;          // is the down arrow currently pressed?
   int isUpPress;            //    "   up         "
   int isLeftPress;          //    "   left       "
   int isRightPress;         //    "   right      "
   bool isSpacePress;        //    "   space      "
   
   void *p;                   // for client
   void (*callBack)(const Graphics *, void *);
};

/*********************************************
 * NUMBER OUTLINES
 * We are drawing the text for score and things
 * like that by hand to make it look "old school."
 * These are how we render each individual charactger.
 * Note how -1 indicates "done".  These are paired
 * coordinates where the even are the x and the odd
 * are the y and every 2 pairs represents a point
 ********************************************/
const char NUMBER_OUTLINES[10][20] =
{
  {0, 0,  7, 0,   7, 0,  7,10,   7,10,  0,10,   0,10,  0, 0,  -1,-1, -1,-1},//0
  {7, 0,  7,10,  -1,-1, -1,-1,  -1,-1, -1,-1,  -1,-1, -1,-1,  -1,-1, -1,-1},//1
  {0, 0,  7, 0,   7, 0,  7, 5,   7, 5,  0, 5,   0, 5,  0,10,   0,10,  7,10},//2
  {0, 0,  7, 0,   7, 0,  7,10,   7,10,  0,10,   4, 5,  7, 5,  -1,-1, -1,-1},//3
  {0, 0,  0, 5,   0, 5,  7, 5,   7, 0,  7,10,  -1,-1, -1,-1,  -1,-1, -1,-1},//4
  {7, 0,  0, 0,   0, 0,  0, 5,   0, 5,  7, 5,   7, 5,  7,10,   7,10,  0,10},//5
  {7, 0,  0, 0,   0, 0,  0,10,   0,10,  7,10,   7,10,  7, 5,   7, 5,  0, 5},//6
  {0, 0,  7, 0,   7, 0,  7,10,  -1,-1, -1,-1,  -1,-1, -1,-1,  -1,-1, -1,-1},//7
  {0, 0,  7, 0,   0, 5,  7, 5,   0,10,  7,10,   0, 0,  0,10,   7, 0,  7,10},//8
  {0, 0,  7, 0,   7, 0,  7,10,   0, 0,  0, 5,   0, 5,  7, 5,  -1,-1, -1,-1} //9
};

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
void drawCallback();

/************************************************************************
 * KEY DOWN CALLBACK
 * When a key on the keyboard has been pressed, we need to pass that
 * on to the client.  Currnetly, we are only registering the arrow keys
 *************************************************************************/
void keyDownCallback(int key, int x, int y);

/************************************************************************
 * KEY UP CALLBACK
 * When the user has released the key, we need to reset the pressed flag
 *************************************************************************/
void keyUpCallback(int key, int x, int y);

/**************************************************
 * INITIALIZE GRAPHIC GLOBAL
 * Because we are denied the dignity of initializing our
 * graphic state as a local variable, we must write a function
 * to do this.  This function is called from initialize()
 **************************************************/
void initializeGraphicGlobal(void (*callBack)(const Graphics *, void *),
                             void *p);

/************************************************************************
 * IS TIME TO DRAW
 * Have we waited long enough to draw swap the background buffer with
 * the foreground buffer?
 *************************************************************************/
bool isTimeToDraw(Graphics &graphics);

/************************************************************************
 * SET NEXT DRAW TIME
 * What time should we draw the buffer again?  This is a function of
 * the current time and the frames per second.
 *************************************************************************/
void setNextDrawTime(Graphics &graphics);

/************************************************************************
 * SET FRAMES PER SECOND
 * The frames per second dictates the speed of the game.  The more frames
 * per second, the quicker the game will appear to the user.  We will default
 * to 30 frames/second but the client can set this at will.
 *************************************************************************/
void setFramesPerSecond(Graphics &graphics, double value);

/************************************************************************
 * DRAW DIGIT
 * Draw a single digit in the old school line drawing style.  The
 * size of the glyph is 8x11 or x+(0..7), y+(0..10)
 *************************************************************************/
void drawDigit(const Point &topLeft, char digit);

/*************************************************************************
 * DRAW NUMBER
 * Display an positive integer on the screen using the 7-segment method
 *************************************************************************/
void drawNumber(const Point &topLeft, unsigned int number);

/************************************************************************
 * ROTATE
 * Rotate a given point (point) around a given origin (center) by a given
 * number of degrees (angle).
 *************************************************************************/
void rotate(Point &point, const Point &origin, int rotation);

/************************************************************************
 * DRAW RECTANGLE
 * Draw a rectangle on the screen centered on a given point (center) of
 * a given size (width, height), and at a given orientation (rotation)
 *************************************************************************/
void drawRect(const Point &center, char width, char height, int rotation);

/************************************************************************
 * DRAW CIRCLE
 * Draw a circle from a given location (center) of a given size (radius).
 *************************************************************************/
void drawCircle(const Point &center, char radius, int points, int rotation);

/************************************************************************
 * DRAW LINE
 * Draw a line on the screen from the beginning to the end.
 *************************************************************************/
void drawLine(const Point &begin, const Point &end);

/************************************************************************
 * DRAW DOT
 * Draw a single point on the screen, 2 pixels by 2 pixels
 *************************************************************************/
void drawDot(const Point &point);

/************************************************************************
 * RUN
 * Set the game in action.  We will get control back in our drawCallback
 *************************************************************************/
void run();

/************************************************************************
 * INITIALIZE
 * Initialize our drawing window.  This will set the size and position,
 * get ready for drawing, set up the colors, and everything else ready to
 * draw the window.  All these are part of initializing Open GL.
 *************************************************************************/
void initialize(int argc, char* argv[], string title,
                void (*callBack)(const Graphics *, void *), void *p);


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
int random(int min, int max, char *use);
