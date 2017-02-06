/************************************************************
*
*  NAME: Brady Field
*  PROGRAM: list.h
*  PURPOSE: Class definition for a list object
*
************************************************************/
#ifndef LIST_H
#define LIST_H

using namespace std;
#include <iostream>
#include <cstdlib>
#include <string>

class List
{
   public:
      List();
      List(int numItems); // constructors
      ~List();            // destructor
      List(const List &rightHandSide);   // copy constructor
      const List &operator = (const List &rightHandSide);
      string getElementInSet(int index);
      int getSizeOfArray();
      void addElement(string element);
      bool isElementPresent(string element);
   private: // data members
      string* set;
      int sizeOfArray;
};
#endif
