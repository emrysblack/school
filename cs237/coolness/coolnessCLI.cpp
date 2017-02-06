/***************************************************************
 * Binary Predicates and Nested Quantifiers Implementation
 ***************************************************************/
#include <cstdlib>
#include <string>
using namespace std;

/***************************************************************
 * Reports on what was learned.
 ***************************************************************/
void learned();

/***************************************************************
 * Shows how to use the program.
 ***************************************************************/
void usage();

/***************************************************************
 * Runs one test, identified by its string argument.
 ***************************************************************/
void runOne(string);

/***************************************************************
 * Runs all tests.
 ***************************************************************/
void runAll();

/***************************************************************
 * main looks at its command-line parameters.
 * If none, it calls two functions in order, namely
 *   learned
 *   usage
 * Otherwise it calls runOne with each parameter, with "all" as
 * a special case. If there is only "all" then it calls runAll.
 ***************************************************************/
int main(int argc, const char* argv[])
{
   if (argc == 1)
   {
      learned();
      usage();
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
