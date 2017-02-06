/***********************************************************************
 * Program:
 *    Exploration 4, Ripeness
 *    Brother Neff, CS238
 *
 * Author:
 *    Your Name Here
 *
 * Summary:
 *    Tree Structure time-for-space traversal tradeoff and
 *    Tournament Sort
 *
 * Note:
 *    This code is mostly uncommented --- this is deliberate.
 *
 ***********************************************************************/

#include <cmath>
#include <climits> // for INT_MIN
#include <iostream>
#include "words.h"
using namespace std;

class Node
{
private:
   int mValue;
   Node* mLeft;
   Node* mRight;
public:
   Node(int inValue) { mValue = inValue; mLeft = NULL; mRight = NULL; }
   int getValue() { return mValue; }
   void setValue(int pValue) { mValue = pValue; } 
   Node* getLeft() { return mLeft; }
   void setLeft(Node* inLeft) { mLeft = inLeft; }
   Node* getRight() { return mRight; }
   void setRight(Node* inRight) { mRight = inRight; }
};

ostream& operator<<(ostream& os, Node* node)
{
   if (node != NULL)
   {
      os << node->getValue() << " ";
      os << node->getLeft();
      os << node->getRight();
   }
   return os;
}

class Tree
{
private:
   static int cNextNodeNumber;
   int mHeight;
   Node* mRoot;
   Node* buildTree(int height)
   {
      Node* root = new Node(cNextNodeNumber++);
      if (height > 0)
      {
         root->setLeft(buildTree(height - 1));
         root->setRight(buildTree(height - 1));
      }
      return root;
   }

public:
   Tree(int height)
   {
      mHeight = height;
      mRoot = buildTree(height);
   }

   Node* getRoot() { return mRoot; }

   void traversePreorder()
   {
      traverse(mRoot, -1);
   }
   void traverseInorder()
   {
      traverse(mRoot, 0);
   }
   void traversePostorder()
   {
      traverse(mRoot, 1);
   }

   void traverse(Node* node, int tType)
   {
      if (node == NULL) return;
      if (tType == -1)
      {
         visit(node);
      }
      traverse(node->getLeft(), tType);
      if (tType == 0)
      {
         visit(node);
      }
      traverse(node->getRight(), tType);
      if (tType == 1)
      {
         visit(node);
      }
   }

   void visit(Node* node)
   {
      cout << node->getValue() << " ";
   }

   void traverseLevel1()
   {
      const int MAX = 128;
      Node* queue[MAX];
      Node* temp;
      int front = 0;
      int back = 0;

      queue[back++] = mRoot;

      while (front != back)
      {
         temp = queue[front];
         front = (front + 1) % MAX;
         if (temp != NULL)
         {
            cout << temp->getValue() << " ";
            queue[back] = temp->getLeft();
            back = (back + 1) % MAX;
            queue[back] = temp->getRight();
            back = (back + 1) % MAX;
         }
      }
   }

   void traverseLevel2()
   {
      for (int level = 0; level <= mHeight; level++)
      {
         int maxWhich = (int) pow((double) 2, (double) level);
         for (int which = 1; which <= maxWhich; which++)
         {
            visit(findNode(mRoot, level, which));
         }
      }
   }

   Node* findNode(Node* start, int level, int which)
   {
      int maxWhich = (int) pow((double) 2, (double) level);
      int halfway = maxWhich / 2;
      if (level == 0)
      {
         return start;
      }
      else if (which <= halfway)
      {
         return findNode(start->getLeft(), level - 1, which);
      }
      else
      {
         return findNode(start->getRight(), level - 1, which - halfway);
      }
   }
   
   /************************************************************************
    * Fills a tree so the data is all contained in the leaf nodes, then
    * does an initial tournament sort to move the largest value to the top.
    ************************************************************************/
   void makeLikeATreeAndLeave(int array[], int size, Node * current)
   {
      static int pos = 0;
      if(current->getLeft()) // all lefts will also have rights
      {
         makeLikeATreeAndLeave(array, size, current->getLeft());   
         makeLikeATreeAndLeave(array, size, current->getRight());
         // compare
         int left = current->getLeft()->getValue();
         int right = current->getRight()->getValue();
         int max = (left > right ? left : right);
         current->setValue(max); // set up tree for initial sort
      }
      else // leaf node
      {
         if (pos < size)
         {
            current->setValue(array[pos++]);
         }
         else
         {
            // dummy node for arrays not in powers of 2
            current->setValue(INT_MIN);
         }
      }
   }
    /************************************************************************
    * Sets the old winning leaf node to negative infinity, recomputes only
    * that branch, and then returns the winning node value
    ************************************************************************/
   int downWithTheKing(Node * current, int king)
   {
      // got to winning leaf
      if(current->getLeft()) // going to leaves
      {
         if(current->getLeft()->getValue() == king) // only go down winning path
         {
            downWithTheKing(current->getLeft(), king);
         }
         else
         {
            downWithTheKing(current->getRight(), king);
         }
         // recalculate the branch
         // compare
         int left = current->getLeft()->getValue();
         int right = current->getRight()->getValue();
         int max = (left > right ? left : right);
         current->setValue(max);
         return max;
      }
      else if(current->getValue() == king) // we found it!
      {
         current->setValue(INT_MIN);
      }
      else // should always arrive at value as soon as we hit a leaf
      {
         cerr << "ERROR! Should never see this!\n";
      }
  
   }
};

ostream& operator<<(ostream& os, Tree& tree)
{
   os << tree.getRoot();
   return os;
}

int Tree::cNextNodeNumber = 0;

/*************************************************************************
 * treeTraversal
 *
 * Makes a tree of specified height, then outputs a printed representation
 * of the tree followed by output from calling the traversal functions:
 * PRE-order, IN-order, POST-order, LEVEL-order and (versions 1 and 2).
 *************************************************************************/
void treeTraversal(int height)
{
   Tree tree(height);
   cout << tree << endl;
   tree.traversePreorder();
   cout << endl;
   tree.traverseInorder();
   cout << endl;
   tree.traversePostorder();
   cout << endl;
   tree.traverseLevel1();
   cout << endl;
   tree.traverseLevel2();
   cout << endl;
}

/*************************************************************************
 * Tournament Sort implemented here.
 *
 * TODO: if you think it will help, add to (but don't subtract from) the
 * above-defined classes, and/or make other helper functions.
 *************************************************************************/
void tournamentSort(int array[], int size)
{
   // number of levels needed for a complete tree with the given size
   // note, ceiling is used to compensate for trees without powers of 2
   int levels = ceil(log2(size));
   Tree tree(levels);
   
   // prepare the tree and get the first sorted value
   tree.makeLikeATreeAndLeave(array, size, tree.getRoot());
   array[0] = tree.getRoot()->getValue();
   
   // run through the rest of the tree
   for (int i = 1; i < size; i++)
   {
      // get the winning leaf and then erase
      array[i] = tree.downWithTheKing(tree.getRoot(), array[i-1]);
   }
}

/*************************************************************************
 * learned
 *
 * Tells interested parties what you learned.
 *
 * Use one or more calls to out(...), or else use the whatIlearned
 * script and do the following:
 *
 *   Words words = {
 *   #include "whatIlearned.inc"
 *   nl};
 *   cout << words;
 *************************************************************************/
void learned()
{
    Words words = {
    #include "whatIlearned.inc"
    nl};
    cout << words;
}

/*************************************************************************
 * usage
 *
 * Tells the user how to use the program.
 *************************************************************************/
void usage(const char * programName)
{
   cout << "usage: "<< programName << " [test]\n";
   cout << "valid tests: treet, tsort\n";
   cout << "e.g. " << programName << " tsort\n";
}
