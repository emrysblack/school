// test for red-black tree
#include <iostream>
#include "redBlack.h"
using namespace std;

int main()
{
   RBTree<int> tree;
   // tree.insert(1);
   // tree.insert(2);
   // tree.insert(3);
   // tree.insert(4);
   // tree.remove(tree.find(4));
   
   // tree.insert(10);
   // tree.insert(8);
   // tree.insert(12);
   // tree.insert(6);
   // tree.insert(14);
   // tree.insert(4);
   // tree.insert(16);
   // tree.insert(2);
   // tree.insert(18);
   // tree.insert(0);
   // tree.insert(20);

   // tree.insert(7);

   tree.insert(0);
   tree.insert(1);
   tree.insert(2);
   tree.insert(3);
   tree.insert(4);
   tree.insert(5);
   tree.insert(6);
   tree.insert(7);
   tree.insert(8);
   tree.insert(9);
   // tree.insert(20);

   // show tree
   cout << "infix: ";
   tree.infix();
   cout << endl;

   cout << "prefix: ";
   tree.prefix();
   cout << endl;

   cout << "postfix: ";
   tree.postfix();
   cout << endl;

   cout << "level: ";
   tree.level();
   cout << endl;

   // tree.remove(tree.find(14));
   // tree.remove(tree.find(16));
   // tree.remove(tree.find(18));
tree.remove(tree.find(0));
   // show tree
   cout << "infix: ";
   tree.infix();
   cout << endl;

   cout << "prefix: ";
   tree.prefix();
   cout << endl;

   cout << "postfix: ";
   tree.postfix();
   cout << endl;

   cout << "level: ";
   tree.level();
   cout << endl;

   return 0;
}
