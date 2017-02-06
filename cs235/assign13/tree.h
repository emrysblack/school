/*************************************************************
 *
 *  NAME: Brother Cameron
 *  Modified by Brother Ercanbrack 3 Aug 2006
 *  FILE: tree.h
 *
 *  PURPOSE: This file defines the Binary Tree Class
 *
 ************************************************************/
#ifndef _TREE_H
#define _TREE_H
using namespace std;
#include <iostream>

class BTree
{
   private:
      int data;          // --- data stored in node of tree
      BTree* left;       // --- pointer to left subtree
      BTree* right;      // --- pointer to right subtree
      BTree* parent;     // --- pointer to the parent node;

   public:
      BTree(int data = 0);  
      ~BTree(void);
      void insertLeft(int item);     // creates a new node and inserts node to left
      void insertRight(int item);    // creates a new node and inserts node to right
      BTree* getLeftChild(void);     // return the ptr to the left child
      BTree* getRightChild(void);    // return the ptr to the right child
      BTree* getParent(void);        // return parent
      int getData(void);
      void setData(int item);
      void setLeft(BTree* tree);     
      void setRight(BTree* tree);
      void infix(void);              // do infix traversal
      void prefix(void);             // do prefix traversal
      void postfix(void);            // do postfix traversal
      void level(void);              // do level order traversal
};
#endif
