/***********************************************************************
* Program:
*    Assignment 13, Days since 1753
*    Brother Helfrich, CS124
* Author:
*    Brady Field
* Summary: 
*    
*    Displays number of days passed since 1753 and an
*    input year
*    
*    Estimated:  1.5 hrs   
*    Actual:     2.5 hrs
*      used an assignment operator instead of comparison- took me forever
*      to find.
************************************************************************/

#include <iostream>
using namespace std;

bool isLeapYear(int year);
int computeDays (int year);

/**********************************************************************
* Prompts user to input a year and displays number of days between
* year and 1753
***********************************************************************/
int main()
{
   int year;

   cout << "Year: ";
   cin >> year;
   int numDays = computeDays(year);
   cout << "Number of days: " << numDays << endl;
   return 0;
}

/**********************************************************************
* Determines if a given year is a leap year or not
***********************************************************************/
bool isLeapYear(int year)
{
   if (year % 4 != 0)
      return false;
   else if (year % 100 != 0)
      return true;
   else if (year % 400 == 0)
      return true;
   else
      return false;
}

/**********************************************************************
* Calculates difference of days between 1753 and target year
***********************************************************************/
int computeDays(int year)
{
   
   int numDays = 0;
   bool isLeap;
   while (year-- > 1753)
   {
      isLeap = isLeapYear(year);
      if (isLeap == true)
         numDays += 366;
      else
         numDays += 365;
   }
   return numDays;
}
