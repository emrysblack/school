/***********************************************************************
* Program:
*    Lab 0, Practice Lab Submission
*    Brother Jones, CS345
* Author:
*    Brady Field
* Summary: 
*    Prompts a user to input numbers and then displays how many
*    different numbers the user entered
************************************************************************/

#include <iostream>
using namespace std;

/**********************************************************************
 * prompts the user for numerical input. Exits when user enters a 0
 ***********************************************************************/
int promptIntegers()
{
   int count = 0;
   int input;
   do
   {
      cout << "Enter an integer: ";
      cin >> input;
      if (input)
         count++;
   } while (input != 0);
   return count;
}

/**********************************************************************
 * calls function to prompt for integers and displays the result
 ***********************************************************************/
int main()
{
   int count = promptIntegers();
   if (count)
   {
      cout << "You entered " << count 
           << (count > 1 ? " integers.\n" : " integer.\n");
   }
   else 
   {
      cout << "No non-zero integers were entered.\n";
   }
   
   return 0;
}

