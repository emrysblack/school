/***********************************************************************
* Program:
*    Lesson 04, DEQUE
*    Brother Helfrich, CS 235
* Author:
*    Br. Helfrich
* Summary: 
*    This is a driver program to exercise the Deque class.  When you
*    submit your program, this should not be changed in any way.  That being
*    said, you may need to modify this once or twice to get it to work.
************************************************************************/

#include <iostream>     // for CIN and COUT
#include <string>       // for the String class
#include "deque.h"      // your Deque class should be in deque.h
#include "nowServing.h" // your nowServing() function
using namespace std;


// prototypes for our four test functions
void testSimple();
void testPush();
void testPop();
void testErrors();

// To get your program to compile, you might need to comment out a few
// of these. The idea is to help you avoid too many compile errors at once.
// I suggest first commenting out all of these tests, then try to use only
// TEST1.  Then, when TEST1 works, try TEST2 and so on.
#define TEST1   // for testSimple()
#define TEST2   // for testPush()
#define TEST3   // for testPop()
#define TEST4   // for testErrors()

/**********************************************************************
 * MAIN
 * This is just a simple menu to launch a collection of tests
 ***********************************************************************/
int main()
{
   // menu
   cout << "Select the test you want to run:\n";
   cout << "\t0. Now Serving\n";
   cout << "\t1. Just create and destroy a Deque\n";
   cout << "\t2. The above plus push items onto the Deque\n";
   cout << "\t3. The above plus pop items off the Deque\n";
   cout << "\t4. The above plus exercise the error Deque\n";

   // select
   int choice;
   cout << "> ";
   cin  >> choice;
   switch (choice)
   {
      case 0:
         nowServing();
         break;
      case 1:
         testSimple();
         cout << "Test 1 complete\n";
         break;
      case 2:
         testPush();
         cout << "Test 2 complete\n";
         break;
      case 3:
         testPop();
         cout << "Test 3 complete\n";
         break;
      case 4:
         testErrors();
         cout << "Test 4 complete\n";
         break;
      default:
         cout << "Unrecognized command, exiting...\n";
   }

   return 0;
}

/*******************************************
 * TEST SIMPLE
 * Very simple test for a Deque: create and destroy
 ******************************************/
void testSimple()
{
#ifdef TEST1
   // Test1: a bool Deque with default constructor
   cout << "Create a bool Deque using the default constructor\n";
   Deque <bool> d1;
   cout << "\tSize:     " << d1.size()                   << endl;
   cout << "\tEmpty?    " << (d1.empty() ? "Yes" : "No") << endl;
   cout << "\tCapacity: " << d1.capacity()               << endl;

   // Test2: double Deque with non-default constructor
   cout << "Create a double Deque using the non-default constructor\n";
   Deque <double> d2(10 /*capacity*/);
   cout << "\tSize:     " << d2.size()                   << endl;
   cout << "\tEmpty?    " << (d2.empty() ? "Yes" : "No") << endl;
   cout << "\tCapacity: " << d2.capacity()               << endl;
   
   {
      // Test3: copy the bool Deque
      cout << "Copy the double Deque using the copy-constructor\n";
      Deque <double> d3(d2);
      cout << "\tSize:     " << d3.size()                   << endl;
      cout << "\tEmpty?    " << (d3.empty() ? "Yes" : "No") << endl;
      cout << "\tCapacity: " << d3.capacity()               << endl;
   }
   cout << "\tDestroying the third Deque\n";   
#endif //TEST1
}

/*******************************************
 * TEST PUSH
 * Add a whole bunch of items to the Deque.  This will
 * test the Deque growing algorithm
 *****************************************/
void testPush()
{
#ifdef TEST2
   // create
   cout << "Create an integer Deque with the default constructor\n";
   Deque <int> d;

   cout << "\tEnter integer values, type 0 when done\n";
   int value;
   do
   {
      cout << "\t> ";
      cin  >> value;
      if (value)
      {
         d.push_back(value);

         // display the value and the capacity
         cout << "\t\tPushed " << d.back()
              << " size="      << d.size()
              << " capacity="  << d.capacity()
              << endl;
      }
   }
   while (value);

   // empty it and do it again in the front.
   d.clear();
   cout << "\tEnter integer values, type 0 when done\n";
   do
   {
      cout << "\t> ";
      cin  >> value;
      if (value)
      {
         d.push_front(value);

         // display the value and the capacity
         cout << "\t\tPushed " << d.front()
              << " size="      << d.size()
              << " capacity="  << d.capacity()
              << endl;
      }
   }
   while (value);
#endif // TEST2   
}

/*******************************************
 * TEST POP
 * We will test pop_front(), pop_back(),
 * push_front(), and push_back() to make
 * sure the dEque looks the way we expect
 * it to look.
 ******************************************/
void testPop()
{
#ifdef TEST3
   // create
   cout << "Create a string Deque with the non-default constructor\n";
   Deque <string> d(4);

   // instructions
   cout << "instructions:\n"
        << "\t+f dog   pushes dog onto the front\n"
        << "\t+b cat   pushes cat onto the back\n"
        << "\t-f       pops off the front\n"
        << "\t-b       pops off the back\n"
        << "\t*        clear the deque\n"
        << "\t?        shows the statistics of the deque\n"
        << "\t!        quit\n";

   string command;
   string text;
   do
   {
      cout << "> ";
      cin  >> command;

      try
      {
         if (command == "+f")
         {
            cin >> text;
            d.push_front(text);
         }
         else if (command == "+b")
         {
            cin >> text;
            d.push_back(text);
         }
         else if (command == "-f")
         {
            cout << "\tpop: " << d.front() << endl;
            d.pop_front();
         }
         else if (command == "-b")
         {
            cout << "\tpop: " << d.back() << endl;
            d.pop_back();
         }
         else if (command == "?")
         {
            cout << "\tSize:     " << d.size()     << endl;
            cout << "\tCapacity: " << d.capacity() << endl;
         }
         else if (command == "*")
         {
            d.clear();
         }
         else if (command != "!")
         {
            cout << "Unknown command\n";
            cin.ignore(256, '\n');
         }      
      }
      catch (const char * e)
      {
         cout << '\t' << e << endl;
      }
      // d.display();
   }
   while (command != "!");
#endif // TEST3
}

/*******************************************
 * TEST ERRORS
 * Numerous error conditions will be tested
 * here, including bogus popping and the such
 *******************************************/
void testErrors()
{
#ifdef TEST4
   // create
   cout << "Create a char deque with the default constructor\n";
   Deque <char> d;

   // test using front() with an empty deque
   try
   {
      d.front();
      cout << "BUG! We should not be able to front() with an empty deque!\n";
   }
   catch (const char * error)
   {
      cout << "\tDeque::front() error message correctly caught.\n"
           << "\t\"" << error << "\"\n";
   }

   // test using back() with an empty deque
   try
   {
      d.back();
      cout << "BUG! We should not be able to back() with an empty deque!\n";
   }
   catch (const char * error)
   {
      cout << "\tDeque::back() error message correctly caught.\n"
           << "\t\"" << error << "\"\n";
   }

   // test using pop_front() with an empty deque
   try
   {
      d.pop_front();
      cout << "BUG! We should not be able to pop_front() "
           << "with an empty deque!\n";
   }
   catch (const char * error)
   {
      cout << "\tDeque::pop_front() error message correctly caught.\n"
           << "\t\"" << error << "\"\n";
   }      

   // test using pop_back() with an empty deque
   try
   {
      d.pop_back();
      cout << "BUG! We should not be able to pop_back() "
           << "with an empty deque!\n";
   }
   catch (const char * error)
   {
      cout << "\tDeque::pop_back() error message correctly caught.\n"
           << "\t\"" << error << "\"\n";
   }      

#endif // TEST4
}
