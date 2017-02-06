/***********************************************************************
 * Program:
 *    Exploration 1, Sweetness
 *    Brother Neff, CS 238
 * Author:
 *    Brady Field
 * Summary:
 *    Polynomial Prime Generation, with a probability connection.
 ***********************************************************************/

#include <iostream>
#include <string>
#include <vector>
using namespace std;

/*************************************************************************
 * learned tells what was learned.
 *************************************************************************/
void learned();

/*************************************************************************
 * usage tells how to use this program.
 *************************************************************************/
void usage(const char* programName);

/****************************************************************
 * run drives the sweetness search.
 ****************************************************************/
void run(vector<string> args);

/****************************************************************
 * main looks at its command-line parameters.
 * If none, it calls two functions in order, namely
 *   learned
 *   usage
 *
 * Otherwise it calls run with the parameters recast as
 * a vector of strings.
 ****************************************************************/
int main(int argc, char* argv[])
{
   if (argc <= 1)
   {
      learned();
      usage(argv[0]);
   }
   else
   {
      vector<string> args;
      for (int i = 1; i < argc; i++)
      {
         args.push_back(string(argv[i]));
      }
      run(args);
   }

   return 0;
}
