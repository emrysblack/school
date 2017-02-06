/***********************************************************************
* Program:
*    Lab 0, Practice Lab Submission
*    Brother Jones, CS460
* Author:
*    Brady Field
* Summary: 
*    Enter a brief description of your program here!  Please note that if
*    you do not take the time to fill out this block, YOU WILL LOSE POINTS.
************************************************************************/

#include <iostream>
using namespace std;

/**********************************************************************
 * Add text here to describe what the function "main" does. Also don't forget
 * to fill this out with meaningful text or YOU WILL LOSE POINTS.
 ***********************************************************************/
int main()
{
   char text[256];
   int count = 0;
   do
   {
      cout << "Enter a string: ";
      cin.getline(text, 256);
      if (text[0] >= 'A' && text[0] <= 'Z')
         ++count;
   } while (text[0]);

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

