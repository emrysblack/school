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
#include "time.h"

using namespace std;

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
