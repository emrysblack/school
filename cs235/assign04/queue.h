/***********************************************************************
 * Program:
 *    Assignment 04, Queue Header File
 *    Brother Cameron, CS 235
 * Author:
 *    Greg Cameron
 *    modified by Brother Ercanbrack 5/19/06
 *    modified by Brother Twitchell 1/25/13
 *       using ideas from his Winter 2013 CS 235
 * Summary: 
 *    This is the class definition for queue
 ***********************************************************************/

#ifndef _QUEUE_H
#define _QUEUE_H

using namespace std;
#include <iostream>

class Queue
{
 private:
  int front;                  // --- index of front of queue
  int back;                   // --- index of back of queue
  int maxSize;                // --- max storage capacity of array
  int *queueItems;            // --- array containing queue items

 public:
  Queue(int = 128);           // --- constructor
  Queue(const Queue &aQueue); // --- copy constructor
  ~Queue(void);               // --- destructor
  void insert(int item);      // --- insert item into back of queue
  int remove(void);           // --- remove item from front of queue
  bool empty(void);           // --- returns 1 if queue is empty, 0 otherwise
  bool full(void);            // --- returns 1 if queue is full, 0 otherwise
  Queue& operator = (const Queue &rtSide); // overloaded assignment operator
};

#endif
