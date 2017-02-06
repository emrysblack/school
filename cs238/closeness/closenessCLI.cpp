/***********************************************************************
 * Program:
 *    Exploration 3, Closeness
 *    Brother Neff, CS 238
 * Author:
 *    You
 * Summary:
 *    Exploring an implementation of a representation of Relations.
 *************************************************************************/
#include <cstdlib>
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
 * runOne
 *
 * is a global function declared here and implemented in the
 * closeness.cpp file.
 *
 * It serves as the interface between the CLI and the Relation class.
 *************************************************************************/
void runOne(string file);

/**************************************************************
 * main looks at its command-line parameters.
 * If none, it calls two functions in order, namely
 *   learned
 *   usage
 * Otherwise it calls runOne with each command-line parameter,
 * each naming a file to test.
 ***************************************************************/
int main(int argc, const char* argv[])
{
   if (argc == 1)
   {
      learned();
      usage(argv[0]);
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
