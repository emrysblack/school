/***********************************************************************
* Program:
*    Assignment 45, Iterators
*    Brother Boyer, CS165
* Author:
*    Brady Field
* Summary: 
*    This program is designed to demonstrate using iterators to walk
*    through a container or collection of elements.
*
*    Estimated:  1.0 hrs   
*    Actual:     0.5 hrs
*      Iterators were confusing to implement differently than pointers
************************************************************************/

#include <iostream>
#include <string>
using namespace std;

/**********************************************************************
 * Instructions: Please fill in the code below the comments to demonstrate
 * three ways to walk through a string object
 ***********************************************************************/
int main()
{
   // fetch the text
   string text;
   cout << "What is the text: ";
   getline(cin, text);

   // display the text using the array notation
   cout << "Array:    ";
   // <your code goes here>
   for (int i = 0; i < text.size(); i++)
      cout << text[i];
   cout << endl;
   
   // display the text using the pointer notation
   cout << "Pointers: ";
   // <your code goes here>
   for (char *p = &text[0]; *p; p++)
      cout << *p;
   cout << endl;

   // display the text using the iterator notation
   cout << "Iterator: ";
   // <your code goes here>
   for (char *iterator = &text[0]; *iterator; iterator++)
      cout << *iterator;
   cout << endl;
   
   return 0;
}
