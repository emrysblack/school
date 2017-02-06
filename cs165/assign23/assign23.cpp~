/***********************************************************************
* Program:
*    Assignment 23, Getters and Setters
*    Brother Helfrich, CS165
* Author:
*    your name
* Summary: 
*    This assignment is designed to illustrate the design principle of getters
*    and setters.
*
*    Estimated:  0.0 hrs   
*    Actual:     0.0 hrs
*      Please describe briefly what was the most difficult part
************************************************************************/

#include <iostream>
#include <cassert>
#include "date.h"
using namespace std;

/**********************************************************************
 * A simple driver program to exercise our getters and setters
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
      int month;
      int day;

      // prompt for year
      cout << "Year:  ";
      cin  >> year;
      if (!date.setYear(year))
         done = true;

      // prompt for month
      if (!done)
      {
         cout << "Month: ";
         cin  >> month;
         if (!date.setMonth(month))
            done = true;
      }

      // prompt for day
      if (!done)
      {
         cout << "Day:   ";
         cin  >> day;
         if (!date.setDay(day))
            done = true;
      }

      // display
      if (!done)
      {
         assert(day == date.getDay());
         assert(month == date.getMonth());
         assert(year == date.getYear());

         cout << "\t";
         date.displayLong();
         cout << endl;
      }
   }
   while (!done);
   
   date.uninitialize();
   return 0;
}
