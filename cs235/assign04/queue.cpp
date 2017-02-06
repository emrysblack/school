/***********************************************************************
* Program:
*    Assignment 04, Queue Library
*    Brother Cameron, CS 235
* Author:
*    Greg Cameron
*    Modified by Brother Ercanbrack 4/27/07 - added copy constructor
*       and overloaded assignment operator
*    Modified by Brother Twitchell 1/25/13
*       using ideas from his Winter 2013 CS 235
* Summary: 
*    This is a set of function definitions belonging to the Class
* definition contained in queue.h.  These functions are used to
* perform the various operations of a queue.
***********************************************************************/
using namespace std;
#include <iostream>
#include <cstdlib>
#include "queue.h"

/**********************************************************************
 * default constructor
 **********************************************************************/
Queue::Queue(int size)    
{
   maxSize = size > 0 ? size : 128; // don't allow a negative size
   back = 0;
   front = 0;
   queueItems = new int[maxSize];
}

/**********************************************************************
 * destructor
 **********************************************************************/
Queue::~Queue(void)
{
   delete [] queueItems;
}

/***********************************************************************
 * Queue Copy Constructor
 ***********************************************************************/
Queue::Queue(const Queue &aQueue)
{
   maxSize = aQueue.maxSize;
   front = aQueue.front;
   back = aQueue.back;
   queueItems = new int[maxSize];
   for (int i = 0; i < maxSize; i++)
   {
      queueItems[i] = aQueue.queueItems[i];
   }
}

/***********************************************************************
 * Overloaded assignment operator.
 ***********************************************************************/
Queue& Queue::operator =(const Queue &rtSide)
{
   if (this != &rtSide)
   {
   
      if( maxSize != rtSide.maxSize)
      {
         delete [] queueItems;
         queueItems = new int[rtSide.maxSize];
      }
      for (int i = 0; i < rtSide.maxSize; i++)
      {
         queueItems[i] = rtSide.queueItems[i];
      }
      maxSize = rtSide.maxSize;   //max size of queue
      back = rtSide.back;
      front = rtSide.front;
   }
   return *this;
}

/**********************************************************************
 * returns true if queue is empty
 **********************************************************************/
bool Queue::empty(void)
{
   return front == back;
}

/**********************************************************************
 * returns true if queue is full
 **********************************************************************/
bool Queue::full(void)
{
   return (back - front) >= maxSize;
}

/**********************************************************************
 * inserts item into back of queue, then increments number of items
 * in queue
 **********************************************************************/
void Queue::insert(int item)
{
   // --- check for overflow
   if (full())
   {
      cout << "queue overflow" << endl;
      exit(1); // a terrible thing for an object to do
   }
   queueItems[back % maxSize] = item;
   ++back;
}

/**********************************************************************
 * removes item from front of queue, then decrements number of items
 * in queue
 **********************************************************************/
int Queue::remove(void)
{
   int temp;
   
   if (empty())
   {
      cout << "queue underflow" << endl;
      exit(1); // a terrible thing for an object to do
   }
   temp = queueItems[front % maxSize];
   ++front;
   if (front >= maxSize)
   {
      front -= maxSize;
      back -= maxSize;
   }
   return temp;
}
