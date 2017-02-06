/***********************************************************************
* Program:
*    Assignment 21, Count spaces
*    Brother Helfrich, CS124
* Author:
*    Brady Field
* Summary: 
*    Takes input text from a user and outputs the number of spaces
*    in the string.
*    
*    Estimated:  1.0 hrs   
*    Actual:     0.5 hrs
*      It was pretty simple. No prblems yet.
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
   int i;
   int spaces = 0;
   for (i = 0; text[i] != '\0'; i++)
   {
      if (text[i] != ' ')
         ;
      else
         spaces++;
   }
   return spaces;
}
