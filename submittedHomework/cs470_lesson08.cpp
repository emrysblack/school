/***********************************************************************
* Program:
*    Lesson 08, Passwords
*    Brother Smithb, CS470
* Author:
*    Brady Field
* Summary: 
*    This program will inform a user of the complexity of a given password.
*    In an actual application with longer passwords, the ZZ or similar
*    large number library would be used to avoid overflow, but this
*    works just fine for simple passwords
************************************************************************/
#include <iostream>
#include <string>
#include <cmath>
using namespace std;

/***********************************************************************
* computes the complexity of a given password to see if it uses
* lower case, upper case, digits, and special characters
************************************************************************/
long calcStrength(string password)
{
   bool lower = false; // 26 lower case letters
   bool upper = false; // 26 upper case letters
   bool special = false; // 32 other printable characters on a keyboard
   bool digit = false; // 10 digits
   
   // scan for character types in the password
   for (int i = 0; i < password.length(); i++)
   {
      if (islower(password[i]))
         lower = true;
      else if (isupper(password[i]))
         upper = true;
      else if (isdigit(password[i]))
         digit = true;
      else
         special = true;
   }
   
   // total number of possible characters
   int calc = lower * 26 + upper * 26 + digit * 10 + special * 32;
   return pow(calc, password.length()); // compute possible combinations by raising possibles to length
}

/***********************************************************************
* Prompts user for a password, calculates the strength and displays
* the results
************************************************************************/
int main()
{
   // prompt for password
   string password;
   cout << "Please enter the password: ";
   cin >> password;
   
   // compute combinations
   long combo = calcStrength(password);
   cout << "There are " << combo << " combinations\n";
   
   // use log math to simplify counting required number of digits for representation
   cout << "That is equivalent to a key of " << (long)log2(combo) << " bits\n";
   return 0;
}
