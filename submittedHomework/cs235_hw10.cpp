/***********************************************************************
* Program:
*    Homework 10, List Class 
*    Brother Twitchell, CS235
* Author:
*    Brady Field
* Summary: 
*    Contains function definitions for list class and node class
************************************************************************/

#include <iostream>
#include "list.h"
using namespace std;

/**********************************************************************
 * Default constructor for Node class
 **********************************************************************/
Node::Node()
{
   data = 0;
   next = NULL;
}
 
/**********************************************************************
 * Gets pointer to next node in list
 **********************************************************************/
Node* Node::getNext()
{
   return next;
}

/**********************************************************************
 * Gets integer of current node
 **********************************************************************/
int Node::getData()
{
   return data;
}

/**********************************************************************
 * Stores an integer in the current node
 **********************************************************************/
void Node::setData(int item)
{
   data = item;
}

/**********************************************************************
 * Sets pointer to the next node
 **********************************************************************/
void Node::setNext(Node* node)
{
   next = node;
}

/**********************************************************************
 * Default constructor for list class
 **********************************************************************/
List::List()
{
   firstNode = new Node;
   numItems = 0; // count first node
}
 
/**********************************************************************
 * Destructor for list class
 **********************************************************************/
List::~List()
{
   Node* current = firstNode;
   Node* next = firstNode->getNext();
   
   delete current; // delete first node
   
   // delete all nodes after
   while (next != NULL)
   {
      current = next;
      next = current->getNext();
      delete current;
   }
   
}

/**********************************************************************
 * Copy constructor for list class
 **********************************************************************/
List::List(const List &listToCopy)
{
   firstNode = new Node;
   *this = listToCopy;
}

/**********************************************************************
 * Overloaded assignment operator for list class
 **********************************************************************/
List& List::operator = (const List &rightSide)
{
   this->~List(); // clean whole list

   // start a new list
   numItems = 0;
   firstNode = new Node;
   
   // copy contents
   for (int i = 0; i < rightSide.getNumItems(); i++)
      insert(rightSide.getData(i),i);
}

/**********************************************************************
 * Inserts item into the list at a specified position
 **********************************************************************/
void List::insert(int item, int pos)
{
   Node* next; // node after position
   Node* temp; // new node to be inserted
   Node* previous = firstNode; // node before position
   
   // check to see if position belongs on end
   if (pos >= numItems)
      pos = numItems;
   
   // go to right node
   for (int i = 0; i < pos - 1; i++)
      previous = previous->getNext();
   next = previous->getNext();
      
   if (pos != 0) // case if inserting in middle or on end of list
   {
      // create new node and link
      temp = new Node;
      temp->setNext(previous->getNext());
      previous->setNext(temp);
      
      // push data
      previous = previous->getNext();
      previous->setData(item);
   }
   
   else // inserting as fist item in list
   {
      // create new node and link
      temp = new Node;
      temp->setNext(previous); // previous is first node
      firstNode = temp; // temp is new fist node
      
      // push data
      firstNode->setData(item);
   }
   numItems++;
}

/**********************************************************************
 * Removes item from list at specified position
 **********************************************************************/
void List::remove(int pos)
{
   Node* previous = firstNode;
   Node* index = previous->getNext();

   if (pos == 0) // if first item in list
   {
      firstNode = index;
      delete previous;
   }
   else
   {
      // go to right location
      for (int i = 0; i < pos - 1 && index->getNext() != NULL; i++)
      {
         previous = index;
         index = index->getNext();
      }
      // link previous item to next item
      previous->setNext(index->getNext());
      delete index;
   } 
   numItems--;   
}
 
/**********************************************************************
 * Searches for first instance of item in list and returns index
 **********************************************************************/
int List::lookup(int item) const
{
   Node* index = firstNode;
   int pos = -1;
   
   if (!empty())
   {
      for (int i = 0; i < numItems && pos == -1; i++)
      {
         if (index->getData() == item)
            pos = i;
         index = index->getNext();
      }
   }   
   return pos;
}

/**********************************************************************
 * Returns the value stored in the specified index
 **********************************************************************/
int List::getData(int pos) const
{
   Node* index = firstNode;
   
   if (pos > numItems)
      pos = numItems;
   // go to correct location
   for (int i = 0; i < pos; i++)
      index = index->getNext();
   return index->getData();
}

/**********************************************************************
 * Returns true if number of items is 0
 **********************************************************************/
int List::empty(void) const
{
   return numItems == 0;
}

/**********************************************************************
 * Returns number of items inserted in current list, not how many 
 * nodes exist
 **********************************************************************/
int List::getNumItems(void) const
{
   return numItems;
}
