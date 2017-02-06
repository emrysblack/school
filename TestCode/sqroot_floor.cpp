// test for a simple sqrt algorithm
#include <iostream>
using namespace std;

int main()
{
   double num;
   int rootFloor;

   do
   {
      cout << "Enter the number to find the root: ";
      cin >> num;
   } while (num < 0);
   
   // compute the root
   double big = num;
   double small = 0;
   while ((int)big != (int)small)
   {
      // take average
      big = (big + small) / 2;
      small = num / big;
   }

   rootFloor = big;
   // display result
   cout << "The Square root of "
        << num << " floored is " << rootFloor << endl
        << rootFloor << " squared is "
        << rootFloor * rootFloor << endl;
   return 0;
}
