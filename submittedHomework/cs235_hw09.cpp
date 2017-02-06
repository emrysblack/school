/***********************************************************************
* Program:
*    Homework 09, Node Class 
*    Brother Twitchell, CS235
* Author:
*    Brady Field
* Summary: 
*    Reads a list of integers from a file specified from the command line,
*    keeps track of them in numerical order using a linked list and displays
*    the output in an ordered format
************************************************************************/

#include <iostream>
#include <fstream>
using namespace std;

/*******************************************************************
 *
 *     FILE: node.h
 *
 *  PURPOSE: Contains the class definition of a Node
 *******************************************************************/
class Node
{
   private:
      int data;                 // --- data in each node
      Node* next;               // --- pointer to next node

   public:
      Node();                   // --- Creates empty node
      Node* getNext();          // --- returns next pointer of a node
      int getData();            // --- returns data of a node
      void setData(int item);   // --- stores item in data member of node
      void setNext(Node* node); // --- sets next to point to node
};

/**********************************************************************
 * Default constructor
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
 * Reads in a list of integers from a file, places them in a linked
 * list via insertion sort, and displays the list in an ordered format
 ***********************************************************************/
int main(int argc, char** argv)
{
   if (argc < 2)
      cout << "ERROR: no file name specified\n";
   else
   {
      ifstream fin;
      fin.open(argv[1]);
      if (fin.fail())
         cout << "ERROR: could not open file: " << argv[1] << endl;
      else
      {
         // read in the data
         Node a; // Head node         
         Node* pointer = &a; // pointer to traverse list
         Node* node; // pointer to operate on data
         int input;
         
         a.setData(-1); // is simply the head, contains no relevant data
         
         while (!fin.eof())
         {
            fin >> input;
            if (fin.good())
            {
               node = new Node; // make new node
               node->setData(input);
               
               // insertion sort
               pointer = &a; // start at beginning of list
               bool done = false;
               while (!done)
               {
                  if ((pointer->getNext() == NULL) or // place in spot or end 
                      (input < pointer->getNext()->getData()))
                  {
                     node->setNext(pointer->getNext());
                     pointer->setNext(node);
                     done = true;
                  }
                  else
                     pointer = pointer->getNext(); // move to next item in list
               }
            }
         }
         fin.close();
         
         // display
         pointer = a.getNext();
         while (pointer != NULL)
         {
            for (int i = 0; i < 20 and pointer != NULL; i++) // output row
            {
               cout << " "; // space before every item
               if (pointer->getData() < 10)
                  cout << " "; // additional space before small numbers
               cout << pointer->getData();
               pointer = pointer->getNext();
            }
            cout << endl; // end row on twenty items
         }
         
         // return allocated memory to system
         node = a.getNext(); // point to first allocated item with pointers
         pointer = node;
         while (node != NULL)
         {
            pointer = pointer->getNext(); // gets next item to be deleted
            delete node; // delete current node
            node = pointer; // move to next item in list
         }
      }
   }
   return 0;
}
