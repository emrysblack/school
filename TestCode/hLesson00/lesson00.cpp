/***********************************************************************
* Program:
*    Lesson 00, Container
*    Brother Helfrich, CS 235
* Author:
*    Br. Helfrich
* Summary: 
*    This is a driver program to exercise the Container class.  When you
*    submit your program, this should not be changed in any way.  That being
*    said, you may need to modify this once or twice to get it to work.
************************************************************************/

#include <iostream>       // for CIN and COUT
#include <string>         // because testIterate() uses a Container of string
#include "container.h"    // your Container class needs to be in container.h
using namespace std;

// prototypes for our four test functions
void testSimple();
void testFill();
void testIterate();
void testCopy();

// To get your program to compile, you might need to comment out a few
// of these. The idea is to help you avoid too many compile errors at once.
// I suggest first commenting out all of these tests, then try to use only
// TEST1.  Then, when TEST1 works, try TEST2 and so on.
#define TEST1   // for testSimple()
#define TEST2   // for testFill()
#define TEST3   // for testIterate()
#define TEST4   // for testCopy()

/**********************************************************************
 * MAIN
 * This is just a simple menu to launch a collection of tests
 ***********************************************************************/
int main()
{
   // menu
   cout << "Select the test you want to run:\n";
   cout << "\t1. Just create and destroy a Container.\n";
   cout << "\t2. The above plus fill the Container.\n";
   cout << "\t3. The above plus iterate through the Container.\n";
   cout << "\t4. The above plus copy the Container.\n";

   // select
   int choice;
   cout << "> ";
   cin  >> choice;
   switch (choice)
   {
      case 1:
         testSimple();
         cout << "Test 1 complete\n";
         break;
      case 2:
         testFill();
         cout << "Test 2 complete\n";
         break;
      case 3:
         testIterate();
         cout << "Test 3 complete\n";
         break;
      case 4:
         testCopy();
         cout << "Test 4 complete\n";
         break;
      default:
         cout << "Unrecognized command, exiting...\n";
   }
   
   return 0;
}

/*******************************************
 * TEST SIMPLE
 * Very simple test for a container: create and destroy
 ******************************************/
void testSimple()
{
#ifdef TEST1
   // Test1: bool Container with default constructor
   cout << "Create a bool Container using default constructor\n";
   Container <bool> c1;
   cout << "\tSize:  " << c1.size() << endl;
   cout << "\tEmpty? " << (c1.empty() ? "Yes" : "No") << endl;

   {
      // Test2: double Container with non-default constructor
      cout << "Create a double Container using the non-default constructor\n";
      Container <double> c2(10 /*capacity*/);
      cout << "\tSize:  " << c2.size() << endl;
      cout << "\tEmpty? " << (c2.empty() ? "Yes" : "No") << endl;
   }
   cout << "\tDestroying the second Container\n";
#endif // TEST1
}

/******************************************
 * TEST FILL
 * This will test the following:
 *   1. Instantiating a Container object
 *   2. Filling the contents with values
 *   3. Destroying an object when finished
 ******************************************/
void testFill()
{
#ifdef TEST2
   // Test1: integer Container with default constructor
   {
      // create 
      cout << "Create an integer Container with the default constructor\n";
      Container <int> c1;

      cout << "\tEnter numbers, type 0 when done\n";
      int number;
      do
      {
         cout << "\t> ";
         cin  >> number;
         if (number)
            c1.insert(number);
      }
      while (number);
      cout << "\tSize:  " << c1.size() << endl;
      cout << "\tEmpty? " << (c1.empty() ? "Yes" : "No") << endl;
   }
   cout << "\tFirst container deleted\n";

   // Test2: character Container with non-default constructor
   {
      cout << "Create a character Container with non-default constructor\n";
      Container <char> c2(2);

      cout << "Insert user-provided characters in the Container\n";
      cout << "\tEnter characters, type 'q' when done\n";
      char letter;
      do
      {
         cout << "\t> ";
         cin  >> letter;
         if (letter != 'q')
            c2.insert(letter);
      }
      while (letter != 'q');
      cout << "\tSize:  " << c2.size() << endl;

      // clear the contents
      cout << "\tNow we will clear the contents\n";
      c2.clear();
      cout << "\tSize:  " << c2.size() << endl;
      cout << "\tEmpty? " << (c2.empty() ? "Yes" : "No") << endl;      
   }
   cout << "\tSecond Container deleted\n";
#endif // TEST2
}

/******************************************
 * TEST FILL
 * This will test the following:
 *   1. Instantiating a Container object
 *   2. Filling the contents with values
 *   3. Displaying the values using an iterator
 *   4. Destroying an object when finished
 ******************************************/
void testIterate()
{
#ifdef TEST3
   // create a list
   cout << "Create a Container of strings with the default constructor.\n";
   Container <string> c;

   // fill the container with text
   cout << "\tEnter text, type \"quit\" when done\n";
   string text;
   do
   {
      cout << "\t> ";
      cin  >> text;
      if (text != "quit")
         c.insert(text);
   }
   while (text != "quit");

   // display the contents of the Container
   cout << "Use the iterator to display the contents of the Container\n";
   ContainerIterator <string> it;
   for (it = c.begin(); it != c.end(); ++it)
      cout << "\t" << *it << endl;
#endif // TEST3
}

/**********************************************
 * TEST COPY
 * This will test the following:
 *    1. Instantiate a Container object using non-default constructor
 *    2. Fill the contents with values
 *    3. Copy one Container with the values of another
 *    4. Display the contents of the copied Container with an iterator
 **********************************************/
void testCopy()
{
#ifdef TEST4
   // create a list
   cout << "Create a Container of floats with the default constructor.\n";
   Container <float> c1;

   // fill the container with numbers
   cout << "\tEnter numbers, type 0.0 when done\n";
   float number;
   do
   {
      cout << "\t> ";
      cin  >> number;
      if (number != 0.0)
         c1.insert(number);
   }
   while (number != 0.0);

   // copy the container
   cout << "Copy the contents of the Container into a new Container\n";
   Container <float> c2(c1);
   
   // display the contents of the Container
   cout << "Use the iterator to display the contents of the Container\n";
   ContainerIterator <float> it;
   cout.setf(ios::fixed | ios::showpoint);
   cout.precision(1);
   for (it = c2.begin(); it != c2.end(); ++it)
      cout << "\t" << *it << endl;
#endif // TEST3
}
