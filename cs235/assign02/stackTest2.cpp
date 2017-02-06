/***********************************************************************
* Program:
*    Assignment 02, Stack Test #2
*    Brother Cameron, CS 235
* Author: 
*    Greg Cameron
*    Modified by Scott Ercanbrack 5/12/06
* Summary: 
*    Second test file for stack library 
***********************************************************************/
#include <iostream>
#include "stack.h"
using namespace std;

/*  main program tests Pop and Empty functions by pushing 5 items on a 
 *  stack of 5 and then attempting to pop 6 items off stack.
 */  
main()
{
   int i;
   int data[5] = {1,2,3,4,5};
   Stack st(5);

   // --- Push items onto stack
   for (i = 0; i < 5; ++i)
      st.push(data[i]);

   // -- Test Pop function
   cout << "TESTING POP FUNCTION:" << endl;
   for (i = 0; i < 5; ++i)
      st.pop();
   cout << "TESTING EMPTY FUNCTION: " << endl;
   cout << "\tTry popping a value off an empty stack." << endl;
   cout << "\tProgram should exit and fail." << endl;
   st.pop();
   cout << "Test Completed\n";
}
