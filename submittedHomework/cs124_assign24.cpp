/***********************************************************************
* Program:
*    Assignment 24, Allocate a string
*    Brother Helfrich, CS124
* Author:
*    Brady Field
* Summary: 
*    Prompts user for number of characters in a string then allocates
*    a proper amount of space to store said string.
*
*    Estimated:  1.0 hrs   
*    Actual:     0.5 hrs
*      Wasn't too hard, but I still don't understand the mechanics
************************************************************************/

#include <iostream>
using namespace std;

/**********************************************************************
* Prompts for number of characters, allocates sufficient space,
* takes input and displays what it could store in given space
***********************************************************************/
int main()
{
   int numChar;
   char *a;

   // get size
   cout << "Number of characters: ";
   cin >> numChar;

   // check for allocation failure
   if (numChar < 1)
   {
      cout << "Allocation failure!\n";
      exit(1);
   }

   // increase by one for null character
   numChar++;

   // create new memory space
   a = new char[numChar];
   
   cout << "Enter Text: ";
   cin.ignore();
   cin.getline (a, numChar);
   cout << "Text: " << a << endl;

   // release space
   delete [] a;
   a = NULL;
     
   return 0;
}
