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
   String s4("default");
   char   s3[256];
   cout << String("Enter three strings: ");
   s1.getline(cin);
   cin  >> s2 >> s3;
   cout << "s1 = \"" << s1 << "\"\n";
   cout << "s2 = \"" << s2 << "\"\n";
   cout << "s3 = \"" << s3 << "\"\n";
   cout << "s4 = \"" << s4.c_str() << "\"\n";
   // display, replace, display
   for (int i = 0; i < s1.size(); i++)
   {
      cout << s1[i];
   }
   int pos;
   char letter;
   cout << endl << "Which position should be replaced? ";
   cin >> pos;
   cout << "What is the new letter? ";
   cin >> letter;
   s1[pos] = letter;
   cout << "s1 = \"" << s1 << "\"\n";
   cout << s1.size() << endl;
   // assign
   cout << "\nAssign\n";
   cout << (s1 = s2)     << " = " << s2 << endl;
   cout << (s1 = "text") << " = \"text\"\n";
   cout << (s1 = 'x')    << " = 'x'\n";
   s1.clear();
   cout << "after clear() = \"" << s1 << "\"\n";
   s4 = "9876543210 9876543210 9876543210 9876543210 9876543210 9876543210 9876543210 9876543210 9876543210 9876543210 9876543210 9876543210 9876543210 9876543210 9876543210 9876543210 9876543210 9876543210 9876543210 9876543210 9876543210 9876543210 9876543210 9876543210 9876543210 9876543210 9876543210 9876543210 9876543210 9876543210";
   
   return 0;
}
