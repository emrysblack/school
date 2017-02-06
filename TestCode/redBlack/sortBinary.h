/***********************************************************************
 * Module:
 *    Week 09, Sort Binary
 *    Brother Helfrich, CS 235
 * Author:
 *    Br. Helfrich
 * Summary:
 *    This program will implement the Binary Tree Sort
 ************************************************************************/

#ifndef SORT_BINARY_H
#define SORT_BINARY_H

#include "bst.h"

/*****************************************************
 * SORT BINARY
 * Perform the binary tree sort
 ****************************************************/
template <class T>
void sortBinary(T array[], int num)
{
   BST<T> sortTree;

   // insert all values
   int i = 0;
   for (i = 0; i < num; i++)
   {
      sortTree.insert(array[i]);
   }

   // grab sorted using iterator
   i = 0;
   for (BSTIterator<T> it = sortTree.begin(); it != sortTree.end(); i++, it++)
   {
      array[i] = *it;
   }
}


#endif // SORT_BINARY_H
