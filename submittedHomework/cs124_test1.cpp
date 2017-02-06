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
* prompt for dollars and convert to Euros
******************************************/
double computeEuros()
{
   double dollars;
   double euros;
  
   // Prompt for money in Dollars
   cout << "Please enter the amount in US Dollars: $";
   cin >> dollars;

   //perform calculation
   return euros = (dollars / 1.41);
}

/******************************************
* Main will call computeEuros and display
* result
*******************************************/
int main()
{
   double euros = computeEuros();
   
   // set money display options 
   cout.setf(ios::fixed);
   cout.setf(ios::showpoint);
   cout.precision(2);
   
   // Output two possible display options.
   // One for positive amounts
   // One for negative amounts

   if (euros >= 0)
      cout << "\tEuros: " << euros << endl;
   else
      cout << "\tEuros: " << "(" << euros << ")\n";

   return 0;
}

      
        
