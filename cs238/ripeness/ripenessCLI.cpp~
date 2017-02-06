/***********************************************************************
 * Program:
 *    Exploration 4, Ripeness
 *    Brother Neff, CS 238
 * Author:
 *    You
 * Summary:
 *    Exploring a tree-sorting algorithm and a time-for-space
 *    tree traversal tradeoff.
 *
 ***********************************************************************/
#include <cstdlib>
#include <iostream>
#include <string>
using namespace std;

/*************************************************************************
 * learned tells what was learned.
 *************************************************************************/
void learned();

/*************************************************************************
 * usage tells how to use this program.
 *************************************************************************/
void usage(const char* programName);

/*************************************************************************
 * Tournament Sort to be implemented in ripeness.cpp
 *************************************************************************/
void tournamentSort(int array[], int size);

/*************************************************************************
 * tree Traversal IS implemented in ripeness.cpp
 *************************************************************************/
void treeTraversal(int height);

/*************************************************************************
 * Runs one test, identified by its string argument.
 *************************************************************************/
void runOne(string test)
{
   if (test == "treet")
   {
      treeTraversal(3);
   }
   else if (test == "tsort")
   {
      int array[] = {15, 6, 2, 9, 8, 0, 3, 1, 5, 4, 7, 13, 10, 11, 12, 14};
      int size = sizeof(array) / sizeof(int);

      tournamentSort(array, size);

      for (int i = 0; i < size; i++)
      {
         cout << array[i] << " ";
      }
      cout << endl;
   }
}

/*************************************************************************
 * Runs all tests.
 *************************************************************************/
void runAll()
{
   runOne("treet");
   runOne("tsort");
}

/****************************************************************
 * main looks at its command-line parameters.
 * If none, it calls two functions in order, namely
 *   learned
 *   usage
 * Otherwise it calls runOne with each parameter, with "all" as
 * a special case. If there is only "all" then it calls runAll.
 ****************************************************************/
int main(int argc, char* argv[])
{
   if (argc <= 1)
   {
      learned();
      usage(argv[0]);
      return 0;
   }
   else if ((argc == 2) &&
            ("all" == string(argv[1])))
   {
      runAll();
   }
   else
   {
      for (int i = 1; i < argc; i++)
      {
         runOne(string(argv[i]));
      }
   }

   return 0;
}
