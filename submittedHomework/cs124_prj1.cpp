/***********************************************************************
* Program:
*    Project 1, Personal Finance
*    Brother Helfrich, CS124
* Author:
*    Brady Field
* Summary: 
*    
*    Uses input figures to track finances and compare them to input actual
*    expenditures.
*    
*    
*
*    Estimated:  15 hrs   
*    Actual:     11.0 hrs
*      fixing order of operations and getting newline above header
************************************************************************/

#include <iostream>
#include <iomanip>
using namespace std;

/**********************************************************************
* Asks user to input their monthly income and returns it 
* to main
***********************************************************************/
float getIncome()
{
   float income; //money amounts
   cout << "Please enter the following:\n";
   cout << "\tYour monthly income: ";
   cin  >> income;

   return income;
}

/**********************************************************************
* Asks user to input their projected living expenses.
***********************************************************************/
float getProjectedLiving()
{
   float projectedLiving; //enter projected living
   cout << "\tYour projected living expenses: ";
   cin  >> projectedLiving;

   return projectedLiving;
}

/*********************************************************************
* Asks user to input what they actually paid for
* their living expenses
**********************************************************************/
float getActualLiving()
{
   float actualLiving; //enter actual living
   cout << "\tYour actual living expenses: ";
   cin  >> actualLiving;

   return actualLiving;
}

/*********************************************************************
* asks user to enter amount of what was actually taken
* in taxes
**********************************************************************/
float getActualTax()
{
   float actualTax; //enter actual tax
   cout << "\tYour actual taxes withheld: ";
   cin  >> actualTax;

   return actualTax;
}

/**********************************************************************
* Asks user to input what they actually
* paid as a tithing offering
***********************************************************************/
float getActualTithing()
{
   float actualTithing;  //enter actual tithing
   cout << "\tYour actual tithe offerings: ";
   cin  >> actualTithing;

   return actualTithing;
}

/*********************************************************************
* Prompts user to input the actual amount of what they
* paid for other things apart from the above listed expenses
**********************************************************************/
float getActualOther()
{
   float actualOther;  //enter actual other
   cout << "\tYour actual other expenses: ";
   cin  >> actualOther;

   return actualOther;
}

/*********************************************************************
* Calculates the amount of tax as it should have been based of the
* amount of income
**********************************************************************/
float computeTax(float income)
{
   double tax;
   // change tax amount to yearly for calculation
   double yearlyIncome = (income * 12);
   // compute tax rate according to yearly income
   if ((0 <= yearlyIncome) && (yearlyIncome < 15100))
      tax = (yearlyIncome * 0.10);
   if ((15100 <= yearlyIncome) && (yearlyIncome < 61300))
      tax = 1510 + (0.15 * (yearlyIncome - 15100));
   if ((61300 <= yearlyIncome) && (yearlyIncome < 123700))
      tax = 8440 + (0.25 * (yearlyIncome - 61300));
   if ((123700 <= yearlyIncome) && (yearlyIncome < 188450))
      tax = 24040 + (0.28 * (yearlyIncome - 123700));
   if ((188450 <= yearlyIncome) && (yearlyIncome < 336550))
      tax = 42170 + (0.33 * (yearlyIncome - 188450));
   if (336550 <= yearlyIncome)
      tax = 91043 + (0.35 * (yearlyIncome - 336550));
   // change tax back to monthly
   float monthlyTax = (tax / 12);
      
   return monthlyTax;
}

/*********************************************************************
* Calculates the amount of tithing user should have paid based
* of their income
**********************************************************************/
float computedTithing(float income)
{
   // 10% of income for tithing
   float calculatedTithing = (income * 0.10);
   return calculatedTithing;
}

/*********************************************************************
* Displays the gathered and calculated information in
* a table to be easily read by the user
**********************************************************************/
void display(float income, float projectedLiving, float actualTax,
             float actualTithing, float actualLiving, float actualOther)
{
   float projectedTax = computeTax(income);
   float projectedTithing = computedTithing(income);
   float projectedOther = income - projectedTax -
      projectedTithing - projectedLiving;
   float actualDelta = income - actualTax -
      actualTithing - actualLiving - actualOther;
   float projectedDelta = income - projectedTax -
      projectedTithing - projectedLiving - projectedOther;
   
   cout.setf(ios::fixed);  //set up money display settings
   cout.setf(ios::showpoint);
   cout.precision(2);
   cout << "\n"
        << "The following is a report" //header
        << " on your monthly expenses\n"
        << "\tItem            Projected       Actual" << endl
        << "\t=============== =============== ===============\n";
   cout << "\tIncome" //money table
        << setw(11) << "$" << setw(10) << income
        << setw(6) << "$" << setw(14) << income << endl;
   cout << "\tTaxes"
        << setw(12) << "$" << setw(10) << projectedTax
        << setw(6) << "$" << setw(14) << actualTax << endl;
   cout << "\tTithing"
        << setw(10) << "$" << setw(10) << projectedTithing
        << setw(6) << "$" << setw(14) << actualTithing << endl;
   cout << "\tLiving"
        << setw(11) << "$" << setw(10) << projectedLiving
        << setw(6) << "$" << setw(14) << actualLiving << endl;
   cout << "\tOther"
        << setw(12) << "$" << setw(10) << projectedOther
        << setw(6) << "$" << setw(14) << actualOther << endl;
   cout << "\t=============== =============== ===============" << endl //footer
        << "\tDelta"
        << setw(12) << "$" << setw(10) << projectedDelta
        << setw(6) << "$" << setw(14) << actualDelta << endl;
   return;
}

/*********************************************************************
* starts main which will call functions for input and then
* call function to display results in table
**********************************************************************/
int main()
{
   cout << "This program keeps track of your monthly budget\n";
   float income = getIncome();
   float projectedLiving = getProjectedLiving();
   float actualLiving = getActualLiving();
   float actualTax = getActualTax();
   float actualTithing = getActualTithing();
   float actualOther = getActualOther();
   
   display(income, projectedLiving, actualTax,
           actualTithing, actualLiving,  actualOther);
   
   return 0;
}
