#include <iostream>
#include <cstdlib>
using namespace std;

int main()
{
   for(int i = 0; i < 100000; i++)
   {
      if (i % 100 == 0)
      {
         system("clear");
         cout << "\tLoading";
         cout << ".\n";
      }
      else if (i % 100 == 33)
      {
         system("clear");
         cout << "\tLoading";
         cout << "..\n";
      }
      else if (i % 100 == 67)
      {
         system("clear");
         cout << "\tLoading";
         cout << "...\n";
      }
      //system("clear");
   }
   return 0;
}
