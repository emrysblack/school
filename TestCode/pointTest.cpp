// test for pointers and memory allocation
#include <iostream>
using namespace std;

int main()
{
   char *text = NULL;
   int num = 0;
   cout << "Enter num letters to get: ";
   cin >> num;
   cin.ignore();
   
  
   text = new (nothrow) char[num + 1];
   if (text == NULL)
   {
      cout << "Allocation Error!\n";
   }
   else
   {
      cout << "Enter text: ";
      cin.getline(text, num + 1);
      cout << text << endl;
      delete [] text;
   }
   
   
   return 0;
}
