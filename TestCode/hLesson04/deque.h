// my version of a Deque container
#include <iostream>
//#include <string>

#ifndef DEQUE_H
#define DEQUE_H


template <class T>
class Deque
{
private:
   int head; // beginning of list, end is calculated
   int num;
   T *items;
   int cap;

public:
   Deque(int size = 0) throw (const char *); //constructor
   ~Deque(); // destructor
   Deque(const Deque<T> &rhs) throw (const char *); // copy constructor
   Deque & operator = (const Deque<T> &rhs) throw (const char *); // assignment
   void push_front(T value);
   inline void pop_front() throw (const char *);
   void push_back(T value);
   inline void pop_back() throw (const char *);
   void resize() throw (const char *);
   //void display(); // test function to display the whole list
   bool empty() const {return num == 0;}
   bool full() const {return num == cap;}
   int size() const {return num;}
   int capacity() const {return cap;}
   void clear() {head = 0; num = 0;}
   inline T front() throw (const char *);
   inline T back() throw (const char *);
};

/**********************************************************************
 * CONSTRUCTOR
 * sets starting values, if a size is passed in it will allocate
 ***********************************************************************/
template <class T>
Deque<T>::Deque(int size) throw (const char*)
{
   cap = size;
   head = 0;
   num = 0;
   if (cap > 0)
   {
      try
      {
         items = new T[cap];
      }
      catch(std::bad_alloc)
      {
         throw "ERROR: unable to allocate a new buffer for deque";
      }
   }
}

/**********************************************************************
 * DESTRUCTOR
 * returns memory unless it was never allocated
 ***********************************************************************/
template <class T>
Deque<T>::~Deque()
{
   if (cap > 0)
      delete [] items;
}

/**********************************************************************
 * COPY CONSTRUCTOR
 * sets up constructor and then sends it over to the assignment operator
 * to be copied
 ***********************************************************************/
template <typename T>
Deque<T>::Deque(const Deque <T> &rhs) throw (const char *)
{
   cap = rhs.cap;
   head = 0;
   num = 0;
   if (cap > 0)
   {
      try
      {
         items = new T[cap];
      }
      catch(std::bad_alloc)
      {
         throw "ERROR: unable to allocate a new buffer for deque";
      }
      *this = rhs;
   }
}

/**********************************************************************
 * ASSIGNMENT OPERATOR
 * makes sure the allocation is ok and then copies the items over
 ***********************************************************************/
template <typename T>
Deque<T> & Deque<T>::operator=(const Deque <T> &rhs) throw (const char *)
{
   if (cap != rhs.cap)
   {
      if (cap > 0) // should never be 0, but better safe than sorry
         delete [] items;
      cap = rhs.cap;
      try
      {
         items = new T[cap];
      }
      catch(std::bad_alloc)
      {
         throw "ERROR: unable to allocate a new buffer for deque";
      }
   }
   
   // reset
   head = 0;
   num = 0;

   // copy over items in order
   // I would have used the push functions, but I felt that speed was more
   // important than saving a line of code or two here
   for (int i = rhs.head, j = 0; j < rhs.num; i++, j++)
   {
      i %= rhs.cap;
      items[j] = rhs.items[i];
      num++;
   }
    
   return *this;
}

/**********************************************************************
 * PUSH_FRONT
 * puts an item on the front of the list and keeps the head tracking that
 ***********************************************************************/
template <class T>
void Deque<T>::push_front(T value)
{
   if (full())
   {
      resize();
   }
   
   head += cap - 1;
   head %= cap;
   num++;
   items[head] = value;
}

/**********************************************************************
 * PUSH_BACK
 * puts an item on the back of the list
 ***********************************************************************/
template <class T>
void Deque<T>::push_back(T value)
{
   if (full())
   {
      resize();
   }
    
   num++; // increment num before inserting so tail is in right place
   items[(head + num - 1) % cap] = value;
  
}

/**********************************************************************
 * POP_FRONT
 * just moves the head to the next item. Throws an exception in an empty
 * list
 ***********************************************************************/
template <class T>
void Deque<T>::pop_front() throw (const char *)
{
   if (num != 0)
   {
      head++;
      head %= cap;
      num--;
   }
   else
      throw "ERROR: unable to pop from the front of empty deque"; 
}

/**********************************************************************
 * POP_BACK
 * decrements count to ignore last item. Throws an exception in an empty
 * list
 ***********************************************************************/
template <class T>
void Deque<T>::pop_back() throw (const char *)
{
   if (num != 0)
   {
      num--;
   }
   else
      throw "ERROR: unable to pop from the back of empty deque";
}

/**********************************************************************
 * RESIZE
 * saves any old values in an array, makes a new array of twice the size
 * and copies them back over
 ***********************************************************************/
template <class T>
void Deque<T>::resize() throw (const char *)
{
   Deque <T> temp(*this); // hold old items
   head = 0; // reset
   num = 0;
   if (cap > 0)
      delete [] items;
   (cap == 0)?cap = 1 : cap *= 2; // reallocate
   try
   {
      items = new T[cap];
   }
   catch(std::bad_alloc)
   {
      throw "ERROR: unable to allocate a new buffer for deque";
   }

   // copy old items back in
   for (int i = temp.head, j = 0; j < temp.num; i++, j++)
   {
      i %= temp.cap;
      items[j] = temp.items[i];
      num++;
   }
}

/**********************************************************************
 * DISPLAY
 * this is just a test function to verify items' order and position
 ***********************************************************************/
/*template <class T>
void Deque<T>::display()
{
   std::cout << "--List--\n";
   for (int i = head, j = 0; j < num; i++, j++)
   {
      i %= cap;
      std::cout << "item at pos " << i  << "-> " << items[i] << std::endl;
   }
   std::cout << std::endl;
}*/

/**********************************************************************
 * FRONT
 * returns the first item or throws an exception for an empty list
 ***********************************************************************/
template <class T>
T Deque<T>::front() throw (const char *)
{
   if (num != 0)
      return items[head];
   else
      throw "ERROR: unable to access data from an empty deque";
}

/**********************************************************************
 * BACK
 * returns the last item or throws an expection for an empty list
 ***********************************************************************/
template <class T>
T Deque<T>::back() throw (const char *)
{
   if (num != 0)
      return items[(head + num - 1) % cap];
   else
      throw "ERROR: unable to access data from an empty deque";
}

#endif
