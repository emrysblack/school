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
*    Actual:     0.2 hrs
*      Easy, but I don't understand why it works. The parameters part
************************************************************************/

#include <iostream>
using namespace std;

/**********************************************************************
* sets display settings, converts parameters into a float, computes
* feet to meters and displays
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
