/***********************************************************************
* Program:
*    Test 2, 
*    Brother Helfrich, CS124
* Author:
*    Brady Field
* Summary: 
*    Will calculate a final balance of money over a given period of
*     time with compound interest incrementing it every year
*    
*    Estimated:  0.5 hrs   
*    Actual:     0.5 hrs
*      Forgot to convert interest from percent to a decimal number
************************************************************************/

#include <iostream>
using namespace std;

/**********************************************************************
* Propmts for amount to be invested
***********************************************************************/
double getDeposit()
{
   double deposit;
   cout << "How much are you investing? ";
   cin >> deposit;
   return deposit;
}

/**********************************************************************
* Prompts for the interest rate
***********************************************************************/
float getInterest()
{
   float interest;
   cout << "What is the interest rate in percent? ";
   cin >> interest;
   return interest *0.01; // change to decimal for calculation
}

/**********************************************************************
* Prompts for total years of investment
***********************************************************************/
int getYears()
{
   int years;
   cout << "How long will this investment grow in years? ";
   cin >> years;
   return years;
}

/**********************************************************************
* Calculates the ending balance by looping through all the years
* and returning the total
***********************************************************************/
double computeBalance(double deposit, float interest, int years)
{
   double balance;
   for (balance = deposit; years > 0; years--)
      balance = balance + (balance * interest);
   return balance;
}

/**********************************************************************
* Calls functions and displays the ending balance 
***********************************************************************/
int main()
{
   double deposit = getDeposit();
   float interest = getInterest();
   int years = getYears();
   double balance = computeBalance(deposit, interest, years);
   
   // set up money display settings
   cout.setf(ios::fixed);
   cout.setf(ios::showpoint);
   cout.precision(2);

   // display ending balance
   cout << "At the end of "
        << years
        << " years, you will have $"
        << balance << endl;
   
   return 0;
}
