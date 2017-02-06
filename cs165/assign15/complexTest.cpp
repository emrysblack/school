/***********************************************************************
* Program:
*    Assignment 15, Separate Compilation
*    Brother Boyer, CS165
* Author:
*    Brady Field
* Summary: 
*    This program is designed to perform very simple manipulations of
*    Complex numbers.  A complex number, as you may recall, is a two
*    part number with a real and imagionary part.
*
*    Your assigment here is to break this file into four parts:
*       complex.h        Header file with data types and prototypes
*       complex.cpp      All the functions manipulating complex numbers
*       complexTest.cpp  Driver program exercising the complex type.
*       makefile         File describing how to build this project
*
*    Estimated:  1.0 hrs   
*    Actual:     1.0 hrs
*      makefile part
************************************************************************/

#include <iostream>
using namespace std;
#include "complex.h"

/**********************************************************************
 * Just a simple driver program to help the user test this new data type
 ***********************************************************************/
int main()
{
   // This is the number we will work with
   Complex number;
   prompt(number);
   cout << "\tCurrent value: ";
   display(number);
   cout << endl;

   // keep going until zero is entered
   while (!isZero(number))
   {
      // grab a new number
      Complex num2;
      prompt(num2);

      // add to current one
      addTo(number, num2);

      // display
      cout << "\tNew value: ";
      display(number);
      cout << endl;
   }

   return 0;
}
