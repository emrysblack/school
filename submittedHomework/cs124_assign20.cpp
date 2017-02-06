/***********************************************************************
* Program:
*    Assignment 20, Debit card choice
*    Brother Helfrich, CS124
* Author:
*    Brady Field
* Summary: 
*    Prompts users for bank account balances and charges bill to person
*    with more money.
*    
*    Estimated:  1.0 hrs   
*    Actual:     0.7 hrs
*      syntax for pointers, when to use & or *
************************************************************************/

#include <iostream>
#include <iomanip>
using namespace std;

void getIncomes(double &samBalance, double &sueBalance);
float getBill();

/**********************************************************************
* calls functions to prompt for balances and then the bill, sets
* pointer to largest account and then displays final balances after
* the bill
***********************************************************************/
int main()
{
   double samBalance;
   double sueBalance;
   double *chargeAccount;
   float bill;
   
   getIncomes(samBalance, sueBalance);
   bill = getBill();
   if (samBalance > sueBalance)
      chargeAccount = &samBalance;
   else
      chargeAccount = &sueBalance;
   *chargeAccount -= bill;

   // display
   cout.setf(ios::fixed);
   cout.setf(ios::showpoint);
   cout.precision(2);
   cout << "Sam's balance: $" << samBalance << endl
        << "Sue's balance: $" << sueBalance << endl;
   return 0;
}

/*********************************************************************
* prompts for balances of debit cards
**********************************************************************/
void getIncomes(double &samBalance, double &sueBalance)
{
   cout << "What is Sam's balance? ";
   cin >> samBalance;
   cout << "What is Sue's balance? ";
   cin >> sueBalance;
}

/*********************************************************************
* prompts for date charges
**********************************************************************/
float getBill()
{
   float charge1;
   float charge2;
   float charge3;

   cout << "Cost of the date:\n"
        << "\tDinner:    ";
   cin >> charge1;
   cout << "\tMovie:     ";
   cin >> charge2;
   cout << "\tIce cream: ";
   cin >> charge3;
   return (charge1 + charge2 + charge3);
}
