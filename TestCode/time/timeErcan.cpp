/**************************************************************************
* Program:
*    Assignment 08, Time class
*    Brother Ercanbrack, CS165
* Author:
*    your name   
* Summary:
*    Descriptive text
****************************************************************************/
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

/*****************************************************************************
 * Class Name: Time
 * Summary: This class contains methods for the the creation,
 *          manipulation, input, and output of time objects
 *****************************************************************************/
class Time
{
   public:

      Time(int theHour, int theMin, int theSec);
      Time(int theHour, int theMin);
      Time(void);
      void setMinute(int theMinute);
      void setHour(int theHour);
      void setSecond(int theSecond);
      void addSeconds(int seconds2Add);
      void addMinutes(int minutes2Add);
      // add hours and returns # of days of overflow
      int  addHours(int hours2Add);
      // display as military time - default no seconds (hh:mm)
      void displayMilitaryTime(bool displaySeconds = false);
      // display the prompt and read data into the time object
      void promptForTime(string prompt, bool readSeconds = false);
      // add two time objects & return the resulting time object
      Time operator + (const Time time1);                           

      // logical operators
      bool operator < (const Time &time1);
      bool operator > (const Time &time1);
      bool operator == (const Time &time1);
      bool operator <= (const Time &time1);
      bool operator >= (const Time &time1);

      // displays the time object in the format "hh:mm"
      friend ostream& operator << (ostream &out, const Time &time1);
      // reads into the time object.  Expects format "hh:mm"
      friend istream& operator >> (istream &in, Time &time1);

   private:
      int hour;
      int minute;
      int second;
};

/************************************************************************
 *  int getInt(string prompt, string errMsg)
 *
 *  Desc: Error safe - read integer routine
 *        On error, this function will re-prompt for the integer
 *        until there is no input error.
 *
 *  Inputs:  prompt - string used to prompt for the integer
 *           errMsg - error message you wish displayed if you get an error.
 *  Outputs: none
 *  return:  integer - read from the console
 **************************************************************************/
int getInt(string prompt, string errMsg = "\nValue must be an integer!\n")
{
   int num;
   cout << prompt;
   cin >> num;
   while (cin.fail())
   {
      cin.clear();
      cin.ignore();
      cout << errMsg;
      cin >> num;
   }
   cin.ignore(80, '\n');
   return num;
}

/***********************************************************************
* Function comments for main go here!
*
* Note: Don't modify main() - Your class functions must work with main()
***********************************************************************/
int main (void)
{
   const bool DISPLAY_SECONDS = true;
   const bool READ_SECONDS = true;

   int hourInput;
   int minInput;
   int secInput;

   Time time1;
   cout << "\nTime1 = " << time1;
   Time time2(8,10);
   cout << "\nTime2 = " << time2; 
   time2.promptForTime("\nChange Time2 (hh:mm): ");

   Time time3(12,30,15);
   time3.promptForTime("Enter Time3 (hh:mm:ss): ",READ_SECONDS);

   Time time4;
   cout << "Enter Time4 (hh:mm): ";
   cin >> time4;

   cout << "\nTime1 = ";
   time1.displayMilitaryTime(DISPLAY_SECONDS);
   cout << "\nTime2 = ";
   time2.displayMilitaryTime(DISPLAY_SECONDS);
   cout << "\nTime3 = ";
   time3.displayMilitaryTime(DISPLAY_SECONDS);
   cout << "\nTime4 = ";
   time4.displayMilitaryTime();

   Time time5(8,0);
   cout << "\nTime5 = ";
   cout << time5;
   cout << endl << endl;
   
   cout << "Adding Time1 to Time2" << endl;
   time5 = time1 + time2;
   cout << time1 << " + " << time2 << " = " << time5 << endl;

   cout << "Adding Time3 to Time4" << endl;
   time5 = time3 + time4;
   cout << time3 << " + " << time4 << " = " << time5 << endl;

   cout << "\nTime5 = ";
   time5.displayMilitaryTime(DISPLAY_SECONDS);

   cout << "\nNow let's add to Time5\n";
   
   secInput = getInt("\nNumber of seconds to add: ","Invalid Seconds value!");
   time5.addSeconds(secInput);
   cout << "Adding " << secInput << " seconds to Time5 = ";
   time5.displayMilitaryTime(DISPLAY_SECONDS);

   minInput = getInt("\nNumber of minutes to add: ","Invalid Minutes value!");
   time5.addMinutes(minInput);
   cout << "Adding " << minInput << " minutes to Time5 = ";
   time5.displayMilitaryTime(DISPLAY_SECONDS);

   hourInput = getInt("\nNumber of hours to add: ","Invalid hours value!");
   int day = time5.addHours(hourInput);
   cout << "Adding " << hourInput << " hours to Time5 = ";
   time5.displayMilitaryTime(DISPLAY_SECONDS);
   cout << "\nDays carried over: " << day << endl;
   cout << endl;
  
   if (time1 < time2)
   {
      cout << time1 << " is less than " << time2 << endl;
   }

   if (time1 > time2)
   {
      cout << time1 << " is greater than " << time2 << endl;
   }
   
   if (time2 == time3)
   {
      cout << time2 << " is equal " << time3 << endl;
   }
   
   if (time3 <= time4)
   {
      cout << time3 << " is less or equal to " << time4 << endl;
   }
   
   if (time4 >= time5)
   {
      cout << time4 << " is greater or equal to " << time5 << endl;
   }

   Time time6(7,40,35);
   Time time7(9,20,40);
   if (time6 < time7)
   {
      time6.displayMilitaryTime(DISPLAY_SECONDS);
      cout << " is less than ";
      time7.displayMilitaryTime(DISPLAY_SECONDS);
      cout << endl;
   }
   else
   {
      time6.displayMilitaryTime(DISPLAY_SECONDS);
      cout << " is greater or equal to ";
      time7.displayMilitaryTime(DISPLAY_SECONDS);
      cout << endl;
   }

   time6 = Time(8,30,15);
   time7 = Time(8,20,15);
   if (time6 <= time7)
   {
      time6.displayMilitaryTime(DISPLAY_SECONDS);
      cout << " is less than or equal ";
      time7.displayMilitaryTime(DISPLAY_SECONDS);
      cout << endl;
   }
   else
   {
      time6.displayMilitaryTime(DISPLAY_SECONDS);
      cout << " is greater than ";
      time7.displayMilitaryTime(DISPLAY_SECONDS);
      cout << endl;
   }

   return 0;
}

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
