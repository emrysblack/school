/*************************************************************************
 * Exploring cliques and anti-cliques in graphs.
 *************************************************************************/
#include <cstdlib>
#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

typedef unsigned int uint;

/*************************************************************************
 * Function prototypes
 *************************************************************************/
void usage(const char *);
bool checkCliqueOrAntiClique(const char* fileName, bool anti,
                             vector<uint>& vertices);

/*************************************************************************
 * What was learned to be implemented more granularly in awareness.cpp
 * via these 8 functions.
 *************************************************************************/
void howImasteredTheBasicTerminologyAndOperationsOfLogicSetsFunctionsAndGraphs();
void howIdemonstrateLogicalReasoningThroughSolvingProblems();
void howIinterpretedTheMeaningOfMathematicalStatementsInTheContextOfRealWorldApplications();
void howIdiscernedBetweenEffectiveAndIneffectiveApproachesToProblemSolving();
void howIsolvedProblemsUsingLimitedOrConstrainedResources();
void howIsynthesizedNewProblemSolvingConceptsByPuttingOldConceptsTogetherInNovelWays();
void howIrecognizedTheRelativeImportanceOfDifferentElementsOfAComputerScienceProblem();
void howIknowHowDiscreteMathematicsAppliesToAllPartsOfComputerScience();

void learned()
{
   howImasteredTheBasicTerminologyAndOperationsOfLogicSetsFunctionsAndGraphs();

   howIdemonstrateLogicalReasoningThroughSolvingProblems();

   howIinterpretedTheMeaningOfMathematicalStatementsInTheContextOfRealWorldApplications();

   howIdiscernedBetweenEffectiveAndIneffectiveApproachesToProblemSolving();

   howIsolvedProblemsUsingLimitedOrConstrainedResources();

   howIsynthesizedNewProblemSolvingConceptsByPuttingOldConceptsTogetherInNovelWays();

   howIrecognizedTheRelativeImportanceOfDifferentElementsOfAComputerScienceProblem();

   howIknowHowDiscreteMathematicsAppliesToAllPartsOfComputerScience();
}

/*************************************************************************
* Outputs results with a minimum of repetitiveness.
*************************************************************************/
void outputResults(const char* fileName, bool does,
                   bool anti, vector<uint>& vertices)
{
   cout << "The graph specified in " << fileName << endl
        << (does ? "does" : "DOES NOT")
        << " contain a"
        << (anti ? "n anti-" : " ")
        << "clique of size "
        << vertices.size()
        << " with vertices\n";
   for (int i = 0; i < vertices.size(); i++)
   {
      cout << vertices[i] << " ";
   }
   cout << endl << endl;
}

/**************************************************************
 * main looks at its command-line parameters.
 * If none, it calls two functions in order, namely
 *   learned
 *   usage
 * Otherwise it parses the command-line and calls two other
 * functions (checkCliqueOrAntiClique and outputResults)
 * with those parsed parameters.
 ***************************************************************/
int main(int argc, const char* argv[])
{
   if (argc == 1)
   {
      learned();
      usage(argv[0]);
   }
   else if (argc >= 2)
   {
      const char* fileName = argv[1];
      vector<uint> vertices;
   
      bool anti = false;
      bool gotWhich = false;

      for (int i = 2; i < argc; i++)
      {
         if (strcmp(argv[i], "anti-clique") == 0)
         {
            anti = true;
            gotWhich = true;
         }
         else if (strcmp(argv[i], "clique") == 0)
         {
            anti = false;
            gotWhich = true;
         }
         else if (gotWhich)
         {
            int n = atoi(argv[i]);
            vertices.push_back(n);
         }
      }

      outputResults(fileName,
                    checkCliqueOrAntiClique(fileName, anti, vertices),
                    anti, vertices);
   }
   return 0;
}   
