// test for itoa
#include <iostream>
using namespace std;

void convert(char * a, int b)
{
   cout << "digits: " << b/ 10 + 1 << endl;
   for (int i = 0; i < 1; i++)
   {     
      a[0] = '0' + b % 10;
      b /= 10;
   }
}
int main()
{
   int a;
   int b;
   char c;
   char d[20];

   cout << "Enter a number: ";
   cin >> a;
   cout << "Enter another number: ";
   cin >> b;
   
   convert(&c,a);
   convert(d,b);
   
   cout << "r: " << c << " " << "c: " << d << endl;
   return 0;
}
