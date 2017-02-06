/***********************************************************************
* Program:
*    Assignment 09, Tax Bracket
*    Brother Helfrich, CS124
* Author:
*    Brady Field
* Summary: 
*    
*    Uses input income to determine which tax bracket percentage
*    a user is in.
*    
*    
*
*    Estimated:  1.0 hrs   
*    Actual:     0.5 hrs
*      need double brackets for multiple conditions
************************************************************************/

#include <iostream>
using namespace std;

/**********************************************************************
* Prompts for income and sets tax percentage according to tax table
***********************************************************************/
int computeTax()
{
   int tax;
   float income;
   
   //prompt for income 
   cout << "Income: ";
   cin >> income;
   // determine tax bracket

   if (income <= 15100)
      tax = 10;
   if ((income > 15100) && (income <= 61300))
      tax = 15;
   if ((income > 61300) && (income <= 123700))
      tax = 25;
   if ((income > 123700) && (income <= 188450))
      tax = 28;
   if ((income > 188450) && (income <= 336550))
      tax = 33;
   if (income > 336550)
      tax = 35;
   return tax;
}
 
/**********************************************************************
* Calls function computeTax to determine tax bracket, and then displays result.
***********************************************************************/
int main()
{
   int taxBracket = computeTax();

   cout << "Your tax bracket is " << taxBracket << "%\n";
   return 0;
}
