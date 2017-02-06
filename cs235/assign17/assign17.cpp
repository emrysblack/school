/***********************************************************************
* Program:
*    Homework 17, Heap Sort 
*    Brother Twitchell, CS235
* Author:
*    Brady Field
* Summary: 
*    Uses heap sort algorithm to sort values and output result
************************************************************************/

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

void heapSort (vector < int > &myVector);
void heapify (vector < int > &myVector, int max);

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
         vector < int > myVector;
         int input;
         while (!fin.eof())
         {
            fin >> input;
            if (fin.good())
            {
               myVector.push_back(input);
            }
         }
         fin.close();
         heapSort(myVector); // sort
         
         // display
         for (int i = 0; i < myVector.size(); i++)
            cout << myVector[i] << " ";
         cout << endl;
      }
   }
   return 0;
}

/**********************************************************************
 * sorts vector using a heap sort algorithm
 **********************************************************************/
void heapSort(vector < int > &myVector)
{
   int max = myVector.size() - 1; // index for heap
   int temp; // used for swap

   while (max > 0)
   {
      heapify(myVector, max);
  
      // swap first and last elements, take sorted end off
      temp = myVector[0];
      myVector[0] = myVector[max];
      myVector[max] = temp;
      max--;
   }
}

/**********************************************************************
 * sorts into tree so that large value is root
 **********************************************************************/
void heapify(vector < int > &myVector, int max)
{
   int temp;
   int left;
   int right;
   int parent;

   // get last parent in tree
   if (max % 2 == 0)
      parent = (max - 2) / 2;

   else
   {
      parent = (max - 1) / 2; // has no right child
      left = parent * 2 + 1;
      // process left and go to next parent
      if (myVector[parent] < myVector[left])
      {
         temp = myVector[parent];
         myVector[parent] = myVector[left];
         myVector[left] = temp;
      }
      parent--;
   }
   while (parent > -1)
   {
      left = parent * 2 + 1;
      right = parent * 2 + 2;
      // process right side
      if (myVector[parent] < myVector[right])
      {
         temp = myVector[parent];
         myVector[parent] = myVector[right];
         myVector[right] = temp;
      }
      // process left side
      if (myVector[parent] < myVector[left])
      {
         temp = myVector[parent];
         myVector[parent] = myVector[left];
         myVector[left] = temp;
      }
      parent--;
   }
}
