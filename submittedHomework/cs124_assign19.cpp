/***********************************************************************
* Program:
*    Assignment 19, Letter Grade from Number Grade
*    Brother Helfrich, CS124
* Author:
*    Brady Field
* Summary: 
*    Takes an input number grade and returns a letter grade with an 
*    appropriate sign of plus, minus, or nothing at all.
*
*    Estimated:  1.0 hrs   
*    Actual:     1.5 hrs
*      never done a switch statement before
************************************************************************/

#include <iostream>
using namespace std;

char computeLetterGrade(int grade);
char computeGradeSign(int grade);

/**********************************************************************
* prompts for grade and then calls functions to return the
* corresponding letter grade with sign and displays the results
***********************************************************************/
int main()
{
   int grade;
   
   // prompt for grade
   cout << "Enter number grade: ";
   cin >> grade;

   // compute letter grade and sign
   char letterGrade = computeLetterGrade(grade);
   char gradeSign = computeGradeSign(grade);

   // display results
   cout << grade << "% is "
        << letterGrade;
   if (gradeSign != '*')
      cout << gradeSign;

   cout << endl;
   
   return 0;
}

/**********************************************************************
* takes number grade and returns appropriate letter
***********************************************************************/
char computeLetterGrade(int grade)
{
   int gradeRange = (grade / 10);
   
   switch (gradeRange)
   {
      case 10:
         return 'A';
         break;
      case 9:
         return 'A';
         break;
      case 8:
         return 'B';
         break;
      case 7:
         return 'C';
         break;
      case 6:
         return 'D';
         break;
      default:
         return 'F';
   }
            
}

/**********************************************************************
* returns appropriate sign for letter grade
***********************************************************************/
char computeGradeSign(int grade)
{
   int gradeRange = (grade / 10);
   int sign = (grade % 10);

   if ((gradeRange > 5) && (gradeRange < 9))
   {
      if (sign < 3)
         return '-';
  
      else if (sign > 6)
         return '+';
      else
         return '*';
   }
   else if (gradeRange == 9)
   {
      if (sign < 3)
         return '-';
      else
         return '*';
   }
   else
      return '*';
}