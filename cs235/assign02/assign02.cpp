/***********************************************************************
* Program:
*    Homework 02, Stacks 
*    Brother Twitchell, CS 235     
* Author:
*    Brady Field
* Summary: 
*    contains function definitions for class Stack
***********************************************************************/

#include <iostream>
#include "stack.h"
using namespace std;

/**********************************************************************
 * Default constructor. Sets up an array for 100 items
 **********************************************************************/
Stack::Stack(int size)
{
   myTop = 0;
   maxSize = size;
   stackItems = new int [size];
}
 
/***********************************************************************
 * Copy constructor. Will do a deep copy of the elements
 **********************************************************************/
Stack::Stack(const Stack &aStack)
{
   maxSize = aStack.maxSize;
   myTop = aStack.myTop;
   stackItems = new int [aStack.maxSize];

   for (int i = 0; i < maxSize; i++) // fill array
      stackItems[i] = aStack.stackItems[i];
}
 
/**********************************************************************
 * Destructor to return allocated memory
 **********************************************************************/
Stack::~Stack()
{
   myTop = 0;
   maxSize = 0;
   delete [] stackItems;
}

/**********************************************************************
 * Returns current item on top of stack
 **********************************************************************/
int Stack::top(void)
{
   return stackItems[myTop - 1]; // get last item put on
}
 
/**********************************************************************
 * Puts a new item on top of the stack
 **********************************************************************/
void Stack::push(int item)
{
   if (!full())
   {
      stackItems[myTop] = item;
      myTop++;
   }
   else
   {
      cout << "ERROR: Stack Overflow\n";
      exit(1);
   }
}
 
/**********************************************************************
 * Removes to item from stack
 **********************************************************************/
void Stack::pop(void)
{
   if (!empty())
      myTop--;
   else
   {
      cout << "ERROR: Stack Underflow\n";
      exit(1);
   }
}
 
/**********************************************************************
 * Returns true if stack is empty
 **********************************************************************/
bool Stack::empty(void)
{
   return (myTop == 0);
}
 
/**********************************************************************
 * Returns true if stack is full
 **********************************************************************/
bool Stack::full(void)
{
   return (myTop >= maxSize);
}
 
/**********************************************************************
 * Assignment operator for stack class
 **********************************************************************/
Stack& Stack::operator = (const Stack &rtSide)
{
   if (maxSize != rtSide.maxSize) // if array isn't right size, reallocate
   {
      maxSize = rtSide.maxSize;
      delete [] stackItems;
      stackItems = new int [rtSide.maxSize];
   }

   myTop = rtSide.myTop;
   for (int i = 0; i < maxSize; i++) // fill array
      stackItems[i] = rtSide.stackItems[i];

   return *this;
}
 
