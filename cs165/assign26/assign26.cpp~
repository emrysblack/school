/***********************************************************************
* Program:
*    Assignment 24, Operator overloading with friends
*    Brother Helfrich, CS165
* Author:
*    your name
* Summary: 
*    This assignment is to demonstrate all types of
*    member function operator overloading
*
*    Estimated:  0.0 hrs   
*    Actual:     0.0 hrs
*      Please describe briefly what was the most difficult part
************************************************************************/

#include <iostream>
#include <cassert>
#include "date.h"
using namespace std;

/**********************************************************************
 * A simple driver program to exercise the insertion and extraction operators
 ***********************************************************************/
int main()
{
   Date date;

   // keep looping until the current date is 1/1/2000
   do
   {
      cout << date << endl;
      cout << "> ";
      cin  >> date;

      // check both member overload and friend overload of addition
      assert(date + 4 == 4 + date);
   }
   while (date != Date());  // until 1/1/2000
   
   return 0;
}
