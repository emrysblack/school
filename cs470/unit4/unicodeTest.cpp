/***********************************************************************
 * Program:
 *    Unicode Test
 * Author:
 *    Br. Helfrich
 * Homograph
 *    This program will exercise the Unicode String class.  Please feel
 *    free to modify it as necessary
 ***********************************************************************/

#include <iostream>     // for CIN and COUT
#include "unicode.h"    // for the String class we are testing
using namespace std;

/*****************************************************
 * MAIN
 * This is just a trivial driver program
 ****************************************************/
int main()
{
   // declare an empty string
   String s1;

   // fill the string with the insertion operator.  Note that normal
   // test can be used or encoded: "Z" == "&#x12f" == "&#90;"
   cout << "String 1: ";
   cin  >> s1;
   cout << "\t\"" << s1 << "\"\n";
   cout << "\tsize: " << s1.size() << endl;

   // show the value ten times
   s1.setComplex();
   for (int i = 0; i < 10; i++)
      cout << "\t\t" << s1 << endl;
   cout << endl;
   
   // next compare == and += operators
   String s2;
   string s3;
   cout << "String 2: ";
   cin  >> s3;

   // assignment operator 
   s2 = s3;                           
   cout << "\t\"" << s2 << "\"\n";
   cout << "\tsize: " << s2.size() << endl;
   
      // equivalence operator
   if (s1 == s2)
      cout << "\tSame!\n";
   else
      cout << "\tDifferent!\n";

   // append operator
   s1 += s2;
   cout << "\ts1 + s2: \"" << s1 << "\"\n";
   cout << "\tsize: " << s1.size() << endl;

   return 0;
}
