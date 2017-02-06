/***********************************************************************
* Program:
*    Assignment 08, Full Tithe Payer
*    Brother Helfrich, CS124
* Author:
*    Brady Field
* Summary: 
*    This program will compute if a user is a full tithe payer using
*    the complicated formula provided in the scriptures:
*        And after that, those who have thus been tithed shall 
*        pay one-tenth of all their interest annually; and this 
*        shall be a standard law unto them forever, for my holy 
*        priesthood, saith the Lord.  D&C 119:4
*
*    Estimated:  1.5 hrs   
*    Actual:     0.7 hrs
*      figuring out how to represent bool expression and writing comments
************************************************************************/

#include <iostream>
using namespace std;

/*****************************************************
 * Will calculate if tithes cover income amount or not
 *****************************************************/
bool isFullTithePayer(float income, float tithe)
{
   float projectedMoney;
   // get max income their their tithing should represent if full tithe payer
   projectedMoney = (tithe * 10);
   // compares projected max to actual income
   bool fullTithePayer = (projectedMoney >= income); 
   return fullTithePayer; // or false, depending...
}


/**********************************************************************
 * Main will call isFullTithePayer() and display an appropriate message
 * to the user based on the results
 ***********************************************************************/
int main()
{
   float income;
   float tithe;


   // prompt user for income
   cout << "Income: ";
   cin  >> income;

   // prompt user for tithe
   cout << "Tithe: ";
   cin  >> tithe;

   // give the user his tithing report
   if (isFullTithePayer(income, tithe))
      cout << "You are a full tithe payer.\n"; 
   else
      cout << "Will a man rob God?  Yet ye have robbed me.\n" 
           << "But ye say, Wherein have we robbed thee?\n"
           << "In tithes and offerings.  Malachi 3:8\n";

   return 0;
}
