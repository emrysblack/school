/***********************************************************************
 * Program:
 *    Exploration 5, Neatness
 *    Brother Neff, CS238
 *
 * Author:
 *    Brady Field
 *
 * Summary:
 *    Boolean Network building and simulating.
 *
 * Note:
 *    Some of this code is uncommented --- this is deliberate.
 *
 ***********************************************************************/

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
using namespace std;

/*******************************************************************
 * A class that represents a Wire with a current and a new boolean
 * value.  The new value is set by the operation of a Cell, and it
 * will become the current value after being updated, which typically
 * happens right before showing (outputting) the value.
 *******************************************************************/
class Wire
{
private:
   bool mValue;
   bool mNewValue;
   bool mUseStarAndBlank;

public:
   /****************************************************************
    * Constructs a new wire instance with a default value (false).
    ****************************************************************/
   Wire()
   {
      setValue(false);
      setNewValue(false);
      setUseStarAndBlank(true);
   }

   /****************************************************************
    * Constructs a new wire instance with a given value.
    ****************************************************************/
   Wire(bool pValue, bool pUseStarAndBlank = true)
   {
      setValue(pValue);
      setNewValue(false);
      setUseStarAndBlank(pUseStarAndBlank);
   }

   /******************************
    * Gets this wire's value.
    *******************************/
   bool getValue() const { return mValue; }

   /******************************
    * Gets this wire's new value.
    *******************************/
   bool getNewValue() const { return mNewValue; }

   /******************************
    * Sets this wire's value.
    *******************************/
   void setValue(bool pValue) { mValue = pValue; }

   /******************************
    * Sets this wire's new value.
    *******************************/
   void setNewValue(bool pNewValue) { mNewValue = pNewValue; }

   /******************************
    * Sets this wire's value to its new value.
    *******************************/
   void setValueToNew() { mValue = mNewValue; }

   /******************************
    * Gets this wire's display mode.
    *******************************/
   bool isUsingStarAndBlank() const
   {
      return mUseStarAndBlank;
   }

   /******************************
    * Sets this wire's display mode.
    *******************************/
   void setUseStarAndBlank(bool pUseStarAndBlank)
   {
      mUseStarAndBlank = pUseStarAndBlank;
   }

   /****************************************************
    * Gets the character representing this wire's value.
    ****************************************************/
   char getCharacterRepresentingValue() const
   {
      return
         (isUsingStarAndBlank() ?
          (getValue() ? '*' : ' ') :
          (getValue() ? '1' : '0'));
   }
};

/****************************************************************
 * Outputs a Wire.
 ****************************************************************/
ostream& operator<<(ostream& os, const Wire& w)
{
   os << w.getCharacterRepresentingValue();
   return os;
}

/****************************************************************
 * A class representing a Boolean function of degree 3.
 ****************************************************************/
class BooleanFunction3
{
protected:
   bool mValues[8];
public:
   BooleanFunction3()
   {
      for (int i = 0; i < 8; i++)
      {
         mValues[i] = false;
      }
   }

   BooleanFunction3(int values)
   {
      populate(values);
   }

   bool evaluate(bool p1, bool p2, bool p3)
   {
      int i = 0;
      if (p3)
      {
         i |= 1;
      }
      if (p2)
      {
         i |= 2;
      }
      if (p1)
      {
         i |= 4;
      }
      return mValues[i];
   }

   void populate(int values)
   {
      int i = 0;
      while (values > 0)
      {
         mValues[i++] = ((values & 1) == 1);
         values /= 2;
      }
   }
};

/****************************************************************
 * A Cell evaluating a boolean function of degree 3.
 ****************************************************************/
class Cell
{
public:
   /****************************************************************
    * Constructs a new Cell instance with a pointer to a Boolean
    * Function of degree 3, and three wires.
    *
    * This merely has the side effect of computing the boolean
    * function on the three wire inputs, storing the result in the
    * middle (output) wire.
    ****************************************************************/
   Cell(BooleanFunction3 * bfp, Wire& x, Wire& y, Wire& z)
   {
      y.setNewValue(bfp->evaluate(
         x.getValue(), y.getValue(), z.getValue()));
   }
};

/****************************************************************
 * getArgs gets command-line arguments.
 ****************************************************************/
void getArgs(int argc, char* argv[], int& booleanFunctionNumber,
             int& numberOfCells, int& numberOfSteps)
{
   // TODO 1: get program input a better way.
   numberOfCells = 100;
   numberOfSteps = 0; // use as a check
   assert(argc > 1);
   for(int i = 1; i < argc; i++)
   {
      switch(argv[i][0])
      {
         case 'f':
            // function number
            booleanFunctionNumber = atoi(&argv[i][2]);
            break;
         case 'c':
            // number of cells
            numberOfCells = atoi(&argv[i][2]);
            break;
         case 's':
            // number of steps
            numberOfSteps = atoi(&argv[i][2]);
            break;
         default:
            // unknown parameter
            cout << "ERROR: unknown parameter\n";
            break;
      }
   }
   numberOfSteps = (numberOfSteps ? numberOfSteps : numberOfCells);
}

/****************************************************************
 * updates and displays the values.
 ****************************************************************/
void updateAndShow(Wire wires[], int numberOfCells)
{
   for (int i = 0; i < numberOfCells; i++)
   {
      wires[i].setValueToNew();
      cout << wires[i];
   }
   cout << endl;
}

/****************************************************************
 * buildNetworkAndStartItRunning should do just that.
 ****************************************************************/
void buildNetworkAndStartItRunning(int booleanFunctionNumber,
                                   int numberOfCells,
                                   int numberOfSteps)
{
   // TODO 2: create numberOfCells Wires.
   Wire * wires = new Wire[numberOfCells];
   // TODO 3: set to true the new value of the middle-most Wire
   // (the middle of the whole array, *NOT* the middle wire of each cell).
   wires[numberOfCells/2].setNewValue(true);
   // TODO 4: update values to new values and show (output) all Wires.
   updateAndShow(wires, numberOfCells);
   // TODO 5: create a BooleanFunction3 given the booleanFunctionNumber.
   BooleanFunction3 function(booleanFunctionNumber);
   // TODO 6: iterate TODO 7 and TODO 8 for numberOfSteps steps.
   for(int i = 0; i < numberOfSteps; i++)
   {
      // TODO 7: create the network of Cells evaluating the BooleanFunction3
      // and connect them to the already-created Wires in the desired fashion.
      for(int j = 0; j < numberOfCells - 2; j++)
      {
         Cell(&function, wires[(j  + numberOfCells - 1) % numberOfCells], wires[j % numberOfCells], wires[(j + 1) % numberOfCells]);
      }
      // TODO 8: update values to new values and show (output) all wires.
      updateAndShow(wires, numberOfCells);
   }
   delete [] wires;
}

/****************************************************************
 * For reporting on what was learned.
 ****************************************************************/
void howICategorizedThePatternsIObserved()
{
}

void howIMasteredTheBasicTerminologyAndOperationsOfBooleanLogicAndGatingNetworks()
{
}

void howIDemonstratedDiscreteMathematicalReasoningThroughSolvingProblems()
{
}

void howIDiscernedBetweenEffectiveAndIneffectiveApproachesToProblemSolving()
{
}

void howISolvedProblemsUsingLimitedOrConstrainedResources()
{
   cout << "First, the type of problem needs to be identified.\n";
   cout << "Second, design happens at a whiteboard using a simple example.";
   cout << "Third, the design is implemented in code and tested using various examples.\n";
   cout << "Finally, the design is revisited to work for more complex data sets if a flaw was found.\n";
   cout << "Then starting at the second step, the process is repeated until the flaws are all fixed, or the code is optimized.\n";
}

void howIRecognizedTheRelativeImportanceOfDifferentElementsOfAMathematicalOrComputerScienceProblem()
{
}

void howIMadeConnectionsBetweenDiscreteMathematicsAndRealWorldApplications()
{
}

/*************************************************************************
 * How to use this program to be implemented here.
 *************************************************************************/
void usage(const char* programName)
{
   cout << "USAGE: " << programName << " [options]\n";
   cout << "options: f=[function number], c=[number of cells], s=[number of steps]\n";
   cout << "e.g. " << programName << " f=22 c=100 s=50\n";
}

