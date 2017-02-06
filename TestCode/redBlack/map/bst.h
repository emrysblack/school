// implementation of red-black tree

#ifndef BST_H
#define BST_H

#include <iostream>

// all adapter additions for testbed compatibility are marked  
#define TESTBED

#ifdef TESTBED
template <class T>
class BSTIterator; // for testbed
#endif

/***********************************************
 * Implements a Binary Search Tree
 * Uses nested classes to work like STL version
 ***********************************************/
template <class T>
class BST
{ 
  public:
   class Iterator; // inner iterator
   BST() : root(NULL), num(0) { }
   BST(T data) throw (char *)
   {
      root = NULL;
      num = 0;
      
      try
      {
         root = new BNode(data);
         num = 1;
      }
      catch(std::bad_alloc)
      {
         throw "ERROR: Unable to allocate a node";
      }
   }
   BST(const BST & rhs)
   {
      root = NULL;
      *this = rhs;
   }
   BST & operator = (const BST & rhs)
   {
      clear();
      num = rhs.num;
      if (num > 0)
      {
         root = rhs.root->copy();
      }
      return *this;
   }
   ~BST(){ clear(); }
   bool empty() { return root == NULL; }
   int size() { return num; }
   void clear()
   {
      if (root)
      {
         root->prune();
         delete root;
         root = NULL;
         num = 0;
      }
   }
   void insert(T data);
   void remove(Iterator it);
   #ifdef TESTBED
   // for testbed
   void remove(BSTIterator<T> it) { remove(it.getIterator()); }
   #endif
   
   Iterator find(T item)
   {
      BNode * search = root;
      while (search && search->getData() != item)
      {
         if(item < search->getData())
         {
            search = search->getLeftChild();
         }
         else
         {
            search = search->getRightChild();
         }
      }
      return search;
   }
   Iterator begin()
   {
      BNode * temp = root;
      if (temp)
      {
         while(temp->getLeftChild())
         {
            temp = temp->getLeftChild();
         }
      }
      return temp;
   }
   Iterator end() { return NULL; }
   Iterator rbegin()
   {
      BNode * temp = root;
      if (temp)
      {
         while(temp->getRightChild())
         {
            temp = temp->getRightChild();
         }
      }
      return temp;
   }
   Iterator rend() { return NULL;}

   // for testing tree structure
   void infix(void) { root->infix(); }           // do infix traversal
   void prefix(void) { root->prefix(); }         // do prefix traversal
   void postfix(void) { root->postfix(); }       // do postfix traversal
   void level(void) { root->level(); }           // do level order traversal

   protected:
   class BNode;
   BNode * root;
   int num;
   BNode * getNode(Iterator it) { it.getNode(); }
};

/***********************************************
 * Iterates through the nodes of a BST
 * public nested class so can be used like STL
 ***********************************************/
template <class T>
class BST<T>::Iterator
{
   //friend class BST;
  protected:
   BNode * p;
   BNode * getNode() { return p; }
   
  public:
  Iterator():p(NULL) {}
  Iterator(BNode * point):p(point) {}
   virtual const T & operator * ()
   {
      return p->getData();
   }
   bool operator == (Iterator rhs)
   {
      return p == rhs.p;
   }
   bool operator != (Iterator rhs)
   {
      return !(*this == rhs);
   }
   Iterator & operator++(); // prefix
   Iterator operator++(int); // postfix
   Iterator & operator--(); // prefix
   Iterator operator--(int); // postfix
   friend BNode * BST<T>::getNode(Iterator it); // needs the getNode function
};

/***********************************************
 * Nodes of the BST
 * Private nested class so only BST can use it
 ***********************************************/
template <class T>
class BST<T>::BNode
{
  private:
   T data;            // --- data stored in node of tree
   BNode* left;       // --- pointer to left subtree
   BNode* right;      // --- pointer to right subtree
   BNode* parent;     // --- pointer to the parent node;
   public:
  BNode(T item, BNode * p = NULL, BNode * l = NULL, BNode * r = NULL)
     : data(item), parent(p), left(l), right(r) { }
   T & getData(void) { return data;}
   void setData(T item) { data = item; }

   void prune();
   BNode * copy(void);
   void insertLeft(T item)     // insert node to left
   {
      BNode * temp;
      temp = new BNode(item);
      left = temp;
      temp->parent = this;
   }

   void insertRight(T item)    // insert node to right
   {
      BNode * temp;
      temp = new BNode(item);
      right = temp;
      temp->parent = this;
   }

   BNode* getLeftChild(void) { return left; }  // return the left child
   BNode* getRightChild(void) { return right; }    // return the right child
   BNode* getParent(void) { return parent; }        // return parent
   void setLeft(BNode* tree)
   {
      left = tree;
      if (left != NULL) left->setParent(this);
   }
   void setRight(BNode* tree)
   {
      right = tree;
      if (right != NULL) right->setParent(this);
   }
   void setParent(BNode* tree)
   {
      parent = tree;
   }
   void infix(void);              // do infix traversal
   void prefix(void);             // do prefix traversal
   void postfix(void);            // do postfix traversal
   void level(void);              // do level order traversal // flawed? check 0 case and 1 case, and debug...
};

/***********************************************
 * BST definitions
 ***********************************************/

/**********************************************************************
 * uses insert left and right to create nodes and balances
 **********************************************************************/
template <class T>
void BST<T>::insert(T item)
{
   // insert left or right depending on value
   if (!root) // root node
   {
      root = new BNode(item);
      num = 1;
      return;
   }
   
   BNode * temp = root;
   bool found = false;
   while(!found)
   {
      if (item <= temp->getData())
      {
         if(temp->getLeftChild())
         {
            temp = temp->getLeftChild();
         }
         else
         {
            temp->insertLeft(item);
            num++;
            found = true;
         }
      }
      else
      {
         if(temp->getRightChild())
         {
            temp = temp->getRightChild();
         }
         else
         {
            temp->insertRight(item);
            num++;
            found = true;
         }
      }
   }
}

/**********************************************************************
 * adapted from data structures book without reassignment
 **********************************************************************/
template <class T>
void BST<T>::remove(Iterator it)
{
   //  only work for valid data
   if (it != end())
   {
      BNode * orig = getNode(it);
      BNode * heir = getNode(++it);
      if (orig->getLeftChild() && orig->getRightChild()) // two children
      {
         heir->setLeft(orig->getLeftChild());
         // do inheritance
         if(heir->getParent() != orig)
         {
            heir->getParent()->setLeft(heir->getRightChild());
            heir->setRight(orig->getRightChild());
         }
      }
      else // orig missing at least one child
      {
         heir = orig->getLeftChild();
         if (!heir)
         {
            heir = orig->getRightChild();
         }
      }
      // re-link parent
      if (!orig->getParent()) // root
      {
         root = heir;
         heir->setParent(NULL);
      }
      else if (orig->getParent()->getLeftChild() == orig)
      {
         orig->getParent()->setLeft(heir);
      }
      else
      {
         orig->getParent()->setRight(heir);
      }
      delete orig;
      orig = NULL;
      num--;
   }
}

/***********************************************
 * Iterator Definitions
 ***********************************************/

template <class T>
typename BST<T>::Iterator & BST<T>::Iterator::operator++() // prefix
{
   BNode * temp = p;

   // root node or has right child
   if(!temp->getParent() || temp->getRightChild())
   {
      // one right, all the way left
      temp = temp->getRightChild();
      if (temp)
      {
         while (temp->getLeftChild())
         {
            temp = temp->getLeftChild();
         }
      }
      p = temp;
      return *this;
   }
   if (temp->getParent()->getLeftChild() == temp) // left child
   {
      p = temp->getParent();
      return *this;
   }
   while (temp->getParent() // root test
          && temp->getParent()->getRightChild() == temp) // right child
   {
      temp = temp->getParent();
   }
   p = temp->getParent();
   return *this;
}

template <class T>
typename BST<T>::Iterator BST<T>::Iterator::operator++(int) // postfix
{
   BNode * temp = p;
   Iterator original = temp;
   
   // root node or has right child
   if(!temp->getParent() || temp->getRightChild())
   {
      // one right, all the way left
      temp = temp->getRightChild();
      if (temp)
      {
         while (temp->getLeftChild())
         {
            temp = temp->getLeftChild();
         }
      }
      p = temp;
      return original;
   }
   if (temp->getParent()->getLeftChild() == temp) // left child
   {
      p = temp->getParent();
      return original;
   }
   while (temp->getParent() // root test
          && temp->getParent()->getRightChild() == temp) // right child
   {
      temp = temp->getParent();
   }
   p = temp->getParent();
   return original;
}

template <class T>
typename BST<T>::Iterator & BST<T>::Iterator::operator--() // prefix
{
   BNode * temp = p;

   // root node or has right child
   if(!temp->getParent() || temp->getLeftChild())
   {
      // one right, all the way left
      temp = temp->getLeftChild();
      if (temp)
      {
         while (temp->getRightChild())
         {
            temp = temp->getRightChild();
         }
      }
      p = temp;
      return *this;
   }
   if (temp->getParent()->getRightChild() == temp) // right child
   {
      p = temp->getParent();
      return *this;
   }
   while (temp->getParent() // root test
          && temp->getParent()->getLeftChild() == temp) // left child
   {
      temp = temp->getParent();
   }
   p = temp->getParent();
   return *this;
}

template <class T>
typename BST<T>::Iterator BST<T>::Iterator::operator--(int) // postfix
{
   BNode * temp = p;
   Iterator original = temp;

   // root node or has right child
   if(!temp->getParent() || temp->getLeftChild())
   {
      // one right, all the way left
      temp = temp->getLeftChild();
      if (temp)
      {
         while (temp->getRightChild())
         {
            temp = temp->getRightChild();
         }
      }
      p = temp;
      return original;
   }
   if (temp->getParent()->getRightChild() == temp) // right child
   {
      p = temp->getParent();
      return original;
   }
   while (temp->getParent() // root test
          && temp->getParent()->getLeftChild() == temp) // left child
   {
      temp = temp->getParent();
   }
   p = temp->getParent();
   return original;
}

/***********************************************
 * Node Definitions
 ***********************************************/

/**********************************************************************
 * prune uses postfix algorithm to delete nodes
 **********************************************************************/
template <class T>
void BST<T>::BNode::prune()
{
   // infix through the tree to destroy from the bottom up
   if (left != NULL)
   {
      left->prune();
   }
      
   if (right != NULL)
   {
      right->prune();
   }

   // return the memory from the bottom up
   if (left != NULL)
   {
      delete left;
      left = NULL;
   }
   if (right != NULL)
   {
      delete right;
      right = NULL;
   }
}

template <class T>
typename BST<T>::BNode * BST<T>::BNode::copy(void)
{
   // prefix, data, go left, go right...
   BNode * temp = new BNode(data);
   if (left != NULL) temp->setLeft(left->copy());
   if (right != NULL) temp->setRight(right->copy());
   return temp;
}

/**********************************************************************
 * do infix traversal
 **********************************************************************/
template <class T>
void BST<T>::BNode::infix(void)
{
   if (left != NULL) left->infix();
   std::cout << data << " ";
   if (right != NULL) right->infix();
}

/**********************************************************************
 * do prefix traversal
 **********************************************************************/
template <class T>
void BST<T>::BNode::prefix(void)
{
   std::cout << data << " ";
   if (left != NULL) left->prefix();
   if (right != NULL) right->prefix();
}

/**********************************************************************
 * do postfix traversal
 **********************************************************************/
template <class T>
void BST<T>::BNode::postfix(void)
{
   if (left != NULL) left->postfix();
   if (right != NULL) right->postfix();
   std::cout << data << " ";
}

/**********************************************************************
 * do level order traversal
 **********************************************************************/
template <class T>
void BST<T>::BNode::level(void)
{
   const int MAX = 50;
   BNode *queue[MAX];
   BNode *temp;
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
         std::cout.width(4);
         std::cout << temp->data << " ";
         if (temp->parent == NULL)
            std::cout << " Parent = NULL! " << std::endl;
         else
            std::cout << " Parent = " << temp->parent->data << "   "
                      << std::endl;
         // end Visit
         queue[back] = temp->left;
         back = (back + 1) % MAX;
         queue[back] = temp->right;
         back = (back + 1) % MAX;
      }
   }
}

#ifdef TESTBED
// wrapper class for BSTIterator that uses the proper iterator
// so that testbed will work...
// this is my adapter pattern!!! :)
template <class T>
class BSTIterator
{
  private:
   typename BST<T>::Iterator it;
  public:
  BSTIterator(typename BST<T>::Iterator rhs = NULL) : it(rhs) {}
   ~BSTIterator() {}
   const T operator * ()
   {
      return *it;
   }
   bool operator == (typename BST<T>::Iterator rhs)
   {
      return it == rhs;
   }
   bool operator != (typename BST<T>::Iterator rhs)
   {
      return !(it == rhs);
   }
   BSTIterator & operator++() { ++it; return *this; }
   BSTIterator operator++(int) { BSTIterator copy(it);it++; return copy; }
   BSTIterator & operator--() { --it; return *this; }
   BSTIterator operator--(int) { BSTIterator copy(it); it--; return copy; }
   typename BST<T>::Iterator getIterator() { return it; }
};
#endif

#endif
