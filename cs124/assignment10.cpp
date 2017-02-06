/***********************************************************************
* Program:
*    Assignment 10, Tax Burden
*    Brother Helfrich, CS124
* Author:
*    Brady Field
* Summary: 
*    
*    Uses input income to determine how much tax user should pay.
*    
*    
*    
*
*    Estimated:  1.0 hrs   
*    Actual:     0.5 hrs
*      need double brackets for multiple conditions
************************************************************************/

#include <iostream>
#include <iomanip>
using namespace std;

/*********************************************************************
* Takes income and calculates the amount of tax that should be paid
* based off the yearly amount
**********************************************************************/
float computeTax(float income)
{
   double tax;
   
   // change tax amount to yearly for calculation
   double yearlyIncome = (income * 12);
   
   // compute tax rate according to yearly income
   if ((0 <= yearlyIncome) && (yearlyIncome < 15100))
      tax = (yearlyIncome * 0.10);
   else if ((15100 <= yearlyIncome) && (yearlyIncome < 61300))
      tax = 1510 + (0.15 * (yearlyIncome - 15100));
   else if ((61300 <= yearlyIncome) && (yearlyIncome < 123700))
      tax = 8440 + (0.25 * (yearlyIncome - 61300));
   else if ((123700 <= yearlyIncome) && (yearlyIncome < 188450))
      tax = 24040 + (0.28 * (yearlyIncome - 123700));
   else if ((188450 <= yearlyIncome) && (yearlyIncome < 336550))
      tax = 42170 + (0.33 * (yearlyIncome - 188450));
   else if (336550 <= yearlyIncome)
      tax = 91043 + (0.35 * (yearlyIncome - 336550));
   
   // change tax back to monthly
   float monthlyTax = (tax / 12);
      
   return monthlyTax;
}

/**********************************************************************
* Prompts for income, calls function computeTax to determine tax bracket,
* and then displays result.
***********************************************************************/
int main()
{
   //prompt for income
   float income;
   cout << "Income: ";
   cin >> income;

   //set money display conditions
   cout.setf(ios::fixed);
   cout.setf(ios::showpoint);
   cout.precision(2);
     
   float taxMonthly = computeTax(income);

   cout << "Your tax is $" << taxMonthly << endl;
   return 0;
}
