/***********************************************************************
 * Program:
 *    Unit 2, Safe String
 *    Brother Helfrich, CS 470
 * Author:
 *    Br. Helfrich
 * Summary: 
 *    Simple driver program to exercise our String class. You may use this
 *    driver program or create your own.
 ************************************************************************/

#include <iostream>
#include "string.h"
using namespace std;

/**********************************************************************
 * MAIN
 * Just a simple driver program 
 ***********************************************************************/
int main()
{
   // input 
   String s1;
   String s2;
   char   s3[256];
   cout << String("Enter three strings: ");
   s1.getline(cin);
   cin  >> s2 >> s3;
   cout << "s1 = \"" << s1 << "\"\n";
   cout << "s2 = \"" << s2 << "\"\n";
   cout << "s3 = \"" << s3 << "\"\n";

   // comparison
   cout << "\nCompare\n";
   if (s1 >  s2)    cout << s1 << " >  " << s2 << endl;
   if (s1 >= s2)    cout << s1 << " >= " << s2 << endl;
   if (s1 <  s2)    cout << s1 << " <  " << s2 << endl;
   if (s1 <= s2)    cout << s1 << " <= " << s2 << endl;
   if (s1 == s2)    cout << s1 << " == " << s2 << endl;
   if (s1 != s2)    cout << s1 << " != " << s2 << endl;
   
   if (s1 >  s3)    cout << s1 << " >  " << s3 << endl;
   if (s1 >= s3)    cout << s1 << " >= " << s3 << endl;
   if (s1 <  s3)    cout << s1 << " <  " << s3 << endl;
   if (s1 <= s3)    cout << s1 << " <= " << s3 << endl;
   if (s1 == s3)    cout << s1 << " == " << s3 << endl;
   if (s1 != s3)    cout << s1 << " != " << s3 << endl;

   // append
   cout << "\nAppend\n";
   cout << s2 << " +  " << s3 << " --> " << (s2 +  s3) << endl;
   cout << s1 << " +  " << s2 << " --> " << (s1 +  s2) << endl;
   cout << s1 << " += " << s2 << " --> ";
   cout << (s1 += s2) << endl;
   cout << s2 << " += " << s3 << " --> ";
   cout << (s2 += s3) << endl;

   // assign
   cout << "\nAssign\n";
   cout << (s1 = s2)     << " = " << s2 << endl;
   cout << (s1 = "text") << " = \"text\"\n";
   cout << (s1 = 'x')    << " = 'x'\n";
   s1.clear();
   cout << "after clear() = \"" << s1 << "\"\n";
   
   return 0;
}
