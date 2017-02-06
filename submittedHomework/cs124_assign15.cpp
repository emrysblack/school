/***********************************************************************
* Program:
*    Assignment 15, Calendar Display
*    Brother Helfrich, CS124
* Author:
*    Brady Field
* Summary: 
*    Displays a Calendar on the screen
*
*    Estimated:  1.5 hrs   
*    Actual:     0.0 hrs
*      Please describe briefly what was the most difficult part
************************************************************************/

#include <iostream>
#include <iomanip>
using namespace std;

// use a prototype
void displayTable(int numDays, int offset);

/**********************************************************************
* prompts for number of days in the month and the offset,
* then displays the calendar
***********************************************************************/
int main()
{
   int numDays;
   int offset;

   // prompts for number of days and the offset
   cout << "Number of days: ";
   cin >> numDays;
   cout << "Offset: ";
   cin >> offset;

   // call display
   displayTable(numDays, offset);
   
   return 0;
}

/***********************************************************************
* displays the calendar on screen
************************************************************************/
void displayTable(int numDays, int offset)
{
   // header
   cout << "  " << "Su  " << "Mo  " << "Tu  "
        << "We  " << "Th  " << "Fr  " << "Sa\n";
   // set up loops
   int counter = (offset * -1);
   int day = 1;
   int columnCounter = (2 + offset);
   int offsetCount = offset;
   cout << setw(4);

   // place offsets
   for (offsetCount; counter <= 0 && offsetCount < 6; counter++) 
      cout << "    ";
   while (day <= numDays) // place date numbers
   {
      // check if new line needed after next entry
      if (columnCounter++ % 7 == 0) 
      {
         cout << setw(4)
              << day
              << "\n";
         columnCounter = 1; // reset column counter for beginning of week
      }
      else
      {
         cout << setw(4)
              << day;
      }
      day += 1;
   }
   // only output new line if last day is not Saturday
   if (columnCounter != 1)
      cout << endl;
}
