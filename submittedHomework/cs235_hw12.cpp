/***********************************************************************
* Program:
*    Homework 12, Opinion Papers 
*    Brother Twitchell, CS235
* Author:
*    Brady Field
* Summary: 
*    Calculates sequence of numbers and displays the one specified
************************************************************************/

#include <iostream>
#include <stdlib.h>
using namespace std;

/*******************************************************************
 *  PURPOSE: Contains the class definition of a Node
 *******************************************************************/
class Node
{
   private:
      long data;                 // --- data in each node
      Node* next;               // --- pointer to next node
      Node* prev;               // --- pointer to previous node

   public:
      Node();                   // --- Creates empty node
      Node* getNext();          // --- returns next pointer of a node
      Node* getPrev();          // --- returns previous pointer of a node
      long getData();            // --- returns data of a node
      void setData(long item);   // --- stores item in current node
      void setNext(Node* node); // --- sets next to point to node
      void setPrev(Node* node); // --- sets previous to point to node
};

/*******************************************************************
 *  PURPOSE: Contains the class definition of a List
 *******************************************************************/
class List
{
   private:
      int numItems;
      Node* firstNode;
      Node* lastNode;
  
   public:
      List();
      ~List();
      List(const List &listToCopy);   // copy constructor
      List& operator = (const List &rightSide);
      Node* getFirstNode(); // returns pointer to first
      Node* getLastNode(); // returns pointer to last
      void insert(long item, int pos);
      void remove(int pos);
      int lookup(long item) const;
      long getData(int pos) const;
      int empty(void) const;
      int getNumItems(void) const;
      void display(void) const;
      void displayBack(void) const;
};
const List operator + (List &leftSide, List &rightSide);

/**********************************************************************
 * Default constructor for Node class
 **********************************************************************/
Node::Node()
{
   data = 0;
   next = NULL;
   prev = NULL;
}
 
/**********************************************************************
 * Gets pointer to next node in list
 **********************************************************************/
Node* Node::getNext()
{
   return next;
}

/**********************************************************************
 * Gets pointer to previous node in list
 **********************************************************************/
Node* Node::getPrev()
{
   return prev;
}

/**********************************************************************
 * Gets integer of current node
 **********************************************************************/
long Node::getData()
{
   return data;
}

/**********************************************************************
 * Stores an integer in the current node
 **********************************************************************/
void Node::setData(long item)
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
 * Sets pointer to the next node
 **********************************************************************/
void Node::setPrev(Node* node)
{
   prev = node;
}

/**********************************************************************
 * Default constructor for list class
 **********************************************************************/
List::List()
{
   firstNode = NULL;// new Node;
   lastNode = firstNode;
   numItems = 0; // count first node
}
 
/**********************************************************************
 * Destructor for list class
 **********************************************************************/
List::~List()
{
   Node* current = firstNode;
   Node* next = firstNode;
   if (current != NULL)
   {
      next = firstNode->getNext();
      delete current; // delete first node
   }
   
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
   firstNode = NULL;
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
   firstNode = NULL;
   
   // copy contents
   for (int i = 0; i < rightSide.getNumItems(); i++)
      insert(rightSide.getData(i),i);
}

/**********************************************************************
 * Returns the pointer to the first node
 **********************************************************************/
Node* List::getFirstNode()
{
   return firstNode;
}

/**********************************************************************
 * Returns the pointer to the first node
 **********************************************************************/
Node* List::getLastNode()
{
   return lastNode;
}

/**********************************************************************
 * Inserts item into the list at a specified position
 **********************************************************************/
void List::insert(long item, int pos)
{
   Node* next; // node after position
   Node* temp; // new node to be inserted
   Node* previous = firstNode; // node before position
   
   // check to see if position belongs on end
   if (pos > numItems)
      pos = numItems;
   
   // go to right node
   for (int i = 0; i < pos - 1; i++)
      previous = previous->getNext();
   if (previous != NULL)
      next = previous->getNext(); // not only item in list
      
   if (pos != 0) // case if inserting in middle or on end of list
   {
      // create new node and link
      temp = new Node;
      temp->setNext(previous->getNext());
      temp->setPrev(previous);
      previous->setNext(temp);
      if (temp->getNext() == NULL)
         lastNode = temp;
      
      // push data
      temp->setData(item);
   }
   
   else // inserting as first item in list
   {
      // create new node and link
      temp = new Node;
      temp->setNext(previous); // previous is first node
      temp->setPrev(NULL);
      if (previous != NULL)
         previous->setPrev(temp);
      else
         lastNode = temp;
      firstNode = temp; // temp is new first node
      
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
      firstNode->setPrev(NULL);
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
      index = previous->getNext();
      index->setPrev(previous);
      if (index->getNext() == NULL)
         lastNode = index;
   } 
   numItems--;   
}
 
/**********************************************************************
 * Searches for first instance of item in list and returns index
 **********************************************************************/
int List::lookup(long item) const
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
long List::getData(int pos) const
{
   Node* index = firstNode;
   
   if (pos > numItems)
      pos = numItems;
   // go to correct location
   for (int i = 0; i < pos; i++)
      index = index->getNext();
   return index->getData ();
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

/**********************************************************************
 * Displays the list starting at first item until it gets to back
 **********************************************************************/
void List::display(void) const
{
   Node* current = firstNode;
   while (current != NULL)
   {
      cout << current->getData();
      current = current->getNext();
   }
   cout << endl;
}

/**********************************************************************
 * Displays the list starting at last item until it gets to front
 **********************************************************************/
void List::displayBack(void) const
{
   Node* current = lastNode;
   while (current != NULL)
   {
      cout << current->getData();
      current = current->getPrev();
   }
   cout << endl;
}

/*********************************************************************
 * Adds two list together keeping numbers in node of nine digits to
 * overcome limits of data with types - overloaded addition will make
 * large numbers easier to work with
 *********************************************************************/
const List operator + (List &leftSide, List &rightSide)
{
   long first = 0;
   long second = 0;
   long carry = 0;
   long sum = 0;

   Node* left = leftSide.getLastNode();
   Node* right = rightSide.getLastNode();
   List temp;
   
   while (left != NULL || right != NULL)
   {
      if (left != NULL)
      {
         first = left->getData();
         left = left->getPrev();
      }
      else
         first = 0;
      if (right != NULL)
      {
         second = right->getData();
         right = right->getPrev();
      }
      else
         second = 0;
      sum = first + second + carry;

      carry = sum / 10;
      sum %= 10;
     
      temp.insert(sum, 0);
      if (carry > 1) // make sure the carry is handled properly
      {
         temp.insert(carry, 0);
         carry = 0;
      }
   }
   if (carry > 0)
      temp.insert(carry, 0);
      
   return temp;
}

/**********************************************************************
 * Takes a number from the command line and calculates the correct
 * number in that sequence to display
 ***********************************************************************/
int main(int argc, char** argv)
{
   if (argc < 2)
      cout << "ERROR: must specify an input number\n";
   else
   {
      List a;
      List b;
      List* fib = &b;
      
      a.insert(0,0);
      b.insert(1,0);
      
      int item = atoi(argv[1]);
      if (item % 2 == 0)
      {
         item++; // if item is odd, go up one to even
         fib = &a; // if even, a will have list
      }
      item /= 2;      
      for (int i = 0; i < item; i++)
      {
         a = a + b;
         b = b + a;
      }
      fib->display();
      cout << endl;
   }
   return 0;
}
