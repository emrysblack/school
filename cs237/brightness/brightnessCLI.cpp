/*************************************************************************
 * Searching to solve a pigeonhole principle problem.
 *************************************************************************/
#include <cstdlib>
#include <string>
using namespace std;

/*************************************************************************
 * Function prototypes
 *************************************************************************/
void usage(const char *);
void runAll();
void runOne(string);

void whatIthinkAboutTheEssayInGeneral();
void whatIthinkAboutTheCertaintyNotChanceFeatureOfThePigeonholePrinciple();
void whatIthinkAboutThePhilosophicalAspectOfThePigeonholePrinciplePerPage41();
void howMyDiscussionWithAnonClassmateWent();
void howIgrappledWithTheProblemAtTheBottomOfPage40();

int calculateNumberOfPossibleInitialsIncludingMiddleInitialIfAny(
   int howManyCharactersAreInTheAlphabet);

string pigeonholeFromPigeon(string pigeonRepresentedAsApersonWithTraits);

/*************************************************************************
 * A more granular report on what was learned.
 *
 * The howIgrappledWithTheProblemAtTheBottomOfPage40 function
 * should make use of the two non-void functions declared above.
 *************************************************************************/
void learned()
{
   whatIthinkAboutTheEssayInGeneral();
   whatIthinkAboutTheCertaintyNotChanceFeatureOfThePigeonholePrinciple();
   whatIthinkAboutThePhilosophicalAspectOfThePigeonholePrinciplePerPage41();
   howMyDiscussionWithAnonClassmateWent();
   howIgrappledWithTheProblemAtTheBottomOfPage40();
}

/**************************************************************
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
      usage(argv[0]);
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
