// test for conditionals
#include <iostream>
using namespace std;

int main()
{
   bool yes = true;
   // it can return only same type on both sides, no mixing
   // if inline on the cin
   cout << (yes? "true" : "false") << endl;

   // for mixing types, the cout is the return, so
   // can't do inline
   (yes)? cout << 1 << endl : cout << "---" << endl;
   return 0;
}
