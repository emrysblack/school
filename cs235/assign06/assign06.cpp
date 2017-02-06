/***********************************************************************
* Program:
*    Homework 06, Recursion
*    Brother Twitchell, cs235 
* Author:
*    Brady Field
* Summary:
*    This assignment requires you to change main and "moveObjects" so
*    "moveObjects" work recursively.  No other routines need to be
*    modified.  You may add parameters to moveObjects and modify main.
*    The classes do not need to be modified.
*
*    Note: to compile this program you must compile as follows
*           g++ -l ncurses assign6.cpp
***********************************************************************/

#include <ncurses.h>
#include <cstdlib>
#include <iostream>
#include <time.h>
#include <vector>
#include <unistd.h>
using namespace std;
bool gCursesStarted = false;   // This is set to true the first time
                               // the program enters curses mode.


/*****************************************************************
 * This class is used to create a rectangle graphic object.
 * This is drawn using the ncurses library.
 ****************************************************************/
class Rectangle
{
   public:
      Rectangle();
      Rectangle(int row, int col, int height, int width);
      void move(int row, int col);
      void draw();
      void erase();
      int getRow(){ return startRow;}
      int getCol(){ return startCol;}
      void setRow(int row){startRow = row;}
      void setCol(int col){startCol = col;}
      void setHeight(int theHeight) { height = theHeight;} 
      void setWidth(int theWidth){ width = theWidth;}

   private:
      int height;     // rectangle height in screen lines
      int width;      // rectangle width in screen columns
      int startRow;   // row for upper left corner of rectangle 
      int startCol;   // column of upper left corner of rectangle
};

/**********************************************************
*  This class contains a rectangle object and the row and
*  column change increment to be used when moving the figure.
**********************************************************/
class Figure
{
   public:
      Figure(int row, int col);
      void setRowChange(int rChange){rowChange = rChange;}
      void setColChange(int cChange){colChange = cChange;}
      int getRowChange() {return rowChange;}
      int getColChange() {return colChange;}

      Rectangle box;   // the figure type
   
   private:
      int rowChange;   // row change increment
      int colChange;   // column change increment
};

/*******************************************************
* constructor -
* creates a figure object setting its upper left corner
* to row and col. It also sets the default movement
* increment for the row and column to 1 and 1 respectively
*******************************************************/
Figure::Figure(int row, int col)
  : rowChange(1), colChange(1)
{
   box.setRow(row);
   box.setCol(col);
}

// **************************************************************
// function prototypes
// ***************************************************************
void endCurses();             // ends curses mode
void startCurses();           // start curses mode
int  getInt(string prompt, int maxIntSize, string errMsg);
void pause(int value);
void moveObjects(vector < Figure > &figures, int drawCnt, int delay, int figureCnt);


/*********************************************************************
* This program prompts the user for the number of objects they wish to
* draw.  It then draws the object, moves it to the next location and
* redraws the object. It simply illustrates the moving and redrawing
* of the object, giving the appearance of move across the screen and
* bouncing off edges of the screen.
*********************************************************************/  
int main()
{
   int delay = 10;     // number between 1 and 100; 1=fastest, 100 = slowest;
   int drawCnt = 1;    // number of times to draw each object instance
   int figureCnt = 1;  // number of instances to draw
   
   while (drawCnt > 0)
   {

      drawCnt = getInt("Number of times to draw object (0 to exit): ", 10000, 
                      "Invalid Entry - must be a between 0 - 10000!\n");
      
      if (drawCnt <= 0)
      {
         break;       // exit program 
      }

      //******************************************************************
      // ADD A NEW USER PROMPT HERE - get the number of object instances
      // use "getInt" to prompt the user for the number of instances.
      //******************************************************************
      
      figureCnt = getInt("How many object instances (1 to 100): ", 100,
                           "Invalid Entry - must be a number 1 - 100!\n");
                           
      delay  = getInt("Enter delay between moves (1 to 100): ", 100,
                         "Invalid Entry - must be a number 1 - 100!\n");

      startCurses();  // Enter curses mode.

      vector < Figure > figureVec;

      //*********************************************************************  
      // MODIFY THIS CODE BELOW TO HANDLE MULTIPLE "figure" INSTANCES.
      // REMOVE THIS FOR LOOP AND MODIFY "moveObjects" TO WORK RECURSIVELY.
      // ALSO MODIFY "moveObjects" TO ACCEPT A VARIABLE NUMBER OF OBJECT
      // INSTANCES. THIS MEANS YOU WILL NEED TO ADD ADDITIONAL "figure"
      // OBJECTS TO THE FIGURE VECTOR YOU MUST PROMPT THE USER FOR THE NUMBER
      // OF INSTANCES OF THE OBJECT.
      // BASED UPON THE VALUE YOU GET FROM THE USER. YOU MUST MOVE AND DISPLAY
      // ALL OBJECT INSTANCES "drawCnt" times in "moveObjects".
      //***********************************************************************
      int row = 1;
      int col = 1;
      Figure rectangle(row, col);     // create a figure instance
      for (int i = 0; i < figureCnt; i++) // push input number of elements
      {
         figureVec.push_back(rectangle); // store the object instance in the vector
         row += 5; // change position of next object
         col += 5;
         if (row > LINES - 5 || row < 1)
            row = 3; // set to number off five so it won't collide with other positions
         if (col > COLS - 5 || col < 1)
            col = 3; //  
         
         rectangle.box.setRow(row);
         rectangle.box.setCol(col);
      }
      moveObjects(figureVec, drawCnt, delay, figureCnt);  // Move the object to next position

      //***************************************************************************
      // END OF CODE TO BE MODIFIED
      //***************************************************************************
      
      // clear screen of any objects
      for (int i = 0; i < figureVec.size(); i++)
      {
         figureVec[i].box.erase();
      }
      refresh();    // Make sure any changes made become visible on screen.
      endCurses();  // end Curses mode
   }
}

/*******************************************************************
* MODIFY THIS FUNCTION TO WORK RECURSIVELY AND TO HANDLE MULTIPLE
* INSTANCES OF A "figure" OBJECT. ADD ANY NECESSARY PARAMETERS TO
* MAKE THIS FUNCTION WORK RECURSIVELY RATHER THAN REQUIRING A
* FOR LOOP TO MOVE THE OBJECT INSTANCES.
*
* Desc: This function moves and redraws the first object in the
*       figures vector.
*
* Inputs: figures  - vector containing one figure object.
* Outputs: figures - the "startRow" and "startCol" of the object instance
*                    in the figures vector is modified with a new location.
*******************************************************************/
void moveObjects(vector < Figure > &figures, int drawCnt, int delay, int figureCnt)
{
   int change;
   int colChange;
   int row;
   int col;
   for (int i = 0; i < figureCnt; i++)
   {
      // get the change increment value for moving the figure
      change = figures[i].getRowChange();
      colChange = figures[i].getColChange();
   
      // calculate the new row and col positions;
      row = figures[i].box.getRow() + change;
      col = figures[i].box.getCol() + colChange;

      // implements change of direction when object gets to the edge of screen
      // Makes it appear to bounce off window and change direction
      if (row > LINES - 5 || row < 1)
      {
         change = -change;
         col = col + colChange;
         if (col < 1) col = 1;
      }

      if (col > COLS - (colChange + 5) || col < 1)
      {
         row = row + change;
         change = -change;
         colChange = -colChange;
         col = col + colChange;
      }
      figures[i].setRowChange(change);
      figures[i].setColChange(colChange);
      figures[i].box.move(row, col);
   }

   if (drawCnt > 1) // recursive call
   {
      refresh();
      pause(delay);
      moveObjects(figures, drawCnt -1, delay, figureCnt);
   }
}

/************************************************************
* default constructor
* Initialize rectangle object to size 1 x 3
* and places in if upper left corner of the screen
* at row 1, col 1
************************************************************/
Rectangle::Rectangle()
{
   height = 1;   // rectangle height in screen rows
   width = 3;    // rectangle width in screen columns
   startRow = 1;
   startCol = 1;
}

/********************************************************************
* constructor
* inputs: row & col - upper left corner screen location of rectangle
*         height & width -  rectangle size (in rows and columns)
******************************************************************/
Rectangle::Rectangle(int row, int col, int theHeight, int theWidth)
{
   startRow = row;
   startCol = col;
   height = theHeight;
   width = theWidth;
}

/***************************************************************************
* draw()
* This routine draws the rectangle
* using special characters such as ACS_ULCORNER and ACS_VLINE.
* The frame extends from startRow to endRow vertically and from
* startCol to endCol horizontally.  (Rows and columns are numbered
* starting from 0.)  Note that the interior of the frame extends
* from startRow+1 to endRow-1 vertically and from startCol+1 to
* endCol-1 horizontally.
*************************************************************************/
void Rectangle::draw()
{
   int endRow = startRow + height;
   int endCol = startCol + width;
   mvaddch(startRow,startCol,ACS_ULCORNER);
   for (int i = startCol + 1; i < endCol; i++)
   {
      addch(ACS_HLINE);
   }
   addch(ACS_URCORNER);
   for (int i = startRow + 1; i < endRow; i++)
   {
      mvaddch(i,startCol,ACS_VLINE);
      mvaddch(i,startCol + width,ACS_VLINE);
   }
   mvaddch(endRow,startCol,ACS_LLCORNER);
   for (int i = startCol + 1; i < endCol; i++)
   {
      addch(ACS_HLINE);
   }
   addch(ACS_LRCORNER);
}

/********************************************************
* This routine erases the rectangle by writing spaces
* over the rectangles line characters
*******************************************************/
void Rectangle::erase()
{
   int endRow = startRow + height;
   int endCol = startCol + width;

   mvaddch(startRow,startCol,' ');
   for (int i = startCol + 1; i < endCol; i++)
   {
      addch(' ');
   }
   addch(' ');
   for (int i = startRow + 1; i < endRow; i++)
   {
      mvaddch(i, startCol,' ');
      mvaddch(i, endCol,' ');
   }
   mvaddch(endRow, startCol,' ');
   for (int i = startCol + 1; i < endCol; i++)
   {
      addch(' ');
   }
   addch(' ');
}

/*******************************************************************
* Desc:  This function moves the rectangle from its current
* location to the newly specified location.
* It first call erase(), then sets the new coordinates
* and draws the new rectangle.
*
* Inputs:  row, col -  rectangle upper left corner screen row and col 
*******************************************************************/
void Rectangle::move(int row, int col)
{
   erase();      // erase current object
   startRow = row;
   startCol = col;
   draw();      // draw at new location
}

/***********************************************************************
*  This function is used to create a time delay or pause.
**********************************************************************/
void pause(int value)
{
   unsigned long ulength = value * 1000;
   usleep(ulength);   //sleep time in microseconds; 
}

/************************************************************************
*  int getInt(string prompt, string errMsg)
*
*  Desc: Error safe - read integer routine
*        On error, this function will re-prompt for the integer
*        until there is no input error.
*
*  Inputs:  prompt - string used to prompt for the integer
*           maxSize - maximum integer size allowed.
*           errMsg - error message you wish displayed if you get an error.
*  Outputs: none
*  return:  integer <= maxSize - read from the console
**************************************************************************/
int getInt(string prompt, int maxSize, string errMsg)
{

   int integer;
   cout << prompt;
   cin >> integer;
   while (cin.fail () || integer < 0 || integer > maxSize )
   {
      cout << errMsg;
      cin.clear ();
      cin.ignore (128, '\n');
      cout << prompt;
      cin >> integer;
   }
   return integer;
}

/********************************************************************
* This will exit curses mode and return the console to the usual
* line-oriented input/output mode.  If it is called when curses
* mode is not in effect, it will have no effect.
*********************************************************************/
void endCurses()
{
   if (gCursesStarted && !isendwin())
   {
      endwin();
   }
}

/***********************************************************************
* This will put the console into curses mode.  If curses mode is being
* entered for the first time, the screen will be cleared.  If it is
* being re-entered after a call to endCurses(), then the previous
* screen contents will be restored.
***********************************************************************/
void startCurses()
{
   if (gCursesStarted)
   {
      refresh();
   }
   else
   {
      initscr();
      cbreak();
      noecho();
      intrflush(stdscr, false);
      keypad(stdscr, true);
      atexit(endCurses);  // Make sure endCurses() is called when program ends.
      gCursesStarted = true;
   }
}
