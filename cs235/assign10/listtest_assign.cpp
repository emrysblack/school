/****************************************************************
 *
 *  NAME: Brother Ercanbrack
 *
 *  FILE: assignment operator test
 *
 *  PURPOSE: This program tests the Lookup function of the 
 *           list class member functions.
 *
 *  Results should match assign10_test4.out
 ****************************************************************/
using namespace std;
#include "list.h"
#include <iostream>
#include <fstream>

main()
{
  List l;
  List newList;
  int  num;
  int  pos;
  int  n;
  ifstream infile("assign10_test4.in");
  
  // --- Create list
  for (int i = 0; i < 10; ++i)
  {
    infile >> num;
    l.insert(num,i);
    newList.insert(num,i*5000);
  }

  cout << "Original List" << endl
       << "-------------" << endl;
  
  n = l.getNumItems();
  for (int i = 0; i < n; ++i)
  {
    cout << "Position " << i << ": " << l.getData(i) << endl;
  }
  cout << endl;

  // assign original list to a new list; 
     newList = l;

  // multiply each value in the list by 10
  for (int i = 0; i < 10; ++i)
  {
     num = newList.getData(i) * 10;
     newList.remove(i);
     newList.insert(num,i);
  }

  cout << "New List" << endl
       << "--------" << endl;
  n = newList.getNumItems();
  for (int i = 0; i < n; ++i)
  {
    cout << "Position " << i << ": " << newList.getData(i) << endl;
  }
  cout << endl;

  // display original list again
  cout << "Original List" << endl
       << "-------------" << endl;
  n = l.getNumItems();
  for (int i = 0; i < n; ++i)
  {
    cout << "Position " << i << ": " << l.getData(i) << endl;
  }
  cout << endl;  
}

