/***********************************************************************
* Program:
*    Homework 01, Set Class 
*    Brother Twitchell, CS 235
* Author:
*    Brady Field
* Summary: 
*    Program will read in a set of values and store them in the order
*    they come in. It will then perform basic comparison operations
*    between the list sets and display them in a reordered format    
*************************************************************************/

#include <iostream>
#include <fstream>
using namespace std;

/************************************************************************
 * normally class would be declared in its own file separately, but as
 * the class is the extent of the program I felt it would be redundant
 ************************************************************************/
class List
{
   public:
      List();
      List(int numItems); // constructors
      ~List();            // destructor
      List(const List &rightHandSide);   // copy constructor
      const List &operator = (const List &rightHandSide);
      int getNumInSet(int index);
      int getSizeOfArray();
      void addElement(int number);
      bool isElementPresent(int number);
      void display();
      void sort();
   private: // data members
      int* set;
      int sizeOfArray;
};
const List operator && (List &leftSide, List &rightSide);
const List operator || (List &leftSide, List &rightSide);
const List operator - (List &leftSide, List &rightSide);
ostream &operator << (ostream &out, List &rightSide);

/**********************************************************************
 * Driver portion of program. Will open file and read in items to the
 * classes, then will call functions to display results
 ***********************************************************************/
int main(int argc, char* argv[])
{
   int numItems = 0;
   ifstream input;
   int number = 0;

   if (argc != 2) // make sure the program has the right parameters to run
   {
      cout << "Error: must be specified with one input file\n";
   }
   else // open the file
   {
      input.open(argv[1]);
      if (input.fail())
         cout << "Error: cannot open file " << argv[1] << endl;
      else
      {
         input >> numItems; 
         List a (numItems); // create new list with memory for items
         for (int i = 0; i < numItems; i++)
         {
            input >> number; // get next number
            if (!a.isElementPresent(number)) // only add num if not in list
               a.addElement(number);
            else // skip number
               ;
         }
         input >> numItems;
         List b (numItems);
         for (int i = 0; i < numItems; i++) // get second list
         {
            input >> number; // get next number
            if (!b.isElementPresent(number)) // only add num if not in list
               b.addElement(number);
            else // skip number
               ;
         }
         input.close();
         cout << "Set A:\n" << a << endl; // display set A
         cout << "Set B:\n" << b << endl; // display set B
         List c = a && b; // show off Intersection of sets A and B
         cout << "Intersection of A and B:\n" << c << endl;
         c = a || b; // show off Union of sets A and B
         cout << "Union of A and B:\n" << c << endl;
         c = a - b; // show off A minus B
         cout << "Difference of A and B:\n" << c << endl;
         c = b - a; // show of B minus A
         cout << "Difference of B and A:\n" << c << endl;
      }
   }
   return 0;
}

/*********************************************************************
 * constructors for the List class
 *********************************************************************/
List::List() // default constructor
{
   sizeOfArray = 0;
}

List::List(int numItems) // constructor without array
{
   sizeOfArray = 0;
   set = new int [numItems]; // set dynamic memory
}

/*********************************************************************
 * destructor returns dynamic memory to system
 *********************************************************************/
List::~List()
{
   sizeOfArray = 0;
   delete [] set;
}

/*********************************************************************
 * copy constructor
 ********************************************************************/
List::List(const List &rightHandSide)
{
   // reallocate memory if not same as list being copied from
   if (sizeOfArray != rightHandSide.sizeOfArray)
   {
      delete [] set;
      sizeOfArray = rightHandSide.sizeOfArray;
      set = new int [sizeOfArray]; 
   }

   // copy contents over
   sizeOfArray = rightHandSide.sizeOfArray;
   for (int i = 0; i < sizeOfArray; i++)
      set[i] = rightHandSide.set[i];
}

/*********************************************************************
 * override to assignment operator to make sure that elements don't 
 * copy address of existing object, but copy contents
 *********************************************************************/
const List &List::operator = (const List &rightHandSide)
{
   // reallocate memory if not same as list being copied from
   if (sizeOfArray != rightHandSide.sizeOfArray)
   {
      delete [] set;
      sizeOfArray = rightHandSide.sizeOfArray;
      set = new int [sizeOfArray]; 
   }

   // copy contents over
   sizeOfArray = rightHandSide.sizeOfArray;
   for (int i = 0; i < sizeOfArray; i++)
      set[i] = rightHandSide.set[i];
   return *this;
}

/*********************************************************************
 * returns the number stored in the array at the given index
 *********************************************************************/
int List::getNumInSet(int index)
{
   return set[index];
}

/*********************************************************************
 * returns the number of elements in the array
 *********************************************************************/
int List::getSizeOfArray()
{
   return sizeOfArray;
}

/*********************************************************************
 * receives the file name specified on the command line and reads the 
 * first line to know how many values on second line to read in
 *********************************************************************/
void List::addElement(int number)
{
   set[sizeOfArray] = number; // use sizeOfArray as index
   sizeOfArray++;
}

/*********************************************************************
 * takes input number from file and compares it to everything already
 * in set to determine if it is already in there or not
 *********************************************************************/
bool List::isElementPresent(int number)
{
   for (int i = 0; i < sizeOfArray; i++)
   {
      if (set[i] == number)
         return true;
      else // do nothing
         ;
   }
   return false;
}

/**********************************************************************
 * Calls sort to put numbers in order first and then displays them
 * in a specified format: rows of 10 with 2 spaces between each entry
 **********************************************************************/
void List::display()
{   
   sort(); // put items in order for display

   // display
   int c = 0; // keep column count to star new row every ten items
   for (int i = 0; i < sizeOfArray; i++)
   {
      cout << "  "; // set two spaces between each entry
      if (set[i] < 10)
         cout << " " << set[i]; // add space to single digits
      else
         cout << set[i];
      c++; // increase column count 
      if ((c % 10 == 0) && (i < (sizeOfArray - 1))) 
         cout << endl; // new row after 10 if still have entries
      else
         ;
   }
   cout << endl;
}

/*********************************************************************
 * loops through list and reorders numbers with a bubble sort.
 * NOTES: size of set has - 1 so as not to run off end of list into
 * no-mans land. don't increment i after execution of loop or it will
 * throw off index - only increment if nothing switched
 *********************************************************************/
void List::sort()
{
   int tmp = 0;

   // compare numbers with bubble sort. size of array - 1 to not run off
   for (int i = 0; i < sizeOfArray - 1;)
   {
      if (set[i] > set[i + 1])
      {
         tmp = set[i];
         set[i] = set[i + 1];
         set[i + 1] = tmp;
         i = 0; // if something switched, start at beginning of list
      }
      else
         i++; // if no switch, go to next number
         
   }
}

/*********************************************************************
 * references elements to see if they have numbers in common
 * and returns a new List with only those numbers
 *********************************************************************/
const List operator && (List &leftSide, List &rightSide)
{
   // get number of intersections between sets
   int intCount = 0;
   List *t = &rightSide;
   for (int i = 0; i < leftSide.getSizeOfArray(); i++)
   {
      if (t->isElementPresent(leftSide.getNumInSet(i)))
         intCount++;
      else
         ;
   }

   List tmp(intCount); // allocate memory for new set

   // fill array
   for (int i = 0; i < leftSide.getSizeOfArray(); i++)
   {
      if (t->isElementPresent(leftSide.getNumInSet(i)))
      {
         tmp.addElement(leftSide.getNumInSet(i));
      }
      else
         ;
   }
   return tmp;
}

/*********************************************************************
 * references elements to see if they have numbers in common
 * and returns a new List with only unique numbers from each list
 *********************************************************************/
const List operator || (List &leftSide, List &rightSide)
{
   // get number of intersections between sets
   int intCount = 0;
   List *t1 = &rightSide;
   List *t2 = &leftSide;
   int num = t1->getSizeOfArray() + t2->getSizeOfArray(); // total entries
   for (int i = 0; i < t2->getSizeOfArray(); i++)
   {
      if (t1->isElementPresent(t2->getNumInSet(i)))
         intCount++;
      else
         ;
   }
   num -= intCount; // take out intersections to leave unique numbers

   List tmp(num); // allocate memory for new set

   // fill array
   for (int i = 0; i < t2->getSizeOfArray(); i++)
   {
      tmp.addElement(t2->getNumInSet(i));
   }
   for (int i = 0; i < t1->getSizeOfArray(); i++)
   {
      if (!t2->isElementPresent(t1->getNumInSet(i)))
      {
         tmp.addElement(t1->getNumInSet(i));
      }
      else
         ;
   }

   return tmp;
}

/*********************************************************************
 * compares two lists and returns a new list with only the numbers
 * unique to the set on the left side of operand
 *********************************************************************/
const List operator - (List &leftSide, List &rightSide)
{
   // get number of intersections between sets
   int intCount = 0;
   int num = leftSide.getSizeOfArray(); // entries from left side
   List *t = &rightSide;
   for (int i = 0; i < leftSide.getSizeOfArray(); i++)
   {
      if (t->isElementPresent(leftSide.getNumInSet(i)))
         intCount++;
      else
         ;
   }

   num -= intCount; // take out intersections to leave unique to left
   List tmp(num); // allocate memory for new set

   // fill array
   for (int i = 0; i < leftSide.getSizeOfArray(); i++)
   {
      if (!t->isElementPresent(leftSide.getNumInSet(i)))
      {
         tmp.addElement(leftSide.getNumInSet(i));
      }
      else
         ;
   }
   return tmp;
}

/*********************************************************************
 * calls display function allowing List class to be displayed 
 * easily in main. Looks much cleaner
 *********************************************************************/
ostream &operator << (ostream &out, List &rightSide)
{
   rightSide.display();
   return out;
}
