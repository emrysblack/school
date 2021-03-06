// test for my deque container
#include <iostream>
#include <string>
#include "deque.h"
using namespace std;

const int MAX = 10;

int main(int argc, char** argv)
{
   Deque <string> deque;
   string names[] = {"Charles 0", "Charles 1", "Charles 2",
                     "Charles 3", "Charles 4"};
   for (int i = 0; i < MAX / 2; i++)
   {   
      cout << "pushing front\n";
      deque.push_front(names[i]);   
   }
   
   for (int i = 0; i < MAX / 2; i++)
   {   
      cout << "pushing back\n";
      deque.push_back(names[i]);
   }
   try
   {
   deque.pop_front();
   deque.pop_back();
   deque.pop_back();
   deque.pop_back();
   deque.pop_back();
   deque.pop_back();
   Deque <string> deque1(deque);
   Deque <string> deque2;
   deque2 = deque;
   //deque2.clear();
   deque.display();
   deque1.display();
   deque2.display();
   }
   catch (const char * e)
   {
      cout << e << endl;
   }
   cout << "Full? " << (deque.full() ? "yes" : "no") << endl;
   cout << "Empty? " << (deque.empty() ? "yes" : "no") << endl;
   
   return 0;
}
