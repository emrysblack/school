/***********************************************************************
* Program:
*    Assignment 31, Building Polymorphism
*    Brother Boyer, CS165
* Author:
*    Brady Field
* Summary: 
*    This program will demonstrate the implementation of polymorphism
*    based on two procedural tools: pointers to functions, and structures.
*
*    Your assignment is to create three functions which may be binded
*    to our Date structure:
*            displayLong():  Borrowed from displayLong ();
*            displayShort(): Borrowed from displayShort();
*            displayNone():  This function will have an empty body.
*    Each of these three functions is prototyped in the driver program.
*    Next, create a fourth function which will perform the binding.
*    In our case, we will need to bind pDate->set with our setDate()
     function, and to bind the correct date function with pDate->display.
*
*    Estimated:  1.0 hrs   
*    Actual:     1.0 hrs
*      It was easy, but hard to figure out what was wanted of me exactly
************************************************************************/

#include <iostream>
#include <cassert>
using namespace std;

enum DateType {NONE, SHORT, LONG};

/****************************************
 * DATE
 *  Our home-made class.  You are not allowed
 *  to change the definition of Date in any way
 ***************************************/
struct Date
{
   void (*display)(Date *pThis);
   bool (*set)(Date *pThis, int year, int month, int day);

   int year;
   int month;
   int day;
};

// generic prototypes
bool isLeapYear(int year);
int daysMonth(int month, int year);

// prototypes used for pDate->set and pDate->display
void displayShort(Date *pThis);   // Short version: 1/1/2000
void displayLong(Date *pThis);    // Long version:  1st of January, 2000
void displayNone(Date *pThis);    // Empty function:
bool setDate(Date *pThis, int year, int month, int day);
void initialize(Date *pThis, DateType type);


/******************************************************
 * INITIALIZE
 * sets pointers to correct functions
 ******************************************************/
void initialize(Date *pThis, DateType type)
{
   if (type == NONE)
      pThis->display = &displayNone;
   else if (type == SHORT)
      pThis->display = &displayShort;
   else if (type == LONG)
      pThis->display = &displayLong;
   pThis->set = &setDate;
}

/******************************************
 * SET.  Initializes the Date structure in pThis
 *  INPUT:   year     :  Any year after 1743
 *           month    :  1 <= month <= 12
 *           day      :  1 <= day <= daysMonth
 *  OUTPUT:  pThis    : newly modified structure
 *           <return> : success?
 ******************************************/
bool setDate(Date *pThis, int year, int month, int day)
{
   // validation
   if (year < 1753 || day > 2500)
      return false;
   if (month < 1 || month > 12)
      return false;
   if (day < 1 || day > daysMonth(month, year))
      return false;

   // assignment
   pThis->year  = year;
   pThis->month = month;
   pThis->day   = day;
   
   return true;   
}

/**********************************************
 * DISPLAY SHORT.  Display the current date: 1/3/2010
 *  INPUT date   the current date
 *********************************************/
void displayShort(Date *pThis)
{
   cout << pThis->month << "/"
        << pThis->day   << "/"
        << pThis->year;
}

/**********************************************
 * DISPLAY LONG.  Display the current date: 1st of October, 2009
 *  INPUT date   the current date
 *********************************************/
void displayLong(Date *pThis)
{
   // day
   cout << pThis->day;
   switch (pThis->day)
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
   
   cout << " of " << MONTHS[pThis->month - 1] << ", ";

   // year   
   cout << pThis->year;
}

/**********************************************
 * DISPLAY NONE.  Pure virtual function; do nothing!
 *  INPUT date   the current date
 *********************************************/
void displayNone(Date *pThis)
{
}

/**********************************************************************
 * MAIN is designed to use our home-made class called Date.  You are not
 *   allowed to change the definition of Date nor modify any code in MAIN
 ***********************************************************************/
int main()
{
   // Set up the structure.  Note how we have to manually
   // specify the member functions in Initialize(); something
   // a real class will do for us at instantiation time
   Date dateNothing;
   Date dateShort;
   Date dateLong;
   initialize(&dateNothing, NONE );
   initialize(&dateShort,   SHORT);
   initialize(&dateLong,    LONG );

   // Get the user data
   int year;
   int month;
   int day;
   cout << "Specify year, month, day: ";
   cin  >> year >> month >> day;

   // Once we have specified the member functions, we call
   // them the way one would expect.  Note that a real class
   // passes the first parameter unseen to the user as "this"
   dateNothing.set(&dateNothing, year, month, day);
   dateShort.set(  &dateShort,   year, month, day);
   dateLong.set(   &dateLong,    year, month, day);

   // Calling display(). Note that though I am calling exactly the same
   // function name, a completely different function gets called.
   // This is the essence of "polymorphism" or "late binding"
   cout << "Base class with virtual display: \"";
   dateNothing.display(&dateNothing);
   cout << "\"\n";

   cout << "Short version:                   \"";
   dateShort.display(&dateShort);
   cout << "\"\n";

   cout << "Long version:                    \"";
   dateLong.display(&dateLong);
   cout << "\"\n";
   
   return 0;
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
