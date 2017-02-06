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
template <typename StackElement>
Stack<StackElement>::Stack(int size)
{
   myTop = 0;
   maxSize = size;
   stackItems = new StackElement [size];
}
 
/***********************************************************************
 * Copy constructor. Will do a deep copy of the elements
 **********************************************************************/
template <typename StackElement>
Stack<StackElement>::Stack(const Stack<StackElement> &aStack)
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
template <typename StackElement>
Stack<StackElement>::~Stack()
{
   myTop = 0;
   maxSize = 0;
   delete [] stackItems;
}

/**********************************************************************
 * Returns current item on top of stack
 **********************************************************************/
template <typename StackElement>
StackElement Stack<StackElement>::top(void)
{
   return stackItems[myTop - 1]; // get last item put on
}
 
/**********************************************************************
 * Puts a new item on top of the stack
 **********************************************************************/
template <typename StackElement>
void Stack<StackElement>::push(StackElement item)
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
template <typename StackElement>
void Stack<StackElement>::pop(void)
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
template <typename StackElement>
bool Stack<StackElement>::empty(void)
{
   return (myTop == 0);
}
 
/**********************************************************************
 * Returns true if stack is full
 **********************************************************************/
template <typename StackElement>
bool Stack<StackElement>::full(void)
{
   return (myTop >= maxSize);
}
 
/**********************************************************************
 * Assignment operator for stack class
 **********************************************************************/
template <typename StackElement>
Stack<StackElement>& Stack<StackElement>::operator = (const Stack<StackElement> &rtSide)
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
 
