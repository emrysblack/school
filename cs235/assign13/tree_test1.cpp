/*************************************************************
 *
 *   NAME: Brother Cameron
 *
 *   FILE: test1.cpp
 *
 *   PURPOSE: This program tests the following member functions:
 *            constructor, destructor, insertLeft, insertRight
 *            getLeftChild, getRightChild, getData, level, infix, prefix,
 *            and postfix.  The program does this
 *            by doing the following steps:
 *              1. Create a complete binary tree
 *              2. Do all 4 traversals of the tree
 *
 *************************************************************/
using namespace std;
#include <iostream>
#include <math.h>
#include "tree.h"

BTree *find_node(BTree *temp, int node);

main()
{
   BTree *queue[20];      // --- used to implement a queue
   int front = 0;         // --- index to front of queue
   int back = 0;          // --- index to back of queue
   BTree *root;           // --- pointer to root of heap
   BTree *temp;           // --- pointer used to traverse tree
   int node;              // --- current node number
   int parent_node;       // --- node number of parent node
   int mask = 1;          // --- used in finding lowest-level right most node
   int i;      
   int array[] = {23, 15, 21, 29, 26, 27, 3, 10, 0, 2};

   // --- Create complete binary tree with elements from array
   root = new BTree(array[0]);
   queue[back++] = root;
   node = 1;
   while (node < 10)
   {
      temp = queue[front++];
      temp->insertLeft(array[node]);
      node++;
      if (node == 10)
         break;
      else
      {
         temp->insertRight(array[node]);
         node++;
         queue[back++] = temp->getLeftChild();
	 queue[back++] = temp->getRightChild();
      }
   }

   cout << "Tree in Infix-Order Traversal" << endl;
   root->infix();
   cout << endl;

   cout << "Tree in Prefix-Order Traversal" << endl;
   root->prefix();
   cout << endl;

   cout << "Tree in Postfix-Order Traversal" << endl;
   root->postfix();
   cout << endl;

   cout << "Tree in Level-Order Traversal" << endl;
   root->level();
   cout << endl;
   
}
