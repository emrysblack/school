/***********************************************************************
* Program:
*    Assignment 33, Inheritance Qualifiers
*    Brother Boyer, CS165
* Author:
*    Brady Field
* Summary: 
*    This program is designed to demonstrate inheritance with protected
*    variables through a Time class, inheriting off a Minutes parent,
*    inheriting off a Hours parent.
*
*    Estimated:  1.0 hrs   
*    Actual:     0.1 hrs
*      Easy, but why change getters or setters?
************************************************************************/

#include <iostream>
#include <cassert>
using namespace std;

/***********************************************************
 * HOURS: Number of hours in a day.
 ***********************************************************/
class Hours
{
public:
   Hours()      : h(12)      {};
   Hours(int h) : h(0)       { setHours(h); };
   Hours(const Hours &hours) { setHours(hours.getHours()); };
   int  getHours() const     { return h; };
   void setHours(int h)      { if (validateHours(h)) this->h = h; };
   void addHours(int h);
protected:
   bool validateHours(int h) const { return (0 <= h && h <= 23); };
   int h;
};

/**********************************************************
 * MINUTES: Number of hours and minutes in a day.
 *          Looks like HOURS and inherits off Hours
 **********************************************************/
class Minutes : public Hours
{
public:
   Minutes()                : Hours(), m(0) {};
   Minutes(int m)           : Hours(), m(0) { setMinutes(m); };
   Minutes(const Minutes &minutes) { setHours(minutes.getHours());
                                     setMinutes(minutes.getMinutes()); };
   int getMinutes() const          { return m; };
   void setMinutes(int m)          { if (validateMinutes(m)) this->m = m; };
   void addMinutes(int m);
protected:
   bool validateMinutes(int m) const { return (0 <= m && m <= 59); };
   int m;
};   

/************************************************************
 * Time: Hours, minutes, and seconds
 *       Looks like HOURS and MINUTES but inherits off Minutes
 ***********************************************************/
class Time : public Minutes
{
public:
   Time()          : s(0) {};
   Time(int s)     : s(0) { setSeconds(s); };
   Time(const Time &time) { setHours(time.getHours());
      setMinutes(time.getMinutes()); setSeconds(time.getSeconds()); };
   int getSeconds() const {return s; };
   void setSeconds(int s) { if (validateSeconds(s)) this->s = s; };
   void addSeconds(int s);
protected:
   bool validateSeconds(int s) const { return (0 <= s && s <= 59); };
   int s;
};

/**********************************************************************
 * MAIN:  A driver program to exercise our Hours, Minutes, and Time classes
 *        You are not allowed to modify MAIN in any way
 ***********************************************************************/
int main()
{
   //
   // HOURS: A couple quick tests 
   //

   Hours hours1;                   // (1) 12 
   assert(hours1.getHours() == 12); 
   hours1.addHours(4);             // (1) 16
   Hours hours2(16);               // (2) 16
   assert(hours2.getHours() == hours1.getHours());

   //
   // validate Minutes next
   //

   Minutes minutes1;                   // (1) 12:00
   assert(minutes1.getMinutes() == 0 && minutes1.getHours() == 12);
   Minutes minutes2(80);               // (2) 12:00 because invalid so ignored
   assert(minutes2.getMinutes() == 0); // (2) 12:00 
   minutes1.addMinutes(60 * 2 + 30);   // (1) 14:30
   minutes2.addHours(2);               // (2) 14:00
   minutes2.addMinutes(30);            // (2) 14:30   
   assert(minutes1.getHours()   == minutes2.getHours());
   assert(minutes1.getMinutes() == minutes2.getMinutes());   
   minutes1.addHours(-3);              // (1) 11:30
   minutes1.addMinutes(-40);           // (1) 10:50
   minutes2.addMinutes(-(60 * 3 + 40));// (2) 10:50
   assert(minutes1.getHours()   == minutes2.getHours());
   assert(minutes1.getMinutes() == minutes2.getMinutes());

   //
   // finally, validate them all together
   //

   Time time1;                         // (1) 12:00:00
   assert(time1.getHours() == 12);
   assert(time1.getMinutes() == 0);
   assert(time1.getSeconds() == 0);
   time1.addSeconds(60 * 6 + 40);      // (1) 12:06:40
   time1.addMinutes(60 * 1 + 10);      // (1) 13:16:00
   time1.addHours(3);                  // (1) 16:16:40
   Time time2(time1);                  // (2) 16:16:40  Copy constructor
   assert(time1.getHours()   == time2.getHours());
   assert(time1.getMinutes() == time2.getMinutes());
   assert(time1.getSeconds() == time2.getSeconds());
   cout << time1.getHours()   << ":"
        << time1.getMinutes() << ":"
        << time1.getSeconds() << endl; // 16:16:40
   time1.addSeconds(-(6 * 60 + 40));   // (1) 16:10:00
   time1.addMinutes(-(1 * 60 + 10));   // (1) 15:00:00
   time1.addHours(-3);                 // (1) 12:00:00
   assert(time1.getHours() == Hours().getHours());
   time1.addSeconds(-1);               // (1) 11:59:59
   cout << time1.getHours()   << ":"
        << time1.getMinutes() << ":"
        << time1.getSeconds() << endl; // 11:59:59
   
   return 0;
}


/**********************************
 * HOURS : ADD HOURS: add a fixed number of hours to our value
 *   INPUT:  hours: number to add
 **********************************/
void Hours::addHours(int h)
{
   int hNew = h + this->h;
   if (validateHours(hNew))
      this->h = hNew;
}

/**********************************
 * MINTUES : ADD MINUTES: add a fixed number of minutes to our value
 *   INPUT:  minutes: number to add
 **********************************/
void Minutes::addMinutes(int m)
{
   int mNew = m + this->m;
   if (validateMinutes(mNew)) // if not new hour
      this->m = mNew;
   else
   {
      if (mNew % 60 < 0) // if subtracting time
      {
         int negHours = mNew / 60;
         addHours(negHours - 1);
         this->m = 60 + mNew % 60;
      }
      else // if new hour(s)
      {
         addHours(mNew / 60);
         this->m = mNew % 60;
      }
   }
}

/**********************************
 * TIME : ADD SECONDS: add a fixed number of seconds to our value
 *   INPUT:  seconds: number to add
 **********************************/
void Time::addSeconds(int s)
{
   int sNew = s + this->s;
   if (validateSeconds(sNew))
      this->s = sNew;
  else
   {
      if (sNew % 60 < 0) // if subtracting time
      {
         int negMins = sNew / 60;
         addMinutes(negMins - 1);
         this->s = 60 + sNew % 60;
      }
      else // if new minute(s)
      {
         addMinutes(sNew / 60);
         this->s = sNew % 60;
      }
   }
}

