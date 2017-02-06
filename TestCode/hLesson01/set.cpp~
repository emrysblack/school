// template declaration
#include <iostream>
using namespace std;

#ifndef SET_H
#define SET_H

template <typename T>
/**********************************************************************
 * Conatiner class using templates to store data
 **********************************************************************/ 
class SetIterator
{
   private:
   T *item;
   public:
   SetIterator(){item = NULL;};      // default constructor
   SetIterator(T *loc){item = loc;};      // non-default constructor
   SetIterator(const SetIterator<T> &rSide){item = rSide.item;};
   ~SetIterator(){item = NULL;};                   // destructor
   T* getItem(){return item;};
   SetIterator<T>& operator = (const SetIterator<T> &rSide)
      {item = rSide.item; return *this;};
   
   SetIterator<T> operator ++(int)
   {SetIterator<T> postFix(*this); item++; return postFix;};
   SetIterator<T>& operator ++(){item++; return *this;};
   T& operator *(){return *item;};
};

/**********************************************************************
 * Returns true if two iterators are pointing at same location
 **********************************************************************/
template <typename T>
bool operator ==(SetIterator<T> lSide, SetIterator<T> rSide)
{
   return lSide.getItem() == rSide.getItem();
}

/**********************************************************************
 * Returns true if two iterators are not pointing at same location
 **********************************************************************/
template <typename T>
bool operator !=(SetIterator<T> lSide, SetIterator<T> rSide)
{
   return lSide.getItem() != rSide.getItem();
}

template <typename T>

/**********************************************************************
 * Set class using templates to store data
 **********************************************************************/ 
class Set
{
   private:
      int myTop;                  // index of top of stack
      int maxSize;                // maximum size of stack  
      T *items;            // pointer for dynamic array
      void sort(); // sorts items
   public:
      Set(int size = 100);      // default constructor (stack size 100)
      Set(const Set<T> &rSide); // copy constructor
      ~Set();                   // destructor
      
      T top(void) const;              // returns top item in the stack
      void insert(T item);        // store item on the stack
      bool empty(void) const;           // is stack empty
      int size(void) const;
      void clear(void);             // clear the contents
      SetIterator<T> begin(void) const;            // is stack full
      SetIterator<T> end(void) const;
      SetIterator<T> find(T item) const;
      void erase(SetIterator<T> item); // erase a signle element
      
      Set& operator = (const Set<T> &rSide);
};
template <typename T>
Set<T> operator && (const Set<T> &lSide, const Set<T> &rSide);
template <typename T>
Set<T> operator || (const Set<T> &lSide, const Set<T> &rSide);
template <typename T>
ostream & operator << (ostream & out, const Set<T> &rSide);

// Class Definitions
/**********************************************************************
 * Default constructor. Sets up an array for 100 items
 **********************************************************************/
template <typename T>
   Set<T>::Set(int size)
{
   myTop = 0;
   maxSize = size;
   items = new T [size];
}
 
/***********************************************************************
 * Copy constructor. Will do a deep copy of the elements
 **********************************************************************/
template <typename T>
   Set<T>::Set(const Set<T> &rSide)
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
   Set<T>::~Set()
{
   myTop = 0;
   maxSize = 0;
   delete [] items;
}

/**********************************************************************
 * Returns last item inserted
 **********************************************************************/
template <typename T>
   T Set<T>::top(void) const
{
   return items[myTop - 1]; // get last item put on
}
 
/**********************************************************************
 * Puts a new item in the container
 **********************************************************************/
template <typename T>
   void Set<T>::insert(T item)
{
   // check for duplicates
   for (int i = 0; i < myTop + 1; i++)
   {
      if (item == items[i])
         return;
   }
   
   if (myTop == maxSize)
   {
      // allocate more memory and fill
      Set<T> temp(maxSize * 2);
      temp = *this;
      *this = temp;
   }
   items[myTop] = item;
   myTop++;
   sort();
}

/**********************************************************************
 * Puts a new item in the container
 **********************************************************************/
template <typename T>
   void Set<T>::sort()
{
   T temp;
   // simple bubble sort
   for (int i = 0; i < myTop - 1; i++)
   {
      if (items[i] > items[i + 1])
      {
         // swap
         temp = items[i];
         items[i] = items[i + 1];
         items[i + 1] = temp;
         i = -1;
      }
   }
}

/**********************************************************************
 * Returns true if container is empty
 **********************************************************************/
template <typename T>
   bool Set<T>::empty(void) const
{
   return (myTop == 0);
}

/**********************************************************************
 * Returns number of items in the container
 **********************************************************************/
template <typename T>
   int Set<T>::size(void) const
{
   return myTop;
}

/**********************************************************************
 * Resets container by ignoring all previous content
 **********************************************************************/
template <typename T>
   void Set<T>::clear(void)
{
   myTop = 0;
}
 
/**********************************************************************
 * Returns iterator to begining of container
 **********************************************************************/
template <typename T>
SetIterator<T> Set<T>::begin(void) const
{
   return SetIterator<T>(&items[0]);
}

/**********************************************************************
 * Returns iterator to one past end of container
 **********************************************************************/
template <typename T>
SetIterator<T> Set<T>::end(void) const
{
   return SetIterator<T>(&items[myTop]);
}

/**********************************************************************
 * Returns iterator pointing to a specific item in the set
 **********************************************************************/
template <typename T>
SetIterator<T> Set<T>::find(T item) const
{
   SetIterator<T> it = NULL;
   for (int i = 0; i < myTop; i++)
   {
      if (item == items[i])
      {
         it = &items[i];
      }
   }
      
   return it;
}

/**********************************************************************
 * Returns iterator pointing to a specific item in the set
 **********************************************************************/
template <typename T>
void Set<T>::erase(SetIterator<T> item)
{
   SetIterator<T> next = item;
   // erase item and shift others over
   for (next++; next != end(); item++, next++)
   {
      *item = *next;
   }
   item = NULL;
   myTop--;
}

/**********************************************************************
 * Assignment operator for stack class
 **********************************************************************/
template <typename T>
   Set<T>& Set<T>::operator =
   (const Set<T> &rSide)
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

/*********************************************************************
 * references elements to see if they have numbers in common
 * and returns a new List with only those numbers
 *********************************************************************/
   template <typename T>
Set<T> operator && (const Set<T> &lSide, const Set<T> &rSide)
{
   Set<T> tmp(1);
   // get number of intersections between sets

   for (SetIterator<T> it = lSide.begin(); it != lSide.end(); it++)
   {
      if (rSide.find(*it).getItem() != NULL)
         tmp.insert(*it);
   }
   return tmp;
}

/*********************************************************************
 * references elements to see if they have numbers in common
 * and returns a new List with a combination of the two lists
 *********************************************************************/
template <typename T>
Set<T> operator || (const Set<T> &lSide, const Set<T> &rSide)
{
   Set<T> tmp;

   // left side
   for (SetIterator<T> it = lSide.begin(); it != lSide.end(); it++)
   {
         tmp.insert(*it);
   }

   // right side
   for (SetIterator<T> it = rSide.begin(); it != rSide.end(); it++)
   {
         tmp.insert(*it);
   }
   return tmp;
}

/*********************************************************************
 * references elements to see if they have numbers in common
 * and returns a new List with a combination of the two lists
 *********************************************************************/
template <typename T>
ostream & operator << (ostream & out, const Set<T> &rSide)
{
   SetIterator<T> it = rSide.begin();
   out << *it;
   for (it++; it != rSide.end(); it++)
      out << ", " << *it;
   return out;
}

#endif
