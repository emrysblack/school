/***********************************************************************
* Program:
*    Assignment 02, Stack Test #1
*    Brother Cameron, CS 235
* Author: 
*    Greg Cameron
*    modified by Scott Ercanbrack 5/12/06
* Summary: 
*    First test file for stack library 
***********************************************************************/
#include <iostream>
#include "stack.h"
using namespace std;

/*  main program tests Push and Full functions by pushing 6 items on a 
 *  stack of 5.
 */  
main()
{
   Stack st(5);
   int data[5] = {1,2,3,4,5};
   int i;

   cout << "TESTING PUSH FUNCTION:" << endl;
   for (i = 0; i < 5; ++i)
      st.push(data[i]);
   cout << "TESTING FULL FUNCTION: Inserting a 6th item" << endl;
   cout << "This function should fail and leave error message" << endl;
   st.push(-1);
   cout << "Test Completed\n";
}
