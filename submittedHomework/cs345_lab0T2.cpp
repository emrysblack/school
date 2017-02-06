/***********************************************************************
* Program:
*    Lab 0, Practice Lab Submission
*    Brother Jones, CS345
* Author:
*    Brady Field
* Summary: 
*    Prompts a user to input numbers and then displays how many
*    different numbers the user entered
************************************************************************
*****************************************************************************
*
* - Start count at -1 to remove redundant if statement
* - Changed while condition to be implicit true or false
*
*****************************************************************************/

#include <iostream>
using namespace std;

/**********************************************************************
 * prompts the user for numerical input. Exits when user enters a 0
 ***********************************************************************/
int promptIntegers()
{
   int count = -1; // do not count 0 used for exit
   int input;
   do
   {
      cout << "Enter an integer: ";
      cin >> input;
      count++;
   } while (input);
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

