// ercanbrack 165 assignment address book
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include "time.h"
using namespace std;

// constructors
Time::Time(int theHour, int theMin, int theSec)
{
   hour = theHour;
   minute = theMin;
   second = theSec;
}

Time::Time(int theHour, int theMin)
{
   hour = theHour;
   minute = theMin;
   second = 0;
}

Time::Time(void)
{
   hour = 0;
   minute = 0;
   second = 0;
}
void Time::setMinute(int theMinute)
{
   minute = theMinute;
}
void Time::setHour(int theHour)
{
   hour = theHour;
}
void Time::setSecond(int theSecond)
{
   second = theSecond;
}
void Time::addSeconds(int seconds2Add)
{
   second += seconds2Add;
   if (second > 59)
   {
      this->addMinutes(second / 60);
      second %= 60;
   }
}
void Time::addMinutes(int minutes2Add)
{
      minute += minutes2Add;
   if (minute > 59)
   {
      this->addHours(minute / 60);
      minute %= 60;
   }
}
      // add hours and returns # of days of overflow
int  Time::addHours(int hours2Add)
{
   int days = 0;
   
   hour += hours2Add;
   days = hour / 24;
   hour = hour % 24;

   return days;
}
      // display as military time - default no seconds (hh:mm)
void Time::displayMilitaryTime(bool displaySeconds)
{
   cout << *this;
   
   if (displaySeconds)
   {
      cout.fill('0');
      cout << ':' << setw(2) << second;
      cout.fill(' ');
   }
}
      // display the prompt and read data into the time object
void Time::promptForTime(string prompt, bool readSeconds)
{
   char colon;
   cout << prompt;
   cin >> *this;
   if (readSeconds)
      cin >> colon >> second;
}
      // add two time objects & return the resulting time object
Time Time::operator + (const Time time1)
{
   Time temp(hour, minute, second);
   temp.addSeconds(time1.second + (time1.minute * 60) + (time1.hour * 60 * 60));
   return temp;
}

      // logical operators
bool Time::operator < (const Time &time1)
{
      bool smaller = true;
   if (hour > time1.hour)
      smaller = false;
   else if (hour == time1.hour)
   {
      if (minute > time1.minute)
         smaller = false;
      else if (minute == time1.minute)
      {
         if (second >= time1.second)
            smaller = false;
      }
   }
   return smaller;
}
bool Time::operator > (const Time &time1)
{
   bool bigger = true;
   if (hour < time1.hour)
      bigger = false;
   else if (hour == time1.hour)
   {
      if (minute < time1.minute)
         bigger = false;
      else if (minute == time1.minute)
      {
         if (second <= time1.second)
            bigger = false;
      }
   }
   return bigger;
}
bool Time::operator == (const Time &time1)
{
   return hour == time1.hour && minute == time1.minute && second == time1.second;
}
bool Time::operator <= (const Time &time1)
{
   return *this < time1 || *this == time1;
}
bool Time::operator >= (const Time &time1)
{
   return *this > time1 || *this == time1;
}

      // displays the time object in the format "hh:mm"
ostream& operator << (ostream &out, const Time &time1)
{
   out.fill('0');
   out << setw(2) << time1.hour << ':' << setw(2) << time1.minute;
   out.fill(' ');
   return out;
}
      // reads into the time object.  Expects format "hh:mm"
istream& operator >> (istream &in, Time &time1)
{
   char colon;
   in >> time1.hour >> colon >> time1.minute;
   return in;
}
