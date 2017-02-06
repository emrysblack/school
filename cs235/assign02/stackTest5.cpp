/***********************************************************************
* Program:
*    Assignment 02, Stack Test #5
*    Brother Cameron, CS 235
* Author: 
*    Greg Cameron
*    modified by Scott Ercanbrack
* Summary: 
*    Fifth test file for stack library 
***********************************************************************/
#include <iostream>
#include "stack.h"
using namespace std;

void displayStack(Stack st);

/*  main program tests Top function by pushing 5 items on stack and then
 *  doing a Top before a Pop to see if the data is correct. 
 */  
main()
{
   Stack st1(10);
   int data[5] = {1,2,3,4,5};
   int i;
   int item;

   cout << "TEST COPY CONSTRUCTOR" << endl;
   for (i = 0; i < 5; ++i)
   {
      st1.push(data[i]);
   }

   // display original stack
   displayStack(st1);
   
   // add 5 more items to stack
   for (i = 0; i < 5; ++i)
   {
      st1.push(data[i] + 100);
   }
   
   // display new stack with 10 items.
   displayStack(st1);
}

/********************************************************
*  Displays the stack passed in and then addings items
*  to the local stack - but since it's a pass by value
*  parameter we don't really want the values added.
*  We want the stack unchanged.
*******************************************************/
void displayStack(Stack st)
{
   int item;
   cout << "\nStack:\n";
   while(!st.empty())
   {
      item = st.top();
      cout << item << " ";
      st.pop();
   }
   cout << endl;
   
   // This is really just to test the copy constructor
   for (int i = 0; i < 5; i++)
   {
      st.push(i + 1000);
   }
}
