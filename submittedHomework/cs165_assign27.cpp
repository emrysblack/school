/***********************************************************************
* Program:
*    Assignment 27, Recursion 
*    Brother Boyer, CS165
* Author:
*    Brady Field
* Summary:
*    Uses recursion to add two numbers together until stopped by the 
*    user.
*
*    Estimated:  1.0 hrs   
*    Actual:     0.5 hrs
*      I didn't understand how the recursion syntax works for the assignment
************************************************************************/

#include <iostream>
using namespace std;

/**********************************************************************
 * returns sum of two numbers
 **********************************************************************/
int add(int& n, int& m)
{
   if (m > 0)
   {
      n++;
      m--;
      add(n, m);
   }
   return n;
}

/**********************************************************************
 * displays sum of two numbers
 ***********************************************************************/
int main()
{
   int m;
   int n;
   cout << "This program performs addition: sum = m + n\n";
   cout << "m: ";
   cin >> m;
   cout << "n: ";
   cin >> n;
   cout << "sum: " << add(n, m) << endl;
   return 0;
}
