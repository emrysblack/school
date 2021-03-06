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
   void initialize();
   void uninitialize();
   bool setDate(int year, int month, int day);
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
