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

class Date
{
  public:
   Date();
   Date(int year, int month, int day);
   Date(int year);
   Date(const Date& date);
   ~Date();
   bool setDate(int year, int month, int day);
   bool setYear(int year);
   bool setMonth(int month);
   bool setDay(int day);
   int getDay();
   int getMonth();
   int getYear();
   void displayLong();   
  private:
   void assertDate();
   int daysMonth(int, int);
   bool isLeapYear(int year);
   int *data;  // dynamically allocated
};

#ifndef NDEBUG

#else

#endif

#endif // DATE_H
