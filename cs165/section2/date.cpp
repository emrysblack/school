/***********************************************************************
* Program:
*    Assignment ##, ???? 
*    Brother Helfrich, CS165
* Author:
*    your name
* Summary: 
*    Implement the date manipulation functions specified in date.h
************************************************************************/

#include <iostream>
#include <cassert>
#include "date.h"
using namespace std;

// three fields in the date array
enum {DAY, MONTH, YEAR};

/**********************************************************************
 * INITIALIZE.  Initialize the year to 1/1/2000
 *  OUTPUT: date:  the adjusted date
 ***********************************************************************/
void initialize(Date &date)
{
   try
   {
      date.data = new int[3];
      assert(date.data != NULL); // exception handling should catch this
   }
   catch (bad_alloc)
   {
      cerr << "ERROR: Unable to allocate only 12 bytes of data!\n";
      exit(1);
   }
   date.data[DAY] = 1;
   date.data[MONTH] = 1;
   date.data[YEAR] = 2000;
   assertDate(date);
}

/********************************************************
 * UNINITIALIZE.  Free up the memory we allocated
 *  INPUT:  date:  What we will be freeing up
 *  OUTPUT: date:  No longer ready for use
 ********************************************************/
void uninitialize(Date &date)
{
   delete [] date.data;
   date.data = NULL;
}

/**********************************************************************
 * SET YEAR.  Set the year to a given value.  Validate it
 *  INPUT: date:   the current date.  Will only use month and day
 *         year:   the new year
 *  OUTPUT: date:  the adjusted date
 *          return whether we succeeded
 ***********************************************************************/
bool setYear(Date &date, int year)
{
   assertDate(date);

   if (year < 1753 || year > 2500)
      return false;

   date.data[YEAR] = year;
   assertDate(date);
   return true;
}

/**********************************************************************
 * SET Month.  Set the month to a given value.  Validate it
 *  INPUT: date:   the current date.  Will only use month and day
 *         month:   the new month
 *  OUTPUT: date:  the adjusted date
 *          return whether we succeeded
 ***********************************************************************/
bool setMonth(Date &date, int month)
{
   assertDate(date);

   if (month < 1 || month > 12)
      return false;

   date.data[MONTH] = month;
   assertDate(date);
   return true;
}

/**********************************************************************
 * SET DAY.  Set the day to a given value.  Validate it
 *  INPUT: date:   the current date.  Will only use month and day
 *         day:   the new day
 *  OUTPUT: date:  the adjusted date
 *          return whether we succeeded
 ***********************************************************************/
bool setDay(Date &date, int day)
{
   assertDate(date);

   if (day < 1 || day > daysMonth(date.data[MONTH], date.data[YEAR]))
      return false;

   date.data[DAY] = day;
   assertDate(date);
   return true;
}

/*********************************************************
 * SET DATE.  Set all 3 fields of the date type and doing error checking
 *   INPUT  day    Day between 1 and 31 (or 28, depending)
 *          month  Month between 1 and 12
 *          year   After 1753, before something crazy
 *   OUTPUT date   The newly formed type
 *          return Success?
 **********************************************************/
bool setDate(Date &date, int year, int month, int day)
{
   // validation
   if (year < 1753 || day > 2500)
      return false;
   if (month < 1 || month > 12)
      return false;
   if (day < 1 || day > daysMonth(month, year))
      return false;

   // assignment
   date.data[YEAR] = year;
   date.data[MONTH] = month;
   date.data[DAY] = day;

   assertDate(date);

   return true;
}

/***************************************************
 * ADJUST DAY.  Adjust the current date by a given number of days
 *  INPUT  date        date we are adjusting
 *         adjustment  how many days we will adjust
 *  OUTPUT date
 ***************************************************/
void adjustDay(Date &date, int adjustment)
{
   assertDate(date);
   int days = daysMonth(date.data[MONTH], date.data[YEAR]);

   // adjust down if negative
   while (adjustment < 0)
   {
      date.data[DAY]--;
      if (date.data[DAY] == 0)
      {
         date.data[DAY] = 28; // to keep it valid at all points in time
         adjustMonth(date, -1 /*adjustment*/);
         days = daysMonth(date.data[MONTH], date.data[YEAR]);
         date.data[DAY] = days; // last day of the new month
      }
      adjustment++;
   }

   // adjust up if positive
   while (adjustment > 0)
   {
      date.data[DAY]++;
      if (date.data[DAY] > days)
      {
         date.data[DAY] = 1; // first day of the new month
         adjustMonth(date, 1 /*adjustment*/);
         days = daysMonth(date.data[MONTH], date.data[YEAR]);
      }
      adjustment--;
   }

   assertDate(date);
}

/*********************************************************
 * ADJUST MONTH.  Adjust the current date by a given number of months
 *  INPUT  date       date we are adjusting
 *         adjustment how many months we will adjust
 *  OUTPUT date
 *********************************************************/
void adjustMonth(Date &date, int adjustment)
{
   assertDate(date);

   // adjust down if negative
   while (adjustment < 0)
   {
      date.data[MONTH]--;
      if (date.data[MONTH] == 0)
      {
         date.data[MONTH] = 12;  // last month of the new year
         adjustYear(date, -1 /*adjustment*/);
      }
      adjustment++;
   }

   // adjust up if positive
   while (adjustment > 0)
   {
      date.data[MONTH]++;
      if (date.data[MONTH] > 12)
      {
         date.data[MONTH] = 1; // first month of the new year
         adjustYear(date, 1 /*adjustment*/);
      }
      adjustment--;
   }

   assertDate(date);
}

/****************************************************
 * ADJUST YEAR.  Adjust the year bug a given number of years
 *  INPUT  date       date we are adjusting
 *         adjustment how many years we will adjust
 *  OUTPUT date
 *********************************************************/
void adjustYear(Date &date, int adjustment)
{
   assertDate(date);
   date.data[YEAR] += adjustment;
   assertDate(date);
}

/*****************************************************
 * DAYS MONTH.  How many days are there in the current month?
 *   INPUT  month    the month we are inquiring about
 *          year     we only care about this when month == 2
 *   OUTPUT return   return the number
 *****************************************************/
int daysMonth(int month, int year)
{
   if (month > 12 || month < 1)
   {
      assert(false);
      return 0;
   }
   
   const int DAYS[13] =
       /* JAN FEB MAR APR MAY JUN JUL AUG SEP OCT NOV DEC */
      { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

   // special case the one leap month
   if (month == 2 && isLeapYear(year))
      return 29;

   assert(month > 0 && month < 13);
   return DAYS[month];
}

/***********************************************
 * IS LEAP YEAR.  Is the passed year a leap year?
 *   INPUT   year    The current year
 *   OUTPUT  return  True if we are in a leap year
 **********************************************/
bool isLeapYear(int year)
{
   // no leap years before 1753
   assert(year >= 1753);

   // what, are you Buck Rogers?
   assert(year < 2500);

   // Not a leap year if not evenly divisible by 4
   // This will eliminate 75% of all years
   if (year % 4 != 0)
      return false; // 2001, 2002, 2003, 2005, etc.
   assert(year % 4 == 0);

   // Is a leap year if not divisible by 100
   // This will eliminate 96% of the rest
   if (year % 100 != 0)
      return true; // 1996, 2004, 2008, 2012, etc.
   // We better be 1800, 1900, 2000, 2100 at this point
   assert(year % 100 == 0);

   // Is a leap year if on the quad century
   if (year % 400 == 0)
      return true; // 1600, 2000, 2400, etc.
   // It better be something like 1800, 1900, 2100, etc.
   assert(year % 400 != 0);

   // the balance better be 1900, 1800, etc.
   assert(year == 1800 || year == 1900 || year == 2100 || year == 2200);
   return false;
}

/**********************************************
 * DISPLAY.  Display the current date
 *  INPUT date   the current date
 *        short  Are we using the short format?
 *********************************************/
void display(const Date &date, bool isShort)
{
   cout << "Current date: ";
   if (isShort)
      displayShort(date);
   else
      displayLong(date);
   cout << endl;
}

/**********************************************
 * DISPLAY SHORT.  Display the current date: 1/3/2010
 *  INPUT date   the current date
 *********************************************/
void displayShort(const Date &date)
{
   assertDate(date);
   cout << date.data[MONTH] << "/" << date.data[DAY] << "/" << date.data[YEAR];
}

/**********************************************
 * DISPLAY LONG.  Display the current date: 1st of October, 2009
 *  INPUT date   the current date
 *********************************************/
void displayLong(const Date &date)
{
   assertDate(date);

   // day
   cout << date.data[DAY];
   switch (date.data[DAY])
   {
      case 1:
      case 21:
      case 31:
         cout << "st";
         break;
      case 2:
      case 22:
         cout << "nd";
         break;
      case 3:
      case 23:
         cout << "rd";
         break;
      default:
         cout << "th";
   }
   
   // month
   const char MONTHS[12][10] =
      { "January", "February", "March",     "April",   "May",      "June",
        "July",    "August",   "September", "October", "November", "December"};

   cout << " of " << MONTHS[date.data[MONTH] - 1] << ", ";

   // year
   cout << date.data[YEAR];
}

#ifndef NDEBUG

/************************************************
 * ASSERT DATE.  Validate date
 *   INPUT date: the date to be validated
 ***********************************************/
void assertDateProc(const Date &date, const char *file, int line)
{
   // validate the year.  Keep it real
   if (date.data[YEAR] < 1753 || date.data[YEAR] > 2500)
   {
      cerr << "Assert: " << file << ": " << line
           << ": date.year=" << date.data[YEAR] << " outside valid range\n";
      exit(1);
   }

   // valide the month
   if (date.data[MONTH] < 1 || date.data[MONTH] > 12)
   {
      cerr << "Assert: " << file << ": " << line
           << ": date.month=" << date.data[MONTH] << " outside valid range\n";
      exit(1);
   }

   // finally the day.
   if (date.data[DAY] < 1
       || date.data[DAY] > daysMonth(date.data[MONTH], date.data[YEAR]))
   {
      cerr << "Assert: " << file << ": " << line
           << ": date.day=" << date.data[DAY] << " outside valid range\n";
      exit(1);
   }
}

#endif // NDEBUG
