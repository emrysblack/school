/***********************************************************************
* Program:
*    Assignment 24, Constructors and Destructors
*    Brother Boyer, CS165
* Author:
*    Brady Field
* Summary: 
*    This assignment is designed to illustrate the different
*    flavors of constructors, as well as the utility of destructors
*
*    Estimated:  1.0 hrs   
*    Actual:     0.5 hrs
*      It was easy
************************************************************************/

#include <iostream>
#include <cassert>
#include "date.h"
using namespace std;

/**********************************************************************
 * A simple driver program to exercise our constructors
 ***********************************************************************/
int main()
{
   // Call the default constructor
   Date date1;
   cout << "Default constructor: ";
   date1.displayLong();
   cout << endl;
   
   // Prompt the user for the Day, Month, and Year
   int year;
   int month;
   int day;
   cout << "Year:  ";
   cin  >> year;
   cout << "Month: ";
   cin  >> month; 
   cout << "Day:   ";
   cin  >> day;
   Date date2(year, month, day);
   cout << "Constructor with 3 parameters: ";
   date2.displayLong();
   cout << endl;

   // same, but with 1 parameter
   Date date3(year);
   cout << "Constructor with 1 parameter: ";
   date3.displayLong();
   cout << endl;
   
   // copy constructor
   Date date4(date2);
   cout << "Copy Constructor: ";
   date4.displayLong();
   cout << endl;
   
   return 0;
}
