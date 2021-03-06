/***********************************************************************
* Program:
*    Project 2, Calendar Program
*    Brother Helfrich, CS124
* Author:
*    Brady Field
* Summary: 
*    Create a calendar for any month of any year from 1753 forward
*    using user input for desired month and year.
*    
*    Estimated:  10.0 hrs   
*    Actual:     6.2 hrs
*      Implementing loop behavior
************************************************************************/

#include <iostream>
#include <iomanip>
using namespace std;

// set up prototypes
int getMonth();
int getYear();
int getOffset(int month, int year);
int daysYear(int year);
int daysMonth(int month, int year);
bool isLeapYear(int year);
void display(int year, int month);
void displayHeader(int year, int month);
void displayTable(int year, int month);

/**********************************************************************
* Call functions and collects year, month, and offset values
* PUT display
***********************************************************************/
int main()
{
   // collect variables from functions to pass on
   int month = getMonth();
   int year = getYear();
   
   // call function to display calendar
   display(year, month);
   return 0;
}

/**********************************************************************
* prompts user to input desired month number, checks to see if number
* is valid, and keeps prompting until user enters valid a number
* PROMPT month
* IF (month != 1 to 12)
*   PUT error for invalid month number
*   RETURN to PROMPT
* ELSE
* RETURN month
***********************************************************************/
int getMonth()
{
   int month;

   // at least run once, do-while loop is good
   do
   {
      cout << "Enter a month number: "; // prompt for month
      cin >> month;
      if ((month < 1) || (month > 12))
         cout << "Month must be between 1 and 12.\n"; 
   }
   while ((month < 1) || (month > 12));
   return month;
}

/**********************************************************************
* prompts user to input desired year, checks for validation, and
* will continue to prompt until a valid year is entered
* PROMPT year
*   IF (year < 1753)
*   PUT error for invalid year
*   RETURN to PROMPT year
* ELSE
* RETURN year
***********************************************************************/
int getYear()
{
   int year;
   do
   {
      cout << "Enter year: "; //prompt for year
      cin >> year; 
      if (year < 1753)
         cout << "Year must be 1753 or later.\n";
   }
   while (year < 1753);
   return year;
}

/**********************************************************************
* calculates which day of the week the desired month starts on based
* January 1, 1753 being Monday
*
* WHILE year-- > 1753
* IF is Leap
*   ADD 366 to days
* ELSE
*   ADD 365 to days
* WHILE month-- > 1
*   ADD days Month results to days
* RETURN modulus of total days
***********************************************************************/
int getOffset(int month, int year)
{
   int numDays = 0;
   
   /* use year Count so not change value of year
      for parameters in second Loop*/
   
   int yearCount = year;
   
   // don't want to confuse values   
   int monthCount = month; 
   while (yearCount-- > 1753)
      numDays += 365 + isLeapYear(yearCount);
   
   while (monthCount-- > 1)
      numDays += daysMonth(monthCount, year);
   return numDays % 7;
}

/**********************************************************************
* determines if a year has 365 or 366 days in it by calling a function
* to calculate if the input year is a leap year
* IF is Leap
*   RETURN 366
* ELSE
*   RETURN 365
***********************************************************************/
int daysYear(int year)
{
   return 365 + isLeapYear(year);
}

/**********************************************************************
* determines if a month has 30 or 31 days in it, or if February has
* 28 or 29 days
* IF month is big
*   RETURN 31;
* IF month is small
*   RETURN 30
* IF is Leap
*   RETURN 29
* ELSE
*   RETURN 28
***********************************************************************/
int daysMonth(int month, int year)
{
   // February
   if (month == 2)
      return 28 + isLeapYear(year);

   // short months have 30
   else if ((month == 4) || (month == 6) || (month == 9) || (month == 11))
      return 30;

   // big months have 31 days
   else
      return 31;
}

/**********************************************************************
* determines if the input year is a leap year or not
* IF year / 4 remainder is not 0
*   not Leap
* ELSE IF year / 100 remainder is not 0
*   is Leap
* ELSE IF year / 400 remainder is 0
*   is Leap
* ELSE
*   not Leap
***********************************************************************/
bool isLeapYear(int year)
{
   return year % 4 == 0 && ((year % 100 != 0) || (year % 400 == 0));
}

/**********************************************************************
* calls 2 functions to display calendar
*
* PUT display header
* PUT display table
***********************************************************************/
void display(int year, int month)
{
   displayHeader(year, month);
   displayTable(year, month);
   return;
}

/**********************************************************************
* displays a header above Calendar with corresponding month name
* and year of input
* IF
*   month is 1 = January, 2 = February, 3 = March.... 12 = December
* DISPLAY
*    month, year
***********************************************************************/
void displayHeader(int year, int month)
{
   
   cout << endl;
   switch (month)
   {
      case 1:
         cout << "January";
         break;
      case 2:
         cout << "February";
         break;
      case 3:
         cout << "March";
         break;
      case 4:
         cout << "April";
         break;
      case 5:
         cout << "May";
         break;
      case 6:
         cout << "June";
         break;
      case 7:
         cout << "July";
         break;
      case 8:
         cout << "August";
         break;
      case 9:
         cout << "September";
         break;
      case 10:
         cout << "October";
         break;
      case 11:
         cout << "November";
         break;
      case 12:
         cout << "December";
         break;
      default:
         cout << "Error : " << month  << " is not a valid Month";
   }
   cout << ", " << year << endl;
   return;
}

/**********************************************************************
* puts actual generated Calendar on the screen
*
* PUT days of week
* FOR offset counter < 0
*   PUT blank spaces
* WHILE column counter % 7 has remainder
*   PUT day
* ELSE
*   PUT new line and then day
***********************************************************************/
void displayTable(int year, int month)
{
   // header
   cout << "  Su  Mo  Tu  We  Th  Fr  Sa\n";
   
   // set up variables for loops
   int numDays = daysMonth(month, year);
   int offset = getOffset(month, year);
   int columnCounter = (2 + offset);

   // loop to place offsets
   for (int counter = offset * -1; counter <= 0 && offset < 6; counter++)
      cout << setw(4) << " ";

   // place date numbers
   for (int day = 1; day <= numDays; day++) 
   {
      cout << setw(4)
           << day;
      // check if new line needed after next entry
      if (columnCounter++ % 7 == 0)
      {
         cout << endl;
         columnCounter = 1; // reset counter for beginning of week
      }
   }
   if (columnCounter != 1) // only output new line if last day is not Saturday
      cout << endl; 
}


