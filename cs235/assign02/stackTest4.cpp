/***********************************************************************
* Program:
*    Assignment 02, Stack Test #4
*    Brother Cameron, CS 235
* Author: 
*    Greg Cameron
*    modified by Scott Ercanbrack
* Summary: 
*    Fourth test file for stack library 
***********************************************************************/
#include <iostream>
#include "stack.h"
using namespace std;

/*  main program tests Top function by pushing 5 items on stack and then
 *  doing a Top before a Pop to see if the data is correct. 
 */  
main()
{
   Stack st1(10);
   Stack st2(5);
   int data[10] = {1,2,3,4,5,6,7,8,9,10};
   int i;
   int item;

   cout << "TESTING ASSIGNMENT OPERATOR" << endl;
   for (i = 0; i < 10; ++i)
   {
      st1.push(data[i]);
   }
   
   // copy stack 1 to stack 2
   st2 = st1;
   
   cout << "Original Stack 1:" << endl;
   for (i = 0; i < 10; ++i)
   {
      item = st1.top();
      cout << item << " ";
      st1.pop();
   }
   
   // add new items to stack 1
   for (i = 0; i < 5; ++i)
   {
      st1.push(data[i] + 100);
   }
   
   cout << "\nStack 2 - copy of Original stack 1:" << endl;
   for (i = 0; i < 10; ++i)
   {
      item = st2.top();
      cout << item << " ";
      st2.pop();
   }

   cout << "\nNew Stack 1:" << endl;
   for (i = 0; i < 5; ++i)
   {
      item = st1.top();
      cout << item << " ";
      st1.pop();
   }


   cout << endl;
}
