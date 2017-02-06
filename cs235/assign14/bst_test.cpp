/********************************************************************************
*
*  File: bst_test.cpp
*
*  Author: Brother Cameron, 10/23/2001
*
*  Purpose: This program tests the member functions from the BST class.
*           The program reads 25 numbers from a file and inserts them into the BST.
*           It then prints out the tree in infix order.  The program then deletes
*           selected numbers and redisplays the tree in infix order after each delete.
*
*  Limitations: This program does not test the BST Search function.  It is
*               assumed that the remove function uses the search function
*               to find the node to be deleted.
*
*****************************************************************************/

using namespace std;
#include "bst.h"
#include "tree.h"
#include <iostream>
#include <fstream>

main()
{
   BST b;          // --- a binary search tree object
   int number;
   const int NUM = 25;
   int i;
   ifstream infile("assign14.in");

   // --- Create a BST with NUM random numbers between HIGH and LOW
   for (i = 0; i < NUM; i++)
   {
      infile >> number;
      b.insert(number);
   }
   
   // --- Print out number in infix order
   b.BSTInfix();
   cout << endl;

   // --- Delete a node with one children
   b.remove(3);
   b.BSTInfix();
   cout << endl;

   // --- Delete a node with no children
   b.remove(17);
   b.BSTInfix();
   cout << endl;

   // --- Delete a node with two children
   b.remove(58);
   b.BSTInfix();
   cout << endl;

   // --- Try to Delete a node that is not found
   b.remove(58);
   b.BSTInfix();
   cout << endl;

}
