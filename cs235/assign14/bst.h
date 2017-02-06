/*************************************************************************
 *
 *  File: bst.h
 *
 *  Author: Brother Cameron, 10/23/2001
 *
 *  Purpose: Defines the Binary Search Tree class
 *
 **************************************************************************/
#ifndef _BST_H
#define _BST_H

#include "tree.h"

class BST
{
   private:
      BTree* root;
   
   public:
      BST();
      int empty(void);
      BTree* search(int item);
      void insert(int item);
      void remove(int item);
      void BSTInfix(void);
};
#endif
