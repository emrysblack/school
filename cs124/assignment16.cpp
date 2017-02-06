/***********************************************************************
* Program:
*    Assignment 16, Ten Grades
*    Brother Helfrich, CS124
* Author:
*    Brady Field
* Summary: 
*    Prompts for ten grades and then displays the average of the grades
*    
*    Estimated:  1.0 hrs   
*    Actual:     1.0 hrs
*      Getting the array reference correct
************************************************************************/

#include <iostream>
using namespace std;

/***********************************************************************
* Prompts user for 10 grades to fill the array
************************************************************************/
void getGrades(int grades[], int numGrades)
{
   // fill each grade in the array
   for (int arrayNum = 0; arrayNum < numGrades; grades[arrayNum++ ])
   { 
      cout << "Grade " << arrayNum + 1 << ": ";
      cin >> grades[arrayNum];
   }
}

/***********************************************************************
* takes all grades and returns the average of grades
************************************************************************/
int averageGrades(int grades[], int numGrades)
{
   int sumGrades = 0;
   for (int arrayNum = 0; arrayNum < numGrades;
        sumGrades += grades[arrayNum++ ])
      ;
   return (sumGrades / numGrades); // return average of grades
}

/**********************************************************************
* Sets up the array then calls functions to fill the array and
* compute the average. Then displays the resulting average
***********************************************************************/
int main()
{
   int numGrades = 10;
   int grades[];
   
   getGrades(grades, numGrades);
   int averageGrade = averageGrades(grades, numGrades);

   cout << "Average Grade: "
        << averageGrade
        << "%\n";
   
   return 0;
}
