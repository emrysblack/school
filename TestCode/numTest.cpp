// test for num formats
#include <iostream>
#include <bitset>
using namespace std;

int main()
{
   int a;
   int b;

   cout << "Enter a number: ";
   cin >> a;

   cout << "a in hex: " << hex << a << endl
        << "a in dec: " << dec << a << endl
        << "a in bin: " << (bitset<4>) a << endl;
   
   return 0;
}
