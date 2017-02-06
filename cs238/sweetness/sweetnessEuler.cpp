/***********************************************************************
 * Program:
 *    Exploration 1, Sweetness
 *    Brother Neff, CS 238
 * Author:
 *    You
 * Summary:
 *    Prime Generation Program, exploring a probability connection.
 ***********************************************************************/
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <streambuf>
#include <iomanip>
#include <sstream>
#include <vector>
using namespace std;

int f(int x, int C)
{
   return abs((x * x) + x + C);
}

bool isPrime(int n)
{
   if (n == 2)
   {
      return true;
   }
   else if (n % 2 == 0)
   {
      return false;
   }
   else
   {
      int limit = (int) ceil(sqrt(n));
      for (int i = 3; i <= limit; i += 2)
      {
         if ((n % i) == 0)
         {
            return false;
         }
      }
      return true;
   }
}

/****************************************************************
 * Main loops for x from -40 to 39 computing x^2 + x + 41
 *  and printing out which values are prime.
 ****************************************************************/
int main(int argc, char* argv[])
{
   for (int x = -40; x <= 39; x++)
   {
      int v = f(x, 41);
      if (isPrime(v))
      {
         cout << "f(" << x << ") = " << v << " is prime.\n";
      }
   }

   return 0;
}

