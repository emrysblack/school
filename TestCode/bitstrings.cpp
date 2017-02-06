// test for bitstring generation

#include <iostream>
#include <string>
#include <vector>
using namespace std;

// works recursively to simplify the problem
vector<string> generateBitstrings(int n)
{
   vector<string> list;
   if (n == 1)
   {
      list.push_back("0");
      list.push_back("1");
   }
   else
   {
      vector<string> temp = generateBitstrings(n - 1);
      for(int i = 0; i < temp.size(); i++)
      {
         list.push_back(temp[i] + "0");
         list.push_back(temp[i] + "1");
      }
   }
   
   return list;
}

int main()
{
   int n;
   // prompt for n
   cout << "Enter desired length of bitstrings: ";
   cin >> n;
   vector<string> bitstrings = generateBitstrings(n);

   // display the list
   for (int i = 0; i < bitstrings.size(); i++)
   {
      cout << bitstrings[i] << endl;
   }
   return 0;
}
