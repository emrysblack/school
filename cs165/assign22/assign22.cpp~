/***********************************************************************
* Program:
*    Assignment 22, Simple Date class
*    Brother Helfrich, CS165
* Author:
*    your name
* Summary: 
*    This is a driver program for a simple date class.  Your job is
*    to write date.h and date.cpp.  This file is to remain untouched.
************************************************************************/

#include <iostream>
#include "date.h"
using namespace std;

/**********************************************************************
 * Just a very simple driver program.
 ***********************************************************************/
int main()
{
   Date date;
   date.initialize();

   cout << "Instructions: Keep prompting the user for a date until the\n"
        << "              year 0 is specified.\n";

   bool done = false;
   do
   {
      int year;

      // prompt for year
      cout << "Year:  ";
      cin  >> year;

      if (year == 0)
         done = true;
      else
      {
         int month;
         int day;

         // prompt for rest
         cout << "Month: ";
         cin  >> month;
         cout << "Day:   ";
         cin  >> day;

         // set and display
         date.setDate(year, month, day);
         cout << "\t";
         date.displayLong();
         cout << endl;
      }
   }
   while (!done);
    
   // make like a tree
   date.uninitialize();
   return 0;
}
