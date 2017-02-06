/***********************************************************************
* Author:
*    Brady Field
* Summary: 
*    contains function definitions for class list
***********************************************************************/

#include <iostream>
#include "list.h"
using namespace std;

/*********************************************************************
 * constructors for the List class
 *********************************************************************/
List::List() // default constructor
{
   sizeOfArray = 0;
}

List::List(int numItems) // constructor without array
{
   sizeOfArray = 0;
   set = new string [numItems]; // set dynamic memory
}

/*********************************************************************
 * destructor returns dynamic memory to system
 *********************************************************************/
List::~List()
{
   sizeOfArray = 0;
   delete [] set;
}

/*********************************************************************
 * copy constructor
 ********************************************************************/
List::List(const List &rightHandSide)
{
   sizeOfArray = rightHandSide.sizeOfArray;
   set = new string [sizeOfArray]; // allocate memory
   for (int i = 0; i < sizeOfArray; i++) // copy contents over
      set[i] = rightHandSide.set[i];
}

/*********************************************************************
 * override to assignment operator to make sure that elements don't 
 * copy address of existing object, but copy contents
 *********************************************************************/
const List &List::operator = (const List &rightHandSide)
{
   // reallocate memory if not same as list being copied from
   if (sizeOfArray != rightHandSide.sizeOfArray)
   {
      delete [] set;
      sizeOfArray = rightHandSide.sizeOfArray;
      set = new string [sizeOfArray]; 
   }

   // copy contents over
   sizeOfArray = rightHandSide.sizeOfArray;
   for (int i = 0; i < sizeOfArray; i++)
      set[i] = rightHandSide.set[i];
   return *this;
}

/*********************************************************************
 * returns the number stored in the array at the given index
 *********************************************************************/
string List::getElementInSet(int index)
{
   return set[index];
}

/*********************************************************************
 * returns the number of elements in the array
 *********************************************************************/
int List::getSizeOfArray()
{
   return sizeOfArray;
}

/*********************************************************************
 * receives the file name specified on the command line and reads the 
 * first line to know how many values on second line to read in
 *********************************************************************/
void List::addElement(string element)
{
   set[sizeOfArray] = element; // use sizeOfArray as index
   sizeOfArray++;
}

/*********************************************************************
 * takes input number from file and compares it to everything already
 * in set to determine if it is already in there or not
 *********************************************************************/
bool List::isElementPresent(string element)
{
   for (int i = 0; i < sizeOfArray; i++)
   {
      if (set[i] == element)
         return true;
      else // do nothing
         ;
   }
   return false;
}
