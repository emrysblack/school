// compile with: g++ -o 3x+1conjecture 3x+1conjecture.cpp -lntl

#include <iostream>
#include <cstdlib>
#include <NTL/ZZ.h>

NTL_CLIENT

const ZZ ZERO = to_ZZ(0);
const ZZ ONE = to_ZZ(1);
const ZZ BIG_INTEGER = to_ZZ("7194898723259873456987340698308962983739586724987345982634592783495872394857932745987234958");

ZZ highestHigh = ONE;
ZZ currentStep = ONE;

ZZ threeXplusOne(ZZ x)
{
   ZZ result;

   if (x % 2 == ZERO)
   {
      result = x / 2;
   }
   else
   {
      result = x * 3 + 1;
   }
   cout << "At step " << currentStep
        << ", result is " << result << endl;

   return result;
}

bool testConjecture(ZZ x)
{
   ZZ result = x;
   while (result != ONE)
   {
      if (result > highestHigh)
      {
         highestHigh = result;
      }
      result = threeXplusOne(result);
      currentStep++;
   }
   return (result == ONE);
}

int main(int argc, const char* argv[])
{
   if (argc < 2)
   {
      cerr << "Usage: " << argv[0] << " n\n";
      cerr << "E.g., " << argv[0] << " ";
      cerr << BIG_INTEGER << endl;
      return 1;
   }
   else
   {
      ZZ x = to_ZZ(1);
      ZZ upperLimit = to_ZZ(argv[1]);
      for (; x <= upperLimit; x++)
      {
         if (testConjecture(x))
         {
           // cout << "The conjecture holds for "
           //      << argv[1] << ".\n";
           // cout << "The highest it reached: "
           //      << highestHigh << ".\n";
         }
         else
         {
            cerr << "Conjecture failed for " << x << endl;
            break;
         }
      }
      return 0;
   }
}
