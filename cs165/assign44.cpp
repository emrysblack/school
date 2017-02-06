/***********************************************************************
* Program:
*    Assignment 44, Linked Lists
*    Brother Boyer, CS165
* Author:
*    Brady Field
* Summary: 
*    This program is designed to demonstrate the basic operations
*    of linked lists using a simple Node structure.  We will then
*    morph this into a type-independent class during class time.
*
*    Estimated:  1.0 hrs   
*    Actual:     0.5 hrs
*      convienience required constructors. Changed struct to class.
************************************************************************/

#include <iostream>
using namespace std;

/*********************************************
 * NODE: one element of a linked list
 *********************************************/
class Node
{
public:
   Node (int value, Node *pNext)
         : value(value), pNext(pNext){}
   int value;
   Node *pNext;
};

/********************************************
 * ADD: Add a new value to the list
 *   INPUT:  value:   The value of the node
 *           next:    What the node will point to next
 *   OUTPUT: <return> Return a pointer to the newly created node
 *******************************************/
Node *add(int value, Node *pNext)
{
   return new Node(value, pNext);
}

/*********************************************
 * REMOVE: Remove an item from the list.
 *         Before:     pBefore-><this>->pAfter
 *         After:      pBefore->pAfter
 *   INPUT: pThis:   The node to be removed
 *   OUTPUT <return> pointer to <this>->next so pBefore->next can use it
 *********************************************/
Node *remove(Node *pNode)
{
   Node *pThis = pNode;
   delete pNode;
   return pThis->pNext;
}

/*********************************************
 * DISPLAY: Display the contents of a linked list.
 *          In this case, each note will be displayed on
 *          its own line with a tab before it: "\t" << value << endl
 *  INPUT: pHead:  Pointer to the first item in the list
 *********************************************/
void display(Node *pHead)
{
   Node *pNext = pHead;
   while (pNext != NULL)
   {
      cout << "\t" << pNext->value << endl;
      pNext = pNext->pNext;
   }
}

/**********************************************************************
 * MAIN: This driver program will exercise our Node data type
 ***********************************************************************/
int main()
{
   // build a simple linked-list
   Node *pHead = add(7, NULL);           // first item is 7 with nothing after
   pHead = add(21, pHead);               // put 21 at the beginning
   pHead->pNext = add(14, pHead->pNext); // put 14 at the 2nd item in the list
   pHead = add(28, pHead);               // put 28 at the beginning

   // display the contents
   cout << "First list:\n";
   display(pHead);

   // remove 21. {28, 21, 14, 7} --> {28, 14, 7}   
   pHead->pNext = remove(pHead->pNext);
   // remove 7.  {28, 14, 7} --> {28, 14}
   pHead->pNext->pNext = remove(pHead->pNext->pNext); 

   // display the contents
   cout << "Reduced list:\n";
   display(pHead);

   return 0;
}
