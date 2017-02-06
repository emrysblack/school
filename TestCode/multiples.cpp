// cs124 adding multiples assignment
#include <iostream>
using namespace std;

int main()
{
   int value;
   int sum = 0;
   
   cout << "What multiples are we adding? ";
   cin >> value;

   for (int i = 0; value * i < 100; i++)
   {
      sum += value * i;
   }
   cout << "The sum of multiples of " << value << " less than 100 are: "
        << sum << endl;
   return 0;
}
