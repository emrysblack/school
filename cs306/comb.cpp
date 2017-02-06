// test for combinations using recursion, this should be transferable to LISP...
#include <iostream>
#include <vector>
using namespace std;

vector<string> elements;
vector<string> combination;

// show resulting combo
void pretty_print(const vector<string>& v)
{
   static int count = 0;
   cout << "combination no " << (++count) << ": [ ";
   for (int i = 0; i < v.size(); ++i)
   { 
      cout << v[i] << " "; 
   }
   cout << "] " << endl;
}

// uses n choose k to generate lists, stack overflow helped fix a small problem with my recursion order...
void genCombos(int offset, int k)
{
   if (k == 0)
   {
      pretty_print(combination);
   }
   else
   {
      for (int i = offset; i <= elements.size() - k; ++i)
      {
         combination.push_back(elements[i]);
         genCombos(i+1, k-1);
         combination.pop_back();
      }
   }
}

int main() 
{
   int n = 3;
   int k = 2;
   string value;
   for (int i = 0; i < n; ++i) 
   {
      cout << "enter value " << i + 1 <<": ";
      cin >> value;
      elements.push_back(value); 
   }
   genCombos(0, k);
   
   return 0;
}
