/******************************************************
* Program:
*    Test 1, Converting Dollars to Euros
*    Brother Helfrich, CS124
* Author:
*    Brady Field
* Summary: 
*    A simple program to convert Dollars into Euros.
*    And hopefully the easiest test ever!     
********************************************************/
#include <iostream>
#include <iomanip>
using namespace std;

/*****************************************
* prompt for money in dollars
******************************************/
double getDollars()
{
   double dollars;

   cout << "Please enter the amount in US Dollars: $";
   cin >> dollars;

   return dollars;
}

/*****************************************
* convert to Euros
******************************************/
double computeEuros(double dollars)
{
   return (dollars / 1.41);
}

/******************************************
* display results
*******************************************/
void display(double euros)
{
   // set money display options 
   cout.setf(ios::fixed);
   cout.setf(ios::showpoint);
   cout.precision(2);

   cout << "\tEuros: ";
   // Output two possible display options.
   // One for positive amounts
   // One for negative amounts

   if (euros >= 0)
      cout << euros << endl;
   else
      cout << "(" << euros << ")\n";
}

/******************************************
* Main will call functions to prompt,
* convert, and display results
*******************************************/
int main()
{
   dollars = getDollars();
   double euros = computeEuros(dollars);
   display(euros);
   
   return 0;
}

      
        
