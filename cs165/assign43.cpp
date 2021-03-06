/***********************************************************************
* Program:
*    Assignment 43, Class Templates
*    Brother Boyer, CS165
* Author:
*    Brady Field
* Summary: 
*    A class template is similar to a function template, except the
*    abstract type can be applied to all member functions and all
*    member variables of the class. Your job with this assignment is
*    to convert the following class to be type-agnostic.
*
*    Estimated:  1.0 hrs   
*    Actual:     0.5 hrs
*      A bit confusing. But it was alright.
************************************************************************/

#include <iostream>
#include <vector>
#include <cassert>
using namespace std;


// this allows to me conveniently add debug code.  See push() for an example
#ifdef NDEBUG
#define DEBUG(x)    // disappears in ship (or non-debug) mode
#else
#define DEBUG(x) x  // appears in debug mode 
#endif // NDEBUG

/****************************************************
 * STACK: a first-in, last-out data structure
 ****************************************************/
template<class T>
class Stack
{
public:
   bool pop(T &value);
   void push(T value);
   bool isEmpty()       { return data.size() == 0; };
private:
   vector <T> data;
};


/**********************************************************************
 * MAIN: Simple driver program to exercise our Stack data type
 ***********************************************************************/
int main()
{
   //
   // Integer Stack
   //
   cout << "#### Integers ####\n";
   Stack <int>stack;
   int value;

   // add three to the stack
   for (int i = 0; i < 3; i++)
   {
      cout << "push: ";
      cin >> value;
      stack.push(value);
   }
   
   // remove one just for kicks
   stack.pop(value);
   cout << "\tpop: " << value << endl;

   // add three more
   for (int i = 0; i < 3; i++)
   {
      cout << "push: ";
      cin >> value;
      stack.push(value);
   }

   // remove them all 
   while (stack.pop(value))
      cout << "\tpop: " << value << endl;
   assert(stack.isEmpty());

   //
   // String Stack
   //
   cout << "#### Strings ####\n";
   Stack <string>stack1;
   string value1;

   // add three to the stack
   for (int i = 0; i < 3; i++)
   {
      cout << "push: ";
      cin >> value1;
      stack1.push(value1);
   }
   
   // remove one just for kicks
   stack1.pop(value1);
   cout << "\tpop: " << value1 << endl;

   // add three more
   for (int i = 0; i < 3; i++)
   {
      cout << "push: ";
      cin >> value1;
      stack1.push(value1);
   }

   // remove them all 
   while (stack1.pop(value1))
      cout << "\tpop: " << value1 << endl;
   assert(stack1.isEmpty());
   
   return 0;
}




/************************************************
 * POP: remove the item off the end of the list
 *   OUTPUT: value:    The value to be removed from the stack
 *           <return>  Whether the pop was successful
 ************************************************/
template<class T>
bool Stack<T>::pop(T &value)
{
   // empty stack case.
   if (isEmpty())
      return false;

   // remove the last item off the stack
   assert(data.size() > 0);
   value = data[data.size() - 1];
   data.resize(data.size() - 1);
   assert(data.size() >= 0);
   return true;
}


/**********************************************
 * PUSH: add an item to the end of the list
 *   INPUT: value:     The item to be added to the stack
 *********************************************/
template<class T>
void Stack<T>::push(T value)
{
   DEBUG(int size = data.size(););
   assert(size >= 0);
   data.resize(data.size() + 1, value);
   assert(size + 1 == data.size());
   assert(!isEmpty());
};
