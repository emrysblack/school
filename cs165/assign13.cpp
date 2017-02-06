/***********************************************************************
* Program:
*    Assignment 13, Structures
*    Brother Boyer, CS165
* Author:
*    Brady Field
* Summary: 
*    This program will prompt the user for the values in a structure,
*    then display the results on the screen.  It will include an example
*    of pass-by-reference and pass-by-pointer.  The structure has 2 parts:
*       col     Position on the horizontal axis.  This should be an integer
*       row     Position on the vertical axis
*
*    Estimated:  1.0 hrs   
*    Actual:     4.0 hrs
*      pass by pointer syntax for structures
************************************************************************/

#include <iostream>
using namespace std;

struct Position
{
   int col;
   int row;
};

/***********************************************************************
 * fills x and y coordinates
 ***********************************************************************/
bool prompt(Position &pos)
{
   cout << "X coordinate: ";
   cin >> pos.col;
   cout << "Y coordinate: ";
   cin >> pos.row;
   return true;
}

/***********************************************************************
 * displays the coordinates
 ***********************************************************************/
void display(Position *pos)
{
   cout << "("
        << pos->col
        << ", "
        << pos->row
        << ")\n";
}
/**********************************************************************
 * MAIN. Simple driver program calling two functions
 *   prompt:  Prompt the user for the values
 *   display: Display the data of the position on the screen
 ***********************************************************************/
int main()
{
   Position pos;

   // get the data
   prompt(pos);

   // display the data
   display(&pos);
   
   return 0;
}
