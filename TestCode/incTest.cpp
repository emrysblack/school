// test for incremement operator
#include <iostream>
using namespace std;

int main()
{
   // value
   int i = 3;
   int j = i++ + ++i;
   cout << "\nj = i++ + ++i: " << j << endl;

   // pointer
   i = 3;
   int *k = &i;
   j = *k++ + ++*k;
   cout << "\nj = *k++ + ++*k: " << j << endl;

   //steps
   i = 3;
   ++i;
   j = i++ + i;
   cout << "\n++i\n" << "j = i++ + i: " << j << endl;
   return 0;
}
