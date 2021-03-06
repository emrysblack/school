// template declaration
#include <iostream>
using namespace std;

#ifndef CONTAINER_H
#define CONTAINER_H

template <typename T>
/**********************************************************************
 * Conatiner class using templates to store data
 **********************************************************************/ 
class ContainerIterator
{
   private:
   T *item;
   public:
   ContainerIterator(){item = NULL;};      // default constructor
   ContainerIterator(T *loc){item = loc;};      // non-default constructor
   ContainerIterator(const ContainerIterator<T> &rSide){item = rSide.item;};
   ~ContainerIterator(){item = NULL;};                   // destructor
   T* getItem(){return item;};
   ContainerIterator<T>& operator = (const ContainerIterator<T> &rSide)
      {item = rSide.item; return *this;};
   
   ContainerIterator<T> operator ++(int)
   {ContainerIterator<T> postFix(*this); item++; return postFix;};
   ContainerIterator<T>& operator ++(){item++; return *this;};
   T& operator *(){return *item;};
};

/**********************************************************************
 * Returns true if two iterators are pointing at same location
 **********************************************************************/
template <typename T>
bool operator ==(ContainerIterator<T> lSide, ContainerIterator<T> rSide)
{
   return lSide.getItem() == rSide.getItem();
}

/**********************************************************************
 * Returns true if two iterators are not pointing at same location
 **********************************************************************/
template <typename T>
bool operator !=(ContainerIterator<T> lSide, ContainerIterator<T> rSide)
{
   return lSide.getItem() != rSide.getItem();
}

template <typename T>

/**********************************************************************
 * Container class using templates to store data
 **********************************************************************/ 
class Container
{
   private:
      int myTop;                  // index of top of stack
      int maxSize;                // maximum size of stack  
      T *items;            // pointer for dynamic array
   public:
      Container(int size = 100);      // default constructor (stack size 100)
      Container(const Container<T> &rSide); // copy constructor
      ~Container();                   // destructor
      
      inline T top(void);              // returns top item in the stack
      void insert(T item);        // store item on the stack
      inline bool empty(void);           // is stack empty
      inline int size(void);
      inline void clear(void);             // remove/delete top item off stack
      inline ContainerIterator<T> begin(void);            // is stack full
      inline ContainerIterator<T> end(void);
      
      Container& operator = (const Container<T> &rSide);
};

// Class Definitions
/**********************************************************************
 * Default constructor. Sets up an array for 100 items
 **********************************************************************/
template <typename T>
   Container<T>::Container(int size)
{
   myTop = 0;
   maxSize = size;
   items = new T [size];
}
 
/***********************************************************************
 * Copy constructor. Will do a deep copy of the elements
 **********************************************************************/
template <typename T>
   Container<T>::Container(const Container<T> &rSide)
{
   maxSize = rSide.maxSize;
   myTop = rSide.myTop;
   items = new T [rSide.maxSize];

   for (int i = 0; i < maxSize; i++) // fill array
      items[i] = rSide.items[i];
}
 
/**********************************************************************
 * Destructor to return allocated memory
 **********************************************************************/
template <typename T>
   Container<T>::~Container()
{
   myTop = 0;
   maxSize = 0;
   delete [] items;
}

/**********************************************************************
 * Returns last item inserted
 **********************************************************************/
template <typename T>
   T Container<T>::top(void)
{
   return items[myTop - 1]; // get last item put on
}
 
/**********************************************************************
 * Puts a new item in the container
 **********************************************************************/
template <typename T>
   void Container<T>::insert(T item)
{
   if (myTop == maxSize)
   {
      // allocate more memory and fill
      Container<T> temp(maxSize * 2);
      temp = *this;
      *this = temp;
   }
   items[myTop] = item;
   myTop++;
}

/**********************************************************************
 * Returns true if container is empty
 **********************************************************************/
template <typename T>
   bool Container<T>::empty(void)
{
   return (myTop == 0);
}

/**********************************************************************
 * Returns number of items in the container
 **********************************************************************/
template <typename T>
   int Container<T>::size(void)
{
   return myTop;
}

/**********************************************************************
 * Resets container by ignoring all previous content
 **********************************************************************/
template <typename T>
   void Container<T>::clear(void)
{
   myTop = 0;
}
 
/**********************************************************************
 * Returns iterator to begining of container
 **********************************************************************/
template <typename T>
ContainerIterator<T> Container<T>::begin(void)
{
   return ContainerIterator<T>(&items[0]);
}

/**********************************************************************
 * Returns iterator to one past end of container
 **********************************************************************/
template <typename T>
ContainerIterator<T> Container<T>::end(void)
{
   return ContainerIterator<T>(&items[myTop]);
}

/**********************************************************************
 * Assignment operator for stack class
 **********************************************************************/
template <typename T>
   Container<T>& Container<T>::operator = 
   (const Container<T> &rSide)
{
   if (maxSize < rSide.maxSize) // if array isn't right size, reallocate
   {
      maxSize = rSide.maxSize;
      delete [] items;
      items = new T [rSide.maxSize];
   }

   myTop = rSide.myTop;
   for (int i = 0; i < rSide.maxSize; i++) // fill array
      items[i] = rSide.items[i];

   return *this;
}

#endif
