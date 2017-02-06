// display const char * in reverse using simple recursion
#include <iostream>
using namespace std;

void displayReversed(const char * text)
{
   if (text[0])
   {
      displayReversed(text+1);
      cout << text[0];
   }
}

int main(int argc, char ** argv)
{
   for (int i = 1; i < argc; i++)
   {
      displayReversed(argv[i]);
      cout << endl;
   }
}
