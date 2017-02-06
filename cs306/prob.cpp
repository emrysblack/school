// test for recursive probabilities
#include <iostream>
using namespace std;

float P(float p, int i, int j)
{
   if (i == 0)
      return 1;
   else if (j == 0)
      return 0;

   return p * P(p, i - 1, j) + (1 - p) * P(p, i, j - 1);
}

int main()
{
   float p;
   int i, j;
   cout << "Enter p, i, and j: ";
   cin >> p >> i >> j;
   cout << "Final P: " << P(p, i, j) << endl;
   return 0;
}