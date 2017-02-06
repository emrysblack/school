/***********************************************************************
* Program:
*    Lab 0, Practice Lab Submission
*    Brother Jones, CS460
* Author:
*    Brady Field
* Summary: 
*    Counts number of words with a capital letter
*    
************************************************************************/

#include <iostream>
using namespace std;

/**********************************************************************
 * Repeatedly prompts a user for text until the user enters an empty 
 * c-string, tests for a capital letter as they come in, and counts
 ***********************************************************************/
int main()
{
   // use c style strings because the string class is overkill
   // for the simplicity of our application
   
   char text[256];
   int count = 0;

   // prompt for test and count capitals
   do
   {
      cout << "Enter a string: ";
      cin.getline(text, 256);
      if (isupper(text[0]))
         ++count;
   } while (text[0]);

   // display message about number of strings counted
   switch (count)
   {
      case 0:
         cout << "No strings starting with an upper case letter were seen.\n";
         break;
      case 1:
         cout << "One string starting with an upper case letter was seen.\n";
         break;
      default:
         cout << "You entered " << count
              << " strings that started with an upper case letter.\n";
         break;
   }
   return 0;
}

