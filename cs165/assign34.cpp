/***********************************************************************
* Program:
*    Assignment 34, Polymorphism with virtual functions
*    Brother Boyer, CS165
* Author:
*    Brady Field
* Summary: 
*    This program is designed to demonstrate simple polymorphism
*    through the use of virtual functions.  Here the display() function
*    will be differently defined in each of the inherited time classes.
*
*    Estimated:  1.0 hrs   
*    Actual:     1.0 hrs
*      set fill command
************************************************************************/
#include <iostream>
#include <cassert>
#include <iomanip>
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
   void display();
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
   void display();
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
   void display();
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
   // HOURS: A couple quick tests
   cout << "#### HOURS ####\n";
   Hours hours; 
   hours.setHours(2);
   hours.display();
   cout << endl;
   hours.addHours(14);
   hours.display();
   cout << endl;

   // MINUTES: Also, a couple quick tests
   cout << "#### MINUTES ####\n";
   Minutes minutes(30);
   minutes.display();
   cout << endl;
   minutes.addMinutes(-(3 * 60 + 20));
   minutes.display();
   cout << endl;
   
   // SECONDS: Finally, the complete time
   cout << "#### TIME ####\n";
   Time time;
   time.display();
   cout << endl;
   time.addSeconds(-1);
   time.display();
   cout << endl;

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

/***********************************
 *
 ***********************************/
void Hours::display()
{
   cout << setfill('0');
   cout << setw(2) << h;
}

/***********************************
 *
 ***********************************/
void Minutes::display()
{
   cout << setw(2) << h
        << ":"
        << setw(2) << m;
}

/***********************************
 *
 ***********************************/
void Time::display()
{
   cout << setw(2) << h
        << ":"
        << setw(2) << m
        << ":"
        << setw(2) << s;
}

