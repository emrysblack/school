/***********************************************************************
* Program:
*    Lesson 01, Set
*    Brother Helfrich, CS 235
* Author:
*    Br. Helfrich
* Summary: 
*    This is a driver program to exercise the Set class.  When you
*    submit your program, this should not be changed in any way.  That being
*    said, you may need to modify this once or twice to get it to work.
************************************************************************/

#include <iostream>       // for CIN and COUT
#include <string>         // because testIterate() uses a Set of string
#include "set.h"          // your Set class needs to be in set.h
#include "goFish.h"       // your goFish() function needs to be defined here
using namespace std;

// prototypes for our four test functions
void testSimple();
void testFill();
void testFind();
void testUnionIntersection();

// To get your program to compile, you might need to comment out a few
// of these. The idea is to help you avoid too many compile errors at once.
// I suggest first commenting out all of these tests, then try to use only
// TEST1.  Then, when TEST1 works, try TEST2 and so on.
#define TEST1   // for testSimple()
#define TEST2   // for testFill()
#define TEST3   // for testFind()
#define TEST4   // for testUnionItersection()

/**********************************************************************
 * MAIN
 * This is just a simple menu to launch a collection of tests
 ***********************************************************************/
int main()
{
   // menu
   cout << "Select the test you want to run:\n";
   cout << "\t0. Go Fish!\n";
   cout << "\t1. Just create and destroy a Set.\n";
   cout << "\t2. The above plus fill and iterate through the Set.\n";
   cout << "\t3. The above plus find if an item is in the Set.\n";
   cout << "\t4. The above plus union and intersection.\n";

   // select
   int choice;
   cout << "> ";
   cin  >> choice;
   switch (choice)
   {
      case 0:
         goFish();
         break;
      case 1:
         testSimple();
         cout << "Test 1 complete\n";
         break;
      case 2:
         testFill();
         cout << "Test 2 complete\n";
         break;
      case 3:
         testFind();
         cout << "Test 3 complete\n";
         break;
      case 4:
         testUnionIntersection();
         cout << "Test 4 complete\n";
         break;
      default:
         cout << "Unrecognized command, exiting...\n";
   }
   
   return 0;
}

/*******************************************
 * TEST SIMPLE
 * Very simple test for a set: create and destroy
 ******************************************/
void testSimple()
{
#ifdef TEST1
   // Test1: bool Set with default constructor
   cout << "Create a bool Set using default constructor\n";
   Set <bool> s1;
   cout << "\tSize:  " << s1.size() << endl;
   cout << "\tEmpty? " << (s1.empty() ? "Yes" : "No") << endl;

   {
      // Test2: double Set with non-default constructor
      cout << "Create a double Set using the non-default constructor\n";
      Set <double> s2(10 /*capacity*/);
      cout << "\tSize:  " << s2.size() << endl;
      cout << "\tEmpty? " << (s2.empty() ? "Yes" : "No") << endl;
   }
   cout << "\tDestroying the second Set\n";
#endif // TEST1
}

/******************************************
 * TEST FILL
 * This will test the following:
 *   1. Instantiating a Set object
 *   2. Filling the contents with values
 *   3. Iterate through the set to display the contents
 *   4. Destroying an object when finished
 ******************************************/
void testFill()
{
#ifdef TEST2
   // create 
   cout << "Create an integer Set with the default constructor\n";
   Set <int> s;
   
   cout << "\tEnter numbers, type 0 when done\n";
   int number;
   do
   {
      cout << "\t> ";
      cin  >> number;
      if (number)
         s.insert(number);
   }
   while (number);

   // display how big it is
   cout << "\tSize:  " << s.size() << endl;
   cout << "\tEmpty? " << (s.empty() ? "Yes" : "No") << endl;

   // iterate through the set
   cout << "Iterate through the set and display the contents\n";
   SetIterator <int> it;
   for (it = s.begin(); it != s.end(); ++it)
      cout << "\t" << *it << endl;
#endif // TEST2
}

/******************************************
 * TEST FIND
 * This will test the following:
 *   1. Instantiating a Set object
 *   2. Filling the contents with values
 *   3. Displaying the values using an iterator
 *   4. Prompt for the existance of an item in the set and remove it
 *   5. Display the remaining items in the set
 ******************************************/
void testFind()
{
#ifdef TEST3
   // create a list
   cout << "Create a Set of strings with the default constructor.\n";
   Set <string> s;

   // fill the Set with text
   cout << "\tEnter text, type \"quit\" when done\n";
   string text;
   do
   {
      cout << "\t> ";
      cin  >> text;
      if (text != "quit")
         s.insert(text);
   }
   while (text != "quit");

   // display the contents of the Set
   cout << "Use the iterator to display the contents of the Set\n";
   SetIterator <string> it;
   for (it = s.begin(); it != s.end(); ++it)
      cout << "\t" << *it << endl;

   // look for an item in the set
   cout << "Find items in the set and delete.\n";
   cout << "\tEnter words to search for, type \"quit\" when done\n";
   cout << "\t> ";
   cin  >> text;
   do
   {
      SetIterator <string> itEmpty;
      SetIterator <string> itFind = s.find(text);
      if (itFind != itEmpty)
      {
         cout << "\tFound and removed!\n";
         s.erase(itFind);
      }
      else
         cout << "\tNot found\n";
      cout << "\t> ";
      cin  >> text;
   }
   while (text != "quit");

   // show the list again
   cout << "The remaining list after the items were removed\n";
   for (it = s.begin(); it != s.end(); ++it)
      cout << "\t" << *it << endl;
   
#endif // TEST3
}

/**********************************************
 * TEST UNION INTERSECTION
 * This will test the following:
 *    1. Instantiate two Set objects and fill them
 *    2. Display the results of Union
 *    4. Display the results of Intersection
 **********************************************/
void testUnionIntersection()
{
#ifdef TEST4
   cout.setf(ios::fixed | ios::showpoint);
   cout.precision(1);

   // fill the first set with numbers
   Set <float> s1;
   cout << "First set: enter numbers, type 0.0 when done\n";
   float number;
   do
   {
      cout << "\t> ";
      cin  >> number;
      if (number != 0.0)
         s1.insert(number);
   }
   while (number != 0.0);

   // fill the second set with numbers
   Set <float> s2;
   cout << "Second set: enter numbers, type 0.0 when done\n";
   do
   {
      cout << "\t> ";
      cin  >> number;
      if (number != 0.0)
         s2.insert(number);
   }
   while (number != 0.0);
      
   // display union
   cout << "s1 && s2:\n";
   Set <float> sUnion(s1 && s2);
   SetIterator <float> it;
   for (it = sUnion.begin(); it != sUnion.end(); ++it)
      cout << "\t" << *it << endl;

   // display intersection
   cout << "s1 || s2:\n";
   Set <float> sIntersection(s1 || s2);
   for (it = sIntersection.begin(); it != sIntersection.end(); ++it)
      cout << "\t" << *it << endl;

#endif // TEST3
}
