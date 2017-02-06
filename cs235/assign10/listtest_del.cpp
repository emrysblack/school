/****************************************************************
 *
 *  NAME: Brother Cameron
 *
 *  FILE: listtest_del.cpp
 *  Modifed: by Brother Ercanbrack 26 July 2006
 *
 *  PURPOSE: This program tests the Delete function of the 
 *           list class member functions.
 *
 ****************************************************************/
using namespace std;
#include "list.h"
#include <iostream>
#include <fstream>

main()
{
  List l;
  int  num;
  int  pos;
  int  n;
  ifstream infile("assign10_test1.in");

  // --- Read in linked list
  for (int i = 0; i < 10; ++i)
  {
    infile >> num;
    l.insert(num,i);
  }

  // --- Test Get_Data by outputing to screen
  n = l.getNumItems();
  for (int i = 0; i < n; ++i)
    cout << l.getData(i) << " ";
  cout << endl;

  // --- Test Delete function
  cout << "Deleting 10th item in list..." << endl;
  l.remove(9);
  n = l.getNumItems();
  for (int i = 0; i < n; ++i)
    cout << l.getData(i) << " ";
  cout << endl;

  cout << "Deleting 20th item in list (should delete 9th item)..." << endl;
  l.remove(20);
  n = l.getNumItems();
  for (int i = 0; i < n; ++i)
    cout << l.getData(i) << " ";
  cout << endl;

  cout << "Deleting 1st item in list..." << endl;
  l.remove(0);
  n = l.getNumItems();
  for (int i = 0; i < n; ++i)
    cout << l.getData(i) << " ";
  cout << endl;

  cout << "Deleting 3rd item in list..." << endl;
  l.remove(2);
  n = l.getNumItems();
  for (int i = 0; i < n; ++i)
    cout << l.getData(i) << " ";
  cout << endl;

  cout << "Deleting all but one item in list..." << endl;
  l.remove(1);
  l.remove(1);
  l.remove(1);
  l.remove(1);
  l.remove(1);
  n = l.getNumItems();
  for (int i = 0; i < n; ++i)
    cout << l.getData(i) << " ";
  cout << endl;

  cout << "Deleting one item from list..." << endl;
  l.remove(0);
  n = l.getNumItems();
  for (int i = 0; i < n; ++i)
    cout << l.getData(i) << " ";
  cout << endl;
}

