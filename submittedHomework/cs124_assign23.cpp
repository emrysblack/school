/***********************************************************************
* Program:
*    Assignment 23, Count spaces with pointer
*    Brother Helfrich, CS124
* Author:
*    Brady Field
* Summary: 
*    Takes input text from a user and outputs the number of spaces
*    in the string.
*    
*    Estimated:  1.0 hrs   
*    Actual:     0.5 hrs
*     Getting the array pointer in the loop working, it is cool though 
************************************************************************/

#include <iostream>
using namespace std;

int countSpaces(char *text);

/**********************************************************************
* Prompts for a text string. Stores it as a string using get line and 
* calls the function to count spaces. Then displays the results
***********************************************************************/
int main()
{
   char text[256];
   int spaces;
   
   // prompt for line of input
   cout << "Enter text: ";
   cin.getline(text,256);

   // count the spaces
   spaces = countSpaces(text);

   // display the results
   cout << "Number of spaces: " << spaces << endl;
   
   return 0;
}

/**********************************************************************
* takes input text, reads it one character at a time and returns the
* number of spaces in the text string
***********************************************************************/
int countSpaces(char *text)
{
   int spaces = 0;
   char *pointer;
   for (pointer = text; *pointer; pointer++)
   {
      if (*pointer != ' ')
         ;
      else
         spaces++;
   }
   return spaces;
}
