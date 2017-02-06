/**********************************************************************
* Program:
*    Homework 18, Merge with LL 
*    Brother Twitchell, CS235
* Author:
*    Brady Field
* Summary: 
*    Uses heap sort algorithm to sort values and output result
***********************************************************************/

#include <iostream>
#include <fstream>
#include <list>
using namespace std;

/**********************************************************************
 * sorts with merge sort
 **********************************************************************/
void mergeSort(list < int > &myList)
{
   list < int > a;
   list < int > b;
   list < int > ::iterator j;
   int temp; // stores number for comparison
   bool done = false;
   while (!done)
   {
      j = myList.begin();
      
      // split file
      temp = *j;
      a.push_back(temp); // insert first element
      j++;
      while (*j >= temp and j != myList.end())
      {
         temp = *j;
         a.push_back(temp);
         j++;
      }
      if (j != myList.end())
      {
         temp = *j;
         b.push_back(temp);
         j++;
         while (*j >= temp and j != myList.end())
         {
            temp = *j;
            b.push_back(temp);
            j++;
         }
      }
      // merge lists
      if (b.size() != 0) // only merge if not sorted
      {
         list < int > ::iterator k = a.begin(); // reads items from a
         list < int > ::iterator l = b.begin(); // reads items from b
         j = myList.begin(); // used to replace contents
            
         for (int m = 0; m < (a.size() + b.size()); m++)
         {
            if (k != a.end() and l != b.end())
            {
               if (*k < *l)
               {
                  *j = *k;
                  k++;
                  j++;
               }
               else
               {
                  *j = *l;
                  l++;
                  j++;
               }
            }
            else if (k == a.end())
            {
               *j = *l;
               l++;
               j++;
            }
            else if (l == b.end())
            {
               *j = *k;
               k++;
               j++;
            }
         }            
      }
      else
         done = true;
      a.clear();
      b.clear();
   }
}

/**********************************************************************
 * Opens file and sorts it
 **********************************************************************/
int main(int argc, char** argv)
{
   if (argc < 2)
      cout << "ERROR: must specify file name\n";
   else
   {
      ifstream fin(argv[1]);
      if (fin.fail())
         cout << "ERROR: could not open file " << argv[1] << endl;
      else
      {
         list < int > myList;
         int input;
         while (!fin.eof())
         {
            fin >> input;
            if (fin.good())
               myList.push_front(input);
         }
         fin.close();
         mergeSort(myList);
         
         // display
         for (list < int > ::iterator i = myList.begin(); 
              i != myList.end(); i++)
            cout << *i << " ";
         cout << endl;
      }
   }
   return 0;
}