/***********************************************************************
 * Program:
 *    Exploration 1, Sweetness
 *    Brother Neff, CS 238
 * Author:
 *    You
 * Summary:
 *    Polynomial Prime Generation, with a probability connection.
 ***********************************************************************/
#include <cassert>
#include <cmath>
#include <cstdlib> // for abs()
#include <iostream>
#include <limits>  // for INT_MAX
#include <string>
#include <vector>
#include "words.h"
using namespace std;

static const int  LIMIT  = 2000000000;
/*************************************************************************
 * learned
 *
 * Tells interested parties what you learned.
 *
 * Use one or more calls to out(...), or else use the whatIlearned
 * script and do the following:
 *
 *   Words words = {
 *   #include "whatIlearned.inc"
 *   nl};
 *   cout << words;
 *************************************************************************/
void learned()
{
   cout << "\tPrime generation takes a lot of memory. Working with such big\n"
        << "arrays can be tricky to do. Dynamic memory allocation seems to be\n"
        << "the only reliable mechanism that does not sometimes result in a crash.\n"
        << "I need to do more research to see why this is so.\n\n";
   cout << "\tWorking with prime numbers can be fun. While it is fun to explore\n"
        << "using these smaller primes, it is easy to gain an appreciation for\n"
        << "just how effective the RSA cryptography system is. The task to tackle\n"
        << "the large prime numbers required would be daunting to say the least.\n"
        << "I will say that it is easy to see why prime numbers continue to fascinate\n"
        << "mathematicians, and not just for their applications.\n\n";
   cout << "\tI ran into some trouble computing the actual sweetness. I got the\n"
        << "idea on a basic level, but I was unable to stretch further than that.\n"
        << "In the future I must be more assiduous in applying the Gersy Principle,\n"
        << "and in seeking for clarifications to potential roadblocks.\n\n";
}

/*************************************************************************
 * usage
 *
 * Tells the user how to use the program.
 *************************************************************************/
void usage(const char * programName)
{
  cout << "USAGE: [program] [range begin arg] [c arg]\n"
       << "e.g. " << programName << " 0 43\n\n";
}

/****************************************************************
 * genPrimes
 *
 * Generates the different primes
 ****************************************************************/
void genPrimes(bool primes[])
{
   // fill
   for (int i = 0; i < LIMIT; i++)
   {
      primes[i] = i % 2;
   }
   primes[2] = true;
   // cross out non primes
   int prime = 3;
   int mult;
   int product;
   for(; prime < LIMIT; prime++)
   {
      // go to next prime
      while(!primes[prime] && prime < LIMIT)
      {
         prime++;
      }
      product = 1;
      // cancel multiples
      for(mult = prime; product < LIMIT && product > 0; mult++)
      {
         primes[product] = false;
         product = prime * mult;
      }
   }
}

/****************************************************************
 * f
 *
 * Polynomial function used in sweetnessEuler example.
 ****************************************************************/
int f(int x, int C)
{
   return abs((x * x) + x + C);
}

/****************************************************************
 * sweet
 *
 * Plugs in values in the range and checks the output for primes.
 ****************************************************************/
bool sweet(const int start, const int c, bool primes[])
{
   int primeCount = 0;
   for (int i = start; i < start + 10000; i++)
   {
      int n = f(i, c);
      if (primes[n])
      {
         primeCount++;
      }
   }
   // basic sweetness. I could not figure out the proper way to calculate sweetness
   cout << "Found " << primeCount << " primes out of 10000.\n"
        << "Basic sweetness of " << (float)primeCount/10000.00 << endl;
}

/****************************************************************
 * run
 *
 * Drives the sweetness search.
 ****************************************************************/
void run(vector<string> args)
{
   // correct use of the program
   if (args.size() == 2)
   {
      // get user's input
      int start = atoi(args[0].c_str());
      int c = atoi(args[1].c_str());
      
      // generate the primes
      bool * primes = new bool[LIMIT];
      genPrimes(primes);
      
      // compute the sweetness
      sweet(start, c, primes);
      
      // clean up
      delete [] primes;
   }
   else
   {  
      // show user how to properly use the program
      usage("sweetness");
   }
}
