#include <iostream>
#include "map.h"
using namespace std;

int main()
{
   Map<int, int> map;
   map[0] = 1;
   map[0] = 3;
   cout << map[0] << endl;
   return 0;
}
