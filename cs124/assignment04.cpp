/***********************************************************************
* Program:
*    Assignment 04, Display Budget
*    Brother Helfrich, CS124
* Author:
*    Brady Field
* Summary: 
*    Displays and example of a monthly budget.
*    
*    
*    
*    
*
*    Estimated:  1.5 hrs   
*    Actual:     1.7 hrs
*      Figuring out spacing, took me a minute. Had to read instructions better.
************************************************************************/

#include <iostream>
#include <iomanip>
using namespace std;

/**********************************************************************
* Do I need to do this again? Main is the main function. The start of
* exocution of the program.
***********************************************************************/
int main()
{
   cout.setf(ios::fixed);
   cout.setf(ios::showpoint);
   cout.precision(2);

   cout << "\tItem           Projected\n"
        << "\t=============  ==========\n"
        << "\tIncome         $"  << setw(9)
        << 1000.0 << endl
        << "\tTaxes          $"  << setw(9)
        << 100.0 << endl
        << "\tTithing        $"  << setw(9)
        << 100.0 << endl
        << "\tLiving         $"  << setw(9)
        << 650.0 << endl
        << "\tOther          $"  << setw(9)
        << 90.0 << endl
        << "\t=============  ==========\n"
        << "\tDelta          $"  << setw(9)
        << 60.0 << endl;
   return 0;
}
