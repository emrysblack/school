/***********************************************************************
* Program:
*    Assignment 17, Ten Grades Revisited
*    Brother Helfrich, CS124
* Author:
*    Brady Field
* Summary: 
*    Prompts for ten grades and then displays the average of the grades
*    
*    Estimated:  1.0 hrs   
*    Actual:     1.0 hrs
*      Not dividing by zero
************************************************************************/

#include <iostream>
using namespace std;

/***********************************************************************
* Prompts user for 10 grades to fill the array
************************************************************************/
void getGrades(int grades[], int numGrades)
{
   // fill each grade in the array
   for (int i = 0; i < numGrades; grades[i++ ])
   { 
      cout << "Grade " << i + 1 << ": ";
      cin >> grades[i];
   }
}

/***********************************************************************
* takes all grades and returns the average of grades
************************************************************************/
int averageGrades(int grades[], int numGrades)
{
   int sumGrades = 0;
   int notEntered = 0; // set to 0 for division counter for function
   for (int i = 0; i < numGrades; i++)
   {
      if (grades[i] < 0)
      {
         notEntered++;
      }
      else
         sumGrades += grades[i];
   }
   // return average of grades
   if (notEntered < numGrades)
      return (sumGrades / (numGrades - notEntered));
   else
      return -1;
}

/**********************************************************************
* Sets up the array then calls functions to fill the array and
* compute the average. Then displays the resulting average
***********************************************************************/
int main()
{
   int numGrades = 10;
   int grades[10];
   
   getGrades(grades, numGrades);
   int averageGrade = averageGrades(grades, numGrades);

   cout << "Average Grade: ";
   if (averageGrade > -1)
      cout << averageGrade
           << "%\n";
   else
      cout << "---%\n";
   
   return 0;
}
