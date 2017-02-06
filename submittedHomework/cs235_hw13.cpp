/***********************************************************************
* Program:
*    Homework 13, BTree Class 
*    Brother Twitchell, CS235
* Author:
*    Brady Field
* Summary: 
*    Contains function definitions for the Binary Tree Class
************************************************************************/

#include <iostream>
#include "tree.h"
using namespace std;

/**********************************************************************
 * constructor
 **********************************************************************/
BTree::BTree(int item)
{
   parent =  NULL;
   right = NULL;
   left = NULL;
   data = item;
}

/**********************************************************************
 * destructor uses postfix algorithm to delete nodes
 **********************************************************************/
BTree::~BTree(void)
{
   if (left != NULL) left->~BTree();
   if (right != NULL) right->~BTree();
   delete this;
}

/**********************************************************************
 * creates a new node and inserts node to left
 **********************************************************************/
void BTree::insertLeft(int item)
{
   BTree* temp;
   temp = new BTree(item);
   left = temp;
   temp->parent = this;
}

/**********************************************************************
 * creates a new node and inserts node to right
 **********************************************************************/
void BTree::insertRight(int item)
{
   BTree* temp;
   temp = new BTree(item);
   right = temp;
   temp->parent = this;
}

/**********************************************************************
 * returns the pointer to the left child
 **********************************************************************/
BTree* BTree::getLeftChild(void)
{
   return left;
}

/**********************************************************************
 * returns the pointer to the right child
 **********************************************************************/
BTree* BTree::getRightChild(void)
{
   return right;
}

/**********************************************************************
 * returns pointer to the parent node
 **********************************************************************/
BTree* BTree::getParent(void)
{
   return parent;
}

/**********************************************************************
 * returns data of current node
 **********************************************************************/
int BTree::getData(void)
{
   return data;
}

/**********************************************************************
 * sets data of current node
 **********************************************************************/
void BTree::setData(int item)
{
   data = item;
}

/**********************************************************************
 * sets left child to node
 **********************************************************************/
void BTree::setLeft(BTree* tree)
{
   left = tree;
   if (left != NULL) left->parent = this;
}

/**********************************************************************
 * sets right child to node
 **********************************************************************/     
void BTree::setRight(BTree* tree)
{
   right = tree;
   if (right != NULL) right->parent = this;
}

/**********************************************************************
 * do infix traversal
 **********************************************************************/
void BTree::infix(void)
{
   if (left != NULL) left->infix();
   cout << data << " ";
   if (right != NULL) right->infix();
}

/**********************************************************************
 * do prefix traversal
 **********************************************************************/
void BTree::prefix(void)
{
   cout << data << " ";
   if (left != NULL) left->prefix();
   if (right != NULL) right->prefix();
}

/**********************************************************************
 * do postfix traversal
 **********************************************************************/
void BTree::postfix(void)
{
   if (left != NULL) left->postfix();
   if (right != NULL) right->postfix();
   cout << data << " ";
}

/**********************************************************************
 * do level order traversal
 **********************************************************************/
void BTree::level(void)
{
   const int MAX = 50;
   BTree *queue[MAX];
   BTree *temp;
   int front = 0;
   int back = 0;

   queue[back++ ] = this;

   while (front != back)
   {
      temp = queue[front];
      front = (front + 1) % MAX;
      if (temp != NULL)
      {
         // visit
         cout.width(4);
         cout << temp->data << " ";
         if (temp->parent == NULL)
            cout << " Parent = NULL! " << endl;
         else
            cout << " Parent = " << temp->parent->data << "   " << endl;
         // end Visit        
         queue[back] = temp->left;
         back = (back + 1) % MAX;
         queue[back] = temp->right;
         back = (back + 1) % MAX;

      }
   }
}
