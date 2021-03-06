// compile with: g++ -o deepness deepness.cpp -lntl

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <NTL/ZZ.h>
#include <NTL/RR.h>

NTL_CLIENT

const RR ROOT2 = SqrRoot(to_RR(2));
const RR ROOT2ADD2 = SqrRoot(to_RR(2)) + 2;
const ZZ BIG_INTEGER = to_ZZ("7194898723259873456987340698308962983739586724987345982634592783495872394857932745987234958");

/*****************************************************************************
 * tests the conjecture of SetA and SetB as defined in class
 *****************************************************************************/
bool testConjecture(const RR & upperLimit)
{
   // declare before loop to save on efficiency
   RR x;
   RR a = to_RR(1);
   RR b = to_RR(1);
   for (x = to_RR(1); x <= upperLimit; ++x)
   {
           // set a
           if(floor(ROOT2 * a) == x)
           {
              ++a;
           }
           // set b
           else if (floor(ROOT2ADD2 * b) == x)
           {
              ++b;
           }
           else
           {
              cout << "ERROR: should be one or the other";
              return false;
           }
   } 
   return true;
}

/*****************************************************************************
 * lists things learned during development of this project
 *****************************************************************************/
void learned()
{
   cerr << "\nI learned about conjectures and how to test them.\n"
        << "I also learned about the NTL and using ZZ and RR.\n"
        << "This was a fun project :)\n\n";
}

/*****************************************************************************
 * displays appropriate way to use program
 *****************************************************************************/
void usage(const char * argv)
{
   cerr << "Usage: " << argv << " n\n";
   cerr << "E.g., " << argv << " ";
   cerr << BIG_INTEGER << endl << endl;
}

/*****************************************************************************
 * calls the test conjecture function and gives the number of times to run
 *****************************************************************************/
void runOne(string argv)
{ 
      // how many times are we running?
      RR upperLimit = to_RR(argv.c_str());
      if (testConjecture(upperLimit))
         {
            cout << "The conjecture holds for "
                 << argv << ".\n";
         }
         else
         {
            cerr << "Conjecture failed";
         }
      return;
}

/*****************************************************************************
 * runs all functions
 *****************************************************************************/
void runAll()
{
   learned();
   usage("deepness");
   
   // default to 1 million for now if not specified
   runOne("100000000");
}
