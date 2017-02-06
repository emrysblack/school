/***********************************************************************
* Program:
*    Assignment 06, Prompt for Income
*    Brother Helfrich, CS124
* Author:
*    Brady Field
* Summary: 
*    Asks the user to input their income and displays the result
*    on screen.
*    
*    
*    
*
*    Estimated:  1.0 hrs   
*    Actual:     1.0 hrs
*      hardest part: getting syntax of calling functions right
************************************************************************/

#include <iostream>
#include <iomanip>
using namespace std;

/**********************************************************************
* Prompts user to input their income.
* 
***********************************************************************/
float getIncome()
{
   float income;
   cout << "\tYour monthly income: ";
   cin >> income;
   return income;
}
/**********************************************************************
*Displays users income back on the screen.
*
***********************************************************************/
int main()
{
   float income = getIncome();
   cout.setf(ios::fixed);
   cout.setf(ios::showpoint);
   cout.precision(2);
   cout << "Your income is: "
        << "$" << setw(9) << income << endl;
   return 0;
}
