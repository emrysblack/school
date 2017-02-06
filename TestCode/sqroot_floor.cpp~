// test for a simple sqrt algorithm
#include <iostream>
using namespace std;

int main()
{
   double num;

   cout << "Enter the number to find the root: ";
   cin >> num;

   // compute the root
   double big = num;
   double small = 0;
   double error = .0000001;
   while (big - small > error || small - big > error)
   {
      // take average
      big = (big + small) / 2;
      small = num / big;
   }

   // display result
   cout << "The Square root of " << num << " is " << big << endl;
   cout <<  big << " squared is " << big * big << endl;
   return 0;
}
