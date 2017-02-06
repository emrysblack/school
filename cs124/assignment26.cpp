/***********************************************************************
* Program:
*    Assignment 26, Feet to Meters
*    Brother Helfrich, CS124
* Author:
*    Brady Field
* Summary: 
*    A simple program that accepts parameters from the command line
*    and converts feet to meters
*
*    Estimated:  1.0 hrs   
*    Actual:     0.0 hrs
*      Please describe briefly what was the most difficult part
************************************************************************/

#include <iostream>
using namespace std;

/**********************************************************************
* Add text here to describe what the function "main" does. Also don't forget
* to fill this out with meaningful text or YOU WILL LOOSE POINTS.
***********************************************************************/
int main(int argc, char **argv)
{
   // set display
   cout.setf(ios::fixed);
   cout.setf(ios::showpoint);
   cout.precision(1);
   for (int i = 1; i < argc; i++)
   {
      cout << atof(argv[i])
           << " feet is "
           << atof(argv[i]) * 0.3048
           << " meters\n";
   }
   return 0;
}
