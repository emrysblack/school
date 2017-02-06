/*******************************************************************
 *
 *     FILE: list.h
 *
 *  PURPOSE: Contains the class definition of a Node and a List
 *
 *******************************************************************/
#ifndef _LIST_H
#define _LIST_H

using namespace std;
#include <iostream>
#include <cstdlib>

class Node
{
   private:
      int data;                 // --- data in each node
      Node* next;               // --- pointer to next node

   public:
      Node();                   // --- Creates empty node
      Node* getNext();          // --- returns next pointer of a node
      int getData();            // --- returns data of a node
      void setData(int item);   // --- stores item in data member of current node
      void setNext(Node* node); // --- sets next to point to node
};

class List
{
   private:
      int numItems;
      Node* firstNode;
  
   public:
      List();
      ~List();
      List(const List &listToCopy);   // copy constructor
      List& operator = (const List &rightSide);
      void insert(int item, int pos);
      void remove(int pos);
      int lookup(int item) const;
      int getData(int pos) const;
      int empty(void) const;
      int getNumItems(void) const;
};
#endif
