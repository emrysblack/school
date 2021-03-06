// test for binary search tree
#include <iostream>
#include "bst.h"
using namespace std;

int main()
{
   BST<int> tree;
   /* tree.insert(5);
   tree.insert(3);
   tree.insert(2);
   tree.insert(1);
   tree.insert(4);
   tree.insert(8);
   tree.insert(7);
   tree.insert(6);
   tree.insert(9); */
   BST<int> tree1(tree);
   tree.insert(10);   

/*    cout << "infix: ";
   tree1.infix();
   cout << endl;
   cout << tree1.size() << endl;
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
   cout << endl; */
cerr << "hi\n";
   // iterator
   for(BST<int>::Iterator it = tree.begin(); it != tree.end(); it++)
   {
      cout << *it << " ";
   }
   cout << endl;
   for(BSTIterator<int> rit = tree.rbegin(); rit != tree.rend(); rit--)
   {
      cout << *rit << " ";
   }
   cout << endl;

   tree1.remove(tree1.find(8));

   cout << "level: ";
   tree1.level();
   cout << endl;
   cout << tree1.size() << endl << endl;
   tree1.clear();
   cout << endl;
   tree1.insert(9);
   tree1.insert(10);
   tree1.insert(3);
   tree1.insert(1);
   tree1.insert(7);
   tree1.insert(8);
   tree1.insert(4);
   tree1.insert(5);
   tree1.insert(6);
   cout << "level: ";
   tree1.level();
   cout << endl;
   cout << tree1.size() << endl << endl;
   tree1.remove(tree1.find(3));
   cout << "level: ";
   tree1.level();
   cout << endl;
   cout << tree1.size() << endl << endl;
   tree1 = tree;
   cout << "size: " << tree1.size()
        << (tree1.empty()? " empty\n" : " not empty\n");
   cout << "size: " << tree.size()
        << (tree.empty()? " empty\n" : " not empty\n");
   return 0;
}
