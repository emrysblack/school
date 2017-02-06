/****************************************************************
 *
 *  NAME: Brother Cameron
 *
 *  FILE: listtest_lookup.cpp
 *
 *  PURPOSE: This program tests the Lookup function of the 
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
  ifstream infile("assign10_test3.in");
  
  // --- Create list
  for (int i = 0; i < 10; ++i)
  {
    infile >> num;
    l.insert(num,i);
  }

  // --- Test Get_Data
  n = l.getNumItems();
  for (int i = 0; i < n; ++i)
    cout << "Position " << i << ": " << l.getData(i) << endl;
  cout << endl;

  // --- Test Lookup function
  num = 13;
  pos = l.lookup(num);
  cout << "Number " << num << " is in position " << pos << endl;

  num = 22;
  pos = l.lookup(num);
  cout << "Number " << num << " is in position " << pos << endl;

  num = 25;
  pos = l.lookup(num);
  cout << "Number " << num << " is in position " << pos << endl;

  num = 30;
  pos = l.lookup(num);
  cout << "Number " << num << " is in position " << pos << endl;
  
}

