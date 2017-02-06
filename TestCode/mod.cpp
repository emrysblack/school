// test for modulus
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

int main(int argc, char ** argv)
{
   istringstream num ((string)argv[1] + " " + (string)argv[2]);
   int a;
   int b;

   num >> a >> b;

   cout << a << " mod " << b << " = " << a%b << endl;
   return 0;
}
