// implementation of red-black tree

#ifndef RBTREE_H
#define RBTREE_H

#include <iostream>

// all adapter additions for testbed compatibility are marked  
//#define TESTBED

#ifdef TESTBED
template <class T>
class RBTreeIterator; // for testbed
#endif

/***********************************************
 * Implements a Red-Black Binary Search Tree
 * Uses nested classes to work like STL version
 ***********************************************/
template <class T>
class RBTree
{
  protected:
   class BNode;
   BNode * root;
   int num;
   
  public:
   class Iterator; // inner iterator
   RBTree() : root(NULL), num(0) { }
   RBTree(T data) throw (char *)
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
   RBTree(const RBTree & rhs)
   {
      root = NULL;
      *this = rhs;
   }
   RBTree & operator = (const RBTree & rhs)
   {
      clear();
      num = rhs.num;
      if (num > 0)
      {
         root = rhs.root->copy();
      }
      return *this;
   }
   ~RBTree(){ clear(); }
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
   void remove(RBTreeIterator<T> it) { remove(it.getIterator()); }
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
   Iterator rend() { return NULL; }
   void infix(void) { root->infix(); }           // do infix traversal
   void prefix(void) { root->prefix(); }         // do prefix traversal
   void postfix(void) { root->postfix(); }       // do postfix traversal
   void level(void) { root->level(); }           // do level order traversal
};

/***********************************************
 * Iterates through the nodes of a RBTree
 * public nested class so can be used like STL
 ***********************************************/
template <class T>
class RBTree<T>::Iterator
{
  private:
   BNode * p;
   BNode * getNode() { return p; }
  public:
  Iterator():p(NULL) {}
  Iterator(BNode * point):p(point) {}
   const T & operator * ()
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
   friend void RBTree<T>::remove(Iterator it); // needs the getNode function
};

/***********************************************
 * Nodes of the RBTree
 * Private nested class so only RBTree can use it
 ***********************************************/
template <class T>
class RBTree<T>::BNode
{
  private:
   T data;            // --- data stored in node of tree
   BNode* left;       // --- pointer to left subtree
   BNode* right;      // --- pointer to right subtree
   BNode* parent;     // --- pointer to the parent node;
   bool red;          // used for insert
   public:
   BNode(T item, BNode * p = NULL, BNode * l = NULL,BNode * r = NULL)
   {
      data = item;
      parent = p;
      left = l;
      right = r;
      red = true;
   }
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

   bool isRed() { return red; }
   void setRed(bool color) { red = color; }
   void insertBalance();
   void removeBalance(bool isLeftChild);
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
   void level(void);              // do level order traversal
};

/***********************************************
 * RBTree definitions
 ***********************************************/

/**********************************************************************
 * uses insert left and right to create nodes and balances
 **********************************************************************/
template <class T>
void RBTree<T>::insert(T item)
{
   num++; // increment first to cover both cases
   // insert left or right depending on value
   /* std::cerr << "insert level: "; */
   /* root->level(); // testing rotations */
   /* std::cerr << "\n"; */
   if (!root) // root node
   {
      root = new BNode(item);
      root->setRed(false); // root is black
      return;
   }
   
   BNode * temp = root;
   bool found = false;
   while(!found)
   {
      if (item <= temp->getData())
      {
         if(!temp->getLeftChild())
         {
            temp->insertLeft(item);
            found = true;
         }         
         temp = temp->getLeftChild();        
      }
      else
      {
         if(!temp->getRightChild())
         {
            temp->insertRight(item);
            found = true;
         }
         temp = temp->getRightChild();
      }
   }
   // check red-black status and re-balance if needed
   if (temp->getParent()->isRed())
   {
      temp->insertBalance();
      // move root to new root if needed
      while (root->getParent())
      {
         root = root->getParent();
      }
   }
}

template <class T>
void RBTree<T>::remove(Iterator it)
{
   //  only work for valid data
   if (it != end())
   {
      BNode * orig = it.getNode();
      
      // set rebalance variables
      BNode * rotate = NULL;
      bool isLeftChild = false;
      
      // find an heir
      
      // one right, all the way left
      BNode * heir = orig->getRightChild();
      if (heir)
      {
         while (heir->getLeftChild())
         {
            heir = heir->getLeftChild();
         }
         if (!heir->isRed()) // check for rotation
         {
            rotate = heir->getParent();
            isLeftChild = heir->getParent()->getLeftChild() == heir;
         }
      }
      
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
           
         if (!orig->isRed()) // check for rotation
         {
            rotate = orig->getParent();
            isLeftChild = (orig->getParent() &&
                           orig->getParent()->getLeftChild() == orig);
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

      // may need to set up pointers to rotation nodes and double blacks
      // before relinking and test for those, otherwise find rotation
      // stuff could get a bit complicated...
      // test for rebalance
      /*
      if (heir && !heir->isRed()) // if heir was black, rebalance is needed
      {
         std::cerr << "remove rebalance with black heir\n";
         // find double black and rebalance, or make a pointer to double
         // black node before during removal and test for that, this will
         // be difficult in the case of a NULL double-black...
         if (heir->getRightChild() && heir->getRightChild()->isRed())
         {
            heir = heir->getRightChild();
            heir->setRed(false);
         }
         else
         {
            
         }
      }
      else if (!heir && !orig->isRed())
      {
         std::cerr << "remove rebalance with no heir\n";
         orig->getParent()->removeBalance(isLeftChild);
         
      }
      else if (heir) // if heir is red, takes on parent color
      {      
         heir->setRed(orig->isRed()); 
      }
      */
      if (rotate)
      {
         std::cerr << "remove rebalance\n";
         rotate->removeBalance(isLeftChild);
      }
      else if (heir) // heir takes on parent color
      {      
         heir->setRed(orig->isRed()); 
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
typename RBTree<T>::Iterator & RBTree<T>::Iterator::operator++() // prefix
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
typename RBTree<T>::Iterator RBTree<T>::Iterator::operator++(int) // postfix
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
typename RBTree<T>::Iterator & RBTree<T>::Iterator::operator--() // prefix
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
typename RBTree<T>::Iterator RBTree<T>::Iterator::operator--(int) // postfix
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
void RBTree<T>::BNode::prune()
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
typename RBTree<T>::BNode * RBTree<T>::BNode::copy(void)
{
   // prefix, data, go left, go right...
   BNode * temp = new BNode(data);
   if (left != NULL) temp->setLeft(left->copy());
   if (right != NULL) temp->setRight(right->copy());
   return temp;
}

/**********************************************************************
 * handles insertion re-balancing using red black to keep
 * performance optimal
 **********************************************************************/
template <class T>
void RBTree<T>::BNode::insertBalance()
{
   // check red-black cases and re-balance
   BNode * parent = getParent();
   BNode * grandparent = parent->getParent();
   BNode * uncle = grandparent->getRightChild();
   bool parentLeft = uncle != parent; // detect side of uncle

   if(!parentLeft) // select other side for uncle if needed
   {
      uncle = grandparent->getLeftChild();
   }
   if (uncle && uncle->isRed()) // recolor
   {
      parent->setRed(false);
      if (uncle)
      {
         uncle->setRed(false);
      }
      if (grandparent->getParent()) // grandparent is not root
      {
         grandparent->setRed(true);
         if (grandparent->getParent()->isRed())
         {
            grandparent->insertBalance(); // move up tree if needed
         }
      }
   }
   else
   {
      bool leftChild = parent->getLeftChild() == this; // detect myself
      // handle 4 rotation cases depending on parent and myself status
      if (parentLeft && leftChild) // both left
      {
         // single right rotation
         if (grandparent->getParent()) // grandparent is not root
         {
            // grandparent is left child
            if (grandparent->getParent()->getLeftChild() == grandparent)
            {
               grandparent->getParent()->setLeft(parent);
            }
            else
            {
               grandparent->getParent()->setRight(parent);
            }
         }
         else
         {
            parent->setParent(grandparent->getParent());
         }
         grandparent->setLeft(parent->getRightChild());
         parent->setRight(grandparent);
         parent->setRed(false);
         grandparent->setRed(true);
      }
      else if (parentLeft && !leftChild) // parent left, me right
      {
         // left right rotation
         if (grandparent->getParent()) // grandparent is not root
         {
            // grandparent is left child
            if (grandparent->getParent()->getLeftChild() == grandparent)
            {
               grandparent->getParent()->setLeft(this);
            }
            else
            {
               grandparent->getParent()->setRight(this);
            }
         }
         else
         {
            setParent(grandparent->getParent());
         }
         grandparent->setLeft(getRightChild());
         parent->setRight(getLeftChild());
         setRight(grandparent);
         setLeft(parent);
         setRed(false);
         grandparent->setRed(true);
      }
      else if (!parentLeft && !leftChild) // both right
      {
         // single left rotation
         if (grandparent->getParent()) // grandparent is not root
         {
            // grandparent is left child
            if (grandparent->getParent()->getLeftChild() == grandparent)
            {
               grandparent->getParent()->setLeft(parent);
            }
            else
            {
               grandparent->getParent()->setRight(parent);
            }
         }
         else
         {
            parent->setParent(grandparent->getParent());
         }
         grandparent->setRight(parent->getLeftChild());
         parent->setLeft(grandparent);
         parent->setRed(false);
         grandparent->setRed(true);
      }
      else // parent right, me left
      {
         // right left rotation
         if (grandparent->getParent()) // grandparent is not root
         {
            // grandparent is left child
            if (grandparent->getParent()->getLeftChild() == grandparent)
            {
               grandparent->getParent()->setLeft(this);
            }
            else
            {
               grandparent->getParent()->setRight(this);
            }
         }
         else
         {
            setParent(grandparent->getParent());
         }
         grandparent->setRight(getLeftChild());
         parent->setLeft(getRightChild());
         setLeft(grandparent);
         setRight(parent);
         setRed(false);
         grandparent->setRed(true);
      }
   }  
}

/**********************************************************************
 * handles deletion re-balancing using red black to keep
 * performance optimal
 **********************************************************************/
template <class T>
void RBTree<T>::BNode::removeBalance(bool isLeftChild)
{
   // param is bool indicating which child is to be colored black
   BNode * child = (isLeftChild? getLeftChild():getRightChild());
   BNode * sibling = (isLeftChild? getRightChild():getLeftChild());
   if (child && child->isRed()) // re-color red to black and done
   {
      child->setRed(false);
      return;
   }
   // double black needs rotations to fix...
   if(sibling)
   {
      BNode * nephew = (isLeftChild? sibling->getRightChild()
                        : sibling->getLeftChild());
      BNode * niece = (isLeftChild? sibling->getLeftChild()
                        : sibling->getRightChild());
      if (sibling->isRed())
      {
         std::cout << "red sibling - single rotation and recolor, remove balance from new parent and I'm still double black\n";
      }
      else if (nephew && nephew->isRed())
      {
         std::cout << "red nephew - one rotation and recolor\n";
         if(getParent()) // if I'm not root, I need to set parent new child before relinking parent...
         {
         }
         if(isLeftChild)
         {
            setRightChild(sibling->getLeftChild());
            sibling->setLeftChild(this);
         }
         else
         {
         }
      }
      else if (niece && niece->isRed())
      {
         std::cout << "red niece - double rotation and recolor\n";
      }
      else
      {
         std::cout << "both black - push black level up and rebalance\n";
         sibling->setRed(true);
         if (getParent())
         {
            if(getParent()->isRed())
            {
               getParent()->setRed(false);
            }
            else
            {
               getParent()->removeBalance(this == getParent()->getLeftChild());
            }
         }
      }
   }
   else
   {
      std::cout << "no sibling, treat as black with 2 black children...";
   }
}

/**********************************************************************
 * do infix traversal
 **********************************************************************/
template <class T>
void RBTree<T>::BNode::infix(void)
{
   if (left != NULL) left->infix();
   std::cout << data << " ";
   if (right != NULL) right->infix();
}

/**********************************************************************
 * do prefix traversal
 **********************************************************************/
template <class T>
void RBTree<T>::BNode::prefix(void)
{
   std::cout << data << " ";
   if (left != NULL) left->prefix();
   if (right != NULL) right->prefix();
}

/**********************************************************************
 * do postfix traversal
 **********************************************************************/
template <class T>
void RBTree<T>::BNode::postfix(void)
{
   if (left != NULL) left->postfix();
   if (right != NULL) right->postfix();
   std::cout << data << " ";
}

/**********************************************************************
 * do level order traversal
 **********************************************************************/
template <class T>
void RBTree<T>::BNode::level(void)
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
         std::cout << temp->data << " - " << (temp->isRed()?"red":"black") << " ";
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
// wrapper class for RBTreeIterator that uses the proper iterator
// so that testbed will work...
// this is my adapter pattern!!! :)
template <class T>
class RBTreeIterator
{
  private:
   typename RBTree<T>::Iterator it;
  public:
  RBTreeIterator(typename RBTree<T>::Iterator rhs = NULL) : it(rhs) {}
   ~RBTreeIterator() {}
   const T operator * ()
   {
      return *it;
   }
   bool operator == (typename RBTree<T>::Iterator rhs)
   {
      return it == rhs;
   }
   bool operator != (typename RBTree<T>::Iterator rhs)
   {
      return !(it == rhs);
   }
   RBTreeIterator & operator++() { ++it; return *this; }
   RBTreeIterator operator++(int) { RBTreeIterator copy(it);it++; return copy; }
   RBTreeIterator & operator--() { --it; return *this; }
   RBTreeIterator operator--(int) { RBTreeIterator copy(it); it--; return copy; }
   typename RBTree <T>::Iterator getIterator() { return it; }
};
#endif

#endif
