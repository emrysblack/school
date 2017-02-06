/***********************************************************************
* Program:
*    Assignment 02, Stack Test #3
*    Brother Cameron, CS 235
* Author: 
*    Greg Cameron
*    modified by Scott Ercanbrack
* Summary: 
*    Third test file for stack library 
***********************************************************************/
#include <iostream>
#include "stack.h"
using namespace std;

/*  main program tests Top function by pushing 5 items on stack and then
 *  doing a Top before a Pop to see if the data is correct. 
 */  
main()
{
   Stack st(5);
   int data[5] = {1,2,3,4,5};
   int i;
   int item;

   for (i = 0; i < 5; ++i)
      st.push(data[i]);

   cout << "TESTING TOP FUNCTION:" << endl;
   for (i = 0; i < 5; ++i)
   {
      item = st.top();
      cout << item << " ";
      st.pop();
   }
   cout << endl;
}
