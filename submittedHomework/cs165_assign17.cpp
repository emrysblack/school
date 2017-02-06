/***********************************************************************
* Program:
*    Assignment 17, Robust input
*    Brother Boyer, CS165
* Author:
*    Brady Field
* Summary: 
*    This is a driver program for a function design to accept an
*    index from the user and work regardless of the type of input
*    the user may type.
*
*    Estimated:  1.0 hrs   
*    Actual:     1.5 hrs
*      clearing input of more than one char
************************************************************************/

#include <iostream>
#include <string>
using namespace std;

int getIndex(int min, int max);

/***********************************************************************
 * MAIN: Simple driver program for getIndex();
 ***********************************************************************/
int main()
{
   int index = getIndex(1 /*min*/, 10 /*max*/);

   cout << "The user's index is: " << index << endl;
   
   return 0;
}

/**********************************************************************
 *
 **********************************************************************/
int getIndex (const int min, const int max)
{
   int index;
   bool done = false;
   cout << "Please enter the index.  The acceptable range is 1 <= index <= 10.\n";
   
   while(!done)
   {
      cout << "> ";
      cin >> index;
      if (cin.fail())
      {
         string tmp;
         cout << "ERROR: non-digit entered\n";
         cin.clear();
         cin >> tmp;
      }
      else if (index < min || index > max)
      {
         cout << "ERROR: value is outside the accepted range\n";
         cin.clear();
         cin.ignore();
      }
      else
         return index;      
   }
   return index;
}
