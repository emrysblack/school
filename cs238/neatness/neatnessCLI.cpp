/***********************************************************************
 * Program:
 *    Exploration 5, Neatness
 *    Brother Neff, CS 238
 * Author:
 *    You
 * Summary:
 *    Boolean Network building and simulating.
 *
 ***********************************************************************/

#include <iostream>
#include <string>
using namespace std;

/*************************************************************************
 * What was learned to be implemented more granularly in neatness.cpp
 * via these 9 functions.
 *************************************************************************/
void howICategorizedThePatternsIObserved();
void howIMasteredTheBasicTerminologyAndOperationsOfBooleanLogicAndGatingNetworks();
void howIDemonstratedDiscreteMathematicalReasoningThroughSolvingProblems();
void howIDiscernedBetweenEffectiveAndIneffectiveApproachesToProblemSolving();
void howISolvedProblemsUsingLimitedOrConstrainedResources();
void howIRecognizedTheRelativeImportanceOfDifferentElementsOfAMathematicalOrComputerScienceProblem();
void howIMadeConnectionsBetweenDiscreteMathematicsAndRealWorldApplications();

void learned()
{
   cout << "\nHow I Categorized The Patterns I Observed\n\n";

   howICategorizedThePatternsIObserved();

   cout << "\nHow I Mastered The Basic Terminology And Operations\n"
        << "Of Boolean Logic And Gating Networks\n\n";

   howIMasteredTheBasicTerminologyAndOperationsOfBooleanLogicAndGatingNetworks();

   cout << "\nHow I Demonstrated Discrete Mathematical Reasoning "
        << "Through Solving Problems\n\n";

   howIDemonstratedDiscreteMathematicalReasoningThroughSolvingProblems();

   cout << "\nHow I Discerned Between Effective And Ineffective\n"
        << "Approaches To Problem Solving\n\n";

   howIDiscernedBetweenEffectiveAndIneffectiveApproachesToProblemSolving();

   cout << "\nHow I Solved Problems Using Limited Or Constrained Resources\n\n";

   howISolvedProblemsUsingLimitedOrConstrainedResources();

   cout << "\nHow I Recognized The Relative Importance Of Different Elements\n"
        << "Of A Mathematical Or Computer Science Problem\n\n";

   howIRecognizedTheRelativeImportanceOfDifferentElementsOfAMathematicalOrComputerScienceProblem();

   cout << "\nHow I Made Connections Between Discrete Mathematics\n"
        << "And Real World Applications\n\n";

   howIMadeConnectionsBetweenDiscreteMathematicsAndRealWorldApplications();
}

/*************************************************************************
 * usage
 *
 * tells the user how to use the program.
 *************************************************************************/
void usage(const char* programName);

/****************************************************************
 * getArgs
 *
 * gets command-line arguments.
 ****************************************************************/
void getArgs(int argc, char* argv[],
             int& booleanFunctionNumber,
             int& numberOfCells,
             int& numberOfSteps);

/****************************************************************
 * buildNetworkAndStartItRunning
 *
 * should do just that.
 ****************************************************************/
void buildNetworkAndStartItRunning(int booleanFunctionNumber,
                                   int numberOfCells,
                                   int numberOfSteps);

/****************************************************************
 * main looks at its command-line parameters.
 * If none, it calls two functions in order, namely
 *   learned
 *   usage
 *
 * Otherwise it calls getArgs
 * and then buildNetworkAndStartItRunning
 * to do just that.
 ****************************************************************/
int main(int argc, char* argv[])
{
   if (argc <= 1)
   {
      learned();
      usage(argv[0]);
      return 0;
   }
   else
   {
      int booleanFunctionNumber;
      int numberOfCells;
      int numberOfSteps;

      getArgs(argc, argv, booleanFunctionNumber,
              numberOfCells, numberOfSteps);
              
      buildNetworkAndStartItRunning(booleanFunctionNumber,
                                    numberOfCells, numberOfSteps);
   }

   return 0;
}
