/***********************************************************************
* Program:
*    Assignment ##, ???? 
*    Brother Helfrich, CS165
* Author:
*    your name
* Summary: 
*    This header file describes all the interfaces associated with
*    manipulating dates.
************************************************************************/

#ifndef DATE_H
#define DATE_H

struct Date
{
   int *data;  // dynamically allocated
};

// Initialize the date
void initialize(Date &date);

// Uninitialize the date
void uninitialize(Date &date);


// Set the current year 
bool setYear(Date &date, int year);

// Set the current month
bool setMonth(Date &date, int month);

// Set the current day
bool setDay(Date &date, int day);

// set the current date
bool setDate(Date &date, int year, int month, int day);

// adjust the date by a fixed number of days
void adjustDay(Date &date, int adjustment);

// adjust the date by a fixed number of months
void adjustMonth(Date &date, int adjustment);

// adjust the date by a fixed number of years
void adjustYear(Date &date, int adjustment);

// How many days are in the current month?
int daysMonth(int month, int year);

// Is the current year a leap year?
bool isLeapYear(int year);

// Display the current date
void display(const Date &date, bool isShort);

// Short version of the display
void displayShort(const Date &date);

// Long version of the same
void displayLong(const Date &date);

#ifndef NDEBUG
void assertDateProc(const Date &date, const char *file, int line);
#define assertDate(date) assertDateProc(date, __FILE__ , __LINE__)
#else
#define assertDate(date)
#endif

#endif // DATE_H
