
#ifndef MAP_H
#define MAP_H

#include "bst.h" // change to red black after rotations
#include "pair.h"

template <class T1, class T2>
class Tuple;

template <class T1, class T2>
class Map : public BST< Pair <T1, T2> >// is a, or has a?
{
  private:
      
  public:
   Map()
   {
   }
   ~Map()
   {
   }
   T2 & operator[](T1 key)
   {
      T2 value;
      Pair <T1, T2>item(key, value);
      if(this->find(item) == this->end())
         insert(item);
      return getNode(find(item))->getData().second;
   }
   
   /* // can't overload * operator since return types are unrelated... */
   /* // how did they do this in the STL...? */

   // I'm guessing that the STL map uses a red black as a complete inner
   // structure, customized it, and bumped the itererator up from the
   // tree level to the map level...

   // this is what I need to do when I get my rotations finished for the
   // red black trees...

   // I got the insert rotations to work, now I just need to finish
   // node removal and balancing
   
   /* class Iterator : public BST< Pair <T1, T2> >::Iterator */
   /* { */
   /*   public: */
   /*    virtual const T2 & operator * () */
   /*    { */
   /*       return this->p->getData().getSecond(); */
   /*    } */
   /* }; */
};

// wrapper class for BSTIterator that uses the proper iterator
// so that testbed will work...
// this is my adapter pattern!!! :)
template <class T1, class T2>
class MapIterator
{
  private:
   typename Map<T1,T2>::Iterator it;
  public:
  MapIterator(typename Map<T1,T2>::Iterator rhs = NULL) : it(rhs) {}
   ~MapIterator() {}
   const T2 & operator * ()
   {
      return (*it).getSecond();
   }
   bool operator == (typename Map<T1,T2>::Iterator rhs)
   {
      return it == rhs;
   }
   bool operator != (typename Map<T1,T2>::Iterator rhs)
   {
      return !(it == rhs);
   }
   MapIterator & operator++() { ++it; return *this; }
   MapIterator operator++(int) { MapIterator copy(it);it++; return copy; }
   MapIterator & operator--() { --it; return *this; }
   MapIterator operator--(int) { MapIterator copy(it); it--; return copy; }
   typename Map<T1, T2>::Iterator getIterator() { return it; }
};

#endif
