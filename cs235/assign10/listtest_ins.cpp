/****************************************************************
 *
 *  NAME: Brother Cameron
 *
 *  FILE: list_test.cpp
 *
 *  PURPOSE: This program tests the list class member functions
 *
 ****************************************************************/
using namespace std;
#include"list.h"
#include <iostream>
#include <fstream>

main()
{
  List l;
  int  num;
  int  pos;
  int  n;
  ifstream infile("assign10_test2.in");

  infile >> num;
  cout << "Inserting " << num << " at beginning of an empty list..." << endl;
  l.insert(num,0);

  infile >> num;
  cout << "Inserting " << num << " at beginning of an existing list..." << endl;
  l.insert(num,0);

  infile >> num;
  cout << "Inserting " << num << " at end of an existing list..." << endl;
  l.insert(num,5);

  infile >> num;
  cout << "Inserting " << num << " into the middle of an existing list..." << endl;
  l.insert(num,1);


  
  // --- Test Get_Data
  cout << "Testing Get_Data..." << endl;
  n = l.getNumItems();
  for (int i = 0; i < n; ++i)
    cout << "Postion " << i << " contains " << l.getData(i) << endl;
}

