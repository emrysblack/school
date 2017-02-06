/***********************************************************************
* Program:
*    Homework 14, BST Class 
*    Brother Twitchell, CS235
* Author:
*    Brady Field
* Summary: 
*    Contains function definitions for the Binary Tree Class
************************************************************************/

#include <iostream>
#include "tree.h"
#include "bst.h"
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
   BTree* current = this;
   if (current->left != NULL) current->left->~BTree();
   if (current->right != NULL) current->right->~BTree();
   delete current;
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

/**********************************************************************
 * constructor
 **********************************************************************/
BST::BST()
{
   root = NULL; // no items in tree
}

/**********************************************************************
 * returns true if empty
 **********************************************************************/
int BST::empty(void)
{
   return root == NULL;
}

/**********************************************************************
 * returns pointer to node of item in tree
 **********************************************************************/
BTree* BST::search(int item)
{
   BTree* temp = root; // used to traverse tree
   if (temp == NULL) // is first node inserted
      cout << "Empty List\n";
   else
   {
      int found = 0; // 0 - not found, 1 - found, -1 - not present
      while (found == 0)
      {
         if (temp->getData() == item) // in right place
            found = 1;
         else // keep searching
         {
            if (temp->getData() > item)
            {
               if (temp->getLeftChild() != NULL)
                  temp = temp->getLeftChild();
               else
                  found = -1;
            }
            else
               if (temp->getRightChild() != NULL)
                  temp = temp->getRightChild();
               else
                  found = -1;
         }
      }
      if (found == 1) // return pointer to item
         return temp;
      else
         return NULL; // item was not in list
   }
}

/**********************************************************************
 * inserts item into the tree
 **********************************************************************/
void BST::insert(int item)
{
   BTree* temp = root; // used to traverse tree
   if (temp == NULL) // is first node inserted
   {
      temp = new BTree(item);
      root = temp;
   }
   else
   {
      bool found = false;
      while (!found)
      {
         if (temp->getData() > item) // if it goes to left sub-tree
         {
            if (temp->getLeftChild() == NULL)
            {
               temp->insertLeft(item);
               found = true;
            }
            else
               temp = temp->getLeftChild();
         }
         else // goes in right sub-tree
         {
            if (temp->getRightChild() == NULL)
            {
               temp->insertRight(item);
               found = true;
            }
            else
               temp = temp->getRightChild();
         }
      } 
   }
}

/**********************************************************************
 * removes specified value from tree or displays error if item does not
 * exist
 **********************************************************************/
void BST::remove(int item)
{
   BTree* temp = search(item);
   BTree* heir; 
   if (temp == NULL)
      cout << "Item " << item << " is not found, cannot delete it!\n";
   else
   {
      heir = temp->getRightChild(); // default set to right child
      if (temp->getLeftChild() != NULL and temp->getRightChild() != NULL)
      {
         while (heir->getLeftChild() != NULL) // move to inheritance leaf
         {
            heir = heir->getLeftChild();
         }
         temp->setData(heir->getData());
         temp = heir; // node to be removed
         heir = temp->getRightChild(); // reset heir
      }
      if (temp->getLeftChild() == NULL or temp->getRightChild() == NULL)
      {         
         if (temp->getLeftChild() != NULL)
            heir = temp->getLeftChild(); // change to left if has valid child
         if (temp->getParent()->getRightChild() == temp) // reset links
            temp->getParent()->setRight(heir);
         else
            temp->getParent()->setLeft(heir);
      }
   }
}

/**********************************************************************
 * calls infix display
 **********************************************************************/
void BST::BSTInfix(void)
{
   root->infix();
}
