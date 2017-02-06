/***********************************************************************
* Program:
*    Assignment ##, ???? 
*    Brother Helfrich, CS165
* Author:
*    your name
* Summary: 
*    This program is designed to test the date class.  It will provide a
*    Simple user interface
*
*    Estimated:  0.0 hrs   
*    Actual:     0.0 hrs
*      Please describe briefly what was the most difficult part
************************************************************************/

#include <iostream>
#include <cassert>
#include "date.h"
using namespace std;

bool interact(Date &date, bool &isShort);
int  getNumber(const char *PROMPT);
void displayInstructions();

/**********************************************************************
 * Simple driver program to initialize the date and interact with it
 ***********************************************************************/
int main()
{
   Date date;
   initialize(date);

   // set the year
   int year;
   cout << "What is the current year? ";
   cin  >> year;
   setYear(date, year);

   // set the month
   int month;
   cout << "What is the current month? ";
   cin  >> month;
   setMonth(date, month);

   // set the day
   int day;
   cout << "What is the current day? ";
   cin  >> day;
   setDay(date, day);
    
   
   // show current date
   bool isShort = false;
   display(date, isShort);

   // interact
   displayInstructions();
   while (interact(date, isShort))
      ;

   uninitialize(date);
   
   return 0;
}

/*****************************************************
 * INTERACT.  Simple user interface allowing user to work with the date
 *    INPUT: date:    The date to be adjusted
 *           isShort  Long or short version of the date?
 *    OUTPUT date:    This can be adjusted
 *           isShort  May be adjusted
 *           return   Do we continue?
 *****************************************************/
bool interact(Date &date, bool &isShort)
{
   string input;
   cout << "> ";
   cin  >> input;

   bool invalid = false;
   if (input.size() != 1)
      invalid = true;

   if (!invalid)
      switch (input[0])
      {
         case 'y':
            try
            {
               int year = getNumber("Adjust the date by how many years? ");
               adjustYear(date, year);
            }
            catch (string s)
            {
               cout << "Invalid value \"" << s << "\" "
                    << "Please specify a positive or negative digit.\n";
            }
            break;
         case 'm':
            try
            {
               int month = getNumber("Adjust the date by how many months? ");
               adjustMonth(date, month);
            }
            catch (string s)
            {
               cout << "Invalid value \"" << s << "\" "
                    << "Please specify a positive or negative digit.\n";
            }
            break;
         case 'd':
            try
            {
               int day = getNumber("Adjust the date by how many days? ");
               adjustDay(date, day);
            }
            catch (string s)
            {
               cout << "Invalid value \"" << s << "\" "
                    << "Please specify a positive or negative digit.\n";
            }
            break;
         case 'a':
            try
            {
               int year  = getNumber("Year:  ");
               int month = getNumber("Month: ");
               int day   = getNumber("Day:   ");
               if (!setDate(date, year, month, day))
                  throw 0;
            }
            catch (string s)
            {
               cout << "Invalid value \"" << s << "\" "
                    << "Please specify a positive or negative digit.\n";
            }
            catch (int)
            {
               cout << "Invalid value. "
                    << "Please specify a positive or negative digit.\n";
            }
            break;
             
         case 'l':
            isShort = false;
            break;
         case 's':
            isShort = true;
            break;
         case '?':
            displayInstructions();
            break;
         case 'q':
            return false;
         default:
            invalid = true;
      }

   if (invalid)
      cout << "Invalid option \""
           << input << "\".  Please try again.\n";
   else
      display(date, isShort);

   return true;
}

/*****************************************************
 * DISPLAY INSTRUCTIONS. Show the user his options
 *****************************************************/
void displayInstructions()
{
   cout << "\ty  Change the year by a given amount\n";
   cout << "\tm  Change the month by a given amount\n";
   cout << "\td  Change the day by a given amount\n";
   cout << "\ta  Specify a new year, month, and day\n";
   cout << "\tl  Use the long format:  \"1st of January, 2000\"\n";
   cout << "\ts  Use the short format: \"1/1/2000\"\n";
   cout << "\t?  Show these options again\n";
   cout << "\tq  Quit\n";
}

/**************************************************************
 * GET NUMBER: Prompt the user for an index between a certain range
 *   INPUT  prompt: the prompt to show the user
 *   OUTPUT number: returned value guaranteed to be in the range
 *          exception : text of invalid message
 *************************************************************/
int getNumber(const char *PROMPT)
{
   // instructions
   cout << PROMPT;

   // we should be all clear at this point
   assert(cin.good());
   int number;
   cin >> number;

   // check for a value that is not an integer
   if (cin.fail())
   {
      string s;
      cin.clear();           // clear the error state
      getline(cin, s);       // grab the text
      throw s;               // blow this burger joint
   }

   // ensure we are good before we even think of leaving
   assert(cin.good());
   return number;
}

