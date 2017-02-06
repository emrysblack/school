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

#include <iostream>
using namespace std;

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
   Date operator +(int rhs);
   Date operator -(const int rhs);
   Date operator +=(const int rhs);
   Date operator -=(const int rhs);
   Date operator /(const int rhs);
   Date operator *(const int rhs);
   Date operator %(const int rhs);
   Date operator ++();
   Date operator ++(int);
   Date operator --();
   Date operator --(int);
   Date& operator =(const Date& rhs);   
   bool operator ==(const Date& rhs);
   bool operator !=(const Date& rhs);
   bool operator >(const Date& rhs);
   bool operator >=(const Date& rhs);
   bool operator <(const Date& rhs);
   bool operator <=(const Date& rhs);
   friend ostream& operator <<(ostream& out, Date& rhs);
   friend istream& operator >>(istream& cin, Date& rhs);
   friend Date operator +(int lhs, const Date& rhs);
  private:
   void assertDate();
   void adjustDay(int);
   void adjustMonth(int);
   void adjustYear(int);
   int daysMonth(int, int);
   bool isLeapYear(int year);
   int *data;  // dynamically allocated
};

#ifndef NDEBUG

#else

#endif

#endif // DATE_H
