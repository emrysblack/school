/***********************************************************************
* Program:
*    Assignment 18, Ten Grades in a File
*    Brother Helfrich, CS124
* Author:
*    Brady Field
* Summary: 
*    Reads ten grades from a file, displays the average of the grades,
*    and then writes grades to a new file
*
*    Estimated:  1.5 hrs   
*    Actual:     1.0 hrs
*      Not dividing by zero
************************************************************************/

#include <iostream>
#include <fstream>
using namespace std;

void readFile(int grades[], int numGrades, char fileIn[256]);
int averageGrades(int grades[], int numGrades);
void writeFile(int grades[], int numGrades, char fileOut[256]);

/**********************************************************************
* Sets up the array then calls functions to fill the array and
* compute the average. Then displays the resulting average
***********************************************************************/
int main()
{
   int numGrades = 10;
   int grades[10];
   char fileIn[256];
   char fileOut[256];

   cout << "Source file: ";
   cin >> fileIn;
   readFile(grades, numGrades, fileIn);
   int averageGrade = averageGrades(grades, numGrades);

   cout << "Average Grade: ";
   if (averageGrade > -1)
      cout << averageGrade
           << "%\n";
   else
      cout << "---%\n";
   cout << "Destination file: ";
   cin >> fileOut;
   writeFile(grades, numGrades, fileOut);
   
   return 0;
}

/***********************************************************************
* Opens a file and reads grades to fill the array
************************************************************************/
void readFile(int grades[], int numGrades, char fileIn[])
{
   // open target file
   ifstream inStream(fileIn);
   if (inStream.fail())
   {
      cout << "Input file opening failed.\n";
   }
   
   // fill each grade in the array
   for (int i = 0; i < numGrades; grades[i++ ])
      inStream >> grades[i];
   inStream.close();
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

/************************************************************************
* opens a file and writes values of grades from array to new file
*************************************************************************/
void writeFile(int grades[], int numGrades, char fileOut[])
{
   // open target file
   ofstream outStream(fileOut);
   if (outStream.fail())
      cout << "Output file opening failed\n";
   
   // write each grade in the array to file
   for (int i = 0; i < numGrades; grades[i++ ])
      outStream << grades[i] << " ";
   cout << "File written successfully\n";
   outStream.close();
}
