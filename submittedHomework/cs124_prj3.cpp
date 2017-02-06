/***********************************************************************
* Program:
*    Project 3, Grades Program
*    Brother Helfrich, CS124
* Author:
*    Brady Field
* Summary: 
*    Displays a list of options for the user to interact with a grade
*    file created from a text file. Continues the interactions until the
*    user intentionally exits
*    Estimated:  8.0 hrs   
*    Actual:     7.5 hrs
*      figuring out how to use multidimensional arrays
************************************************************************/

#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

void getName(char fileIn[]);
bool newFile(char fileIn[]);
int computeFinalGrade(int score[], int points[], int numGrades);
char computeLetterGrade(int finalGrade);
char computeGradeSign(int finalGrade);
void changeName(char names[][256]);
void changePoints(int points[]);
void changeScore(int score[]);
void clearScore(int score[]);
bool readFile(int &numGrades, char fileIn[256], int points[], int score[],
              char names[][256]);
bool writeFile(int numGrades, char fileIn[], int points[], int score[],
               char names[][256]);
void display(int points[], int score[], int numGrades, char names[][256],
             int finalGrade, char letterGrade, char gradeSign);
void interact(int points[], int score[], int numGrades, char names[][256]);

/**********************************************************************
* Calls the functions to open file, compute grades, display and interact
* writes data to a file on exit
*
* getName(fileIn)
* readFile(numGrades, fileIn, points, score, names)
* finalGrade = computeFinalGrade(score, points, numGrades)
* letterGrade = computeLetterGrade(finalGrade)
* gradeSign = computeGradeSign(finalGrade)
* display(points, score, numGrades, names, finalGrade, letterGrade,
*         gradeSign)
* interact(points, score, numGrades, names)
* writeFile(numGrades, fileIn, points, score, names)
*
***********************************************************************/
int main()
{
   int numGrades;
   char fileIn[256];
   char fileOut[256];
   int points[100];
   int score[100];
   char names[10][256];
   int finalGrade;
   char letterGrade;
   char gradeSign;
   getName(fileIn);
   readFile(numGrades, fileIn, points, score, names);
   finalGrade = computeFinalGrade(score, points, numGrades);
   letterGrade = computeLetterGrade(finalGrade);
   gradeSign = computeGradeSign(finalGrade);
   display(points, score, numGrades, names, finalGrade, letterGrade,
           gradeSign);
   interact(points, score, numGrades, names);
   writeFile(numGrades, fileIn, points, score, names);

   return 0;
}

/**************************************************************************
* prompts for the name of the file to be opened or created
*
* PROMPT file name
* GET file name
* IF file name doesn't exist
*    newFile(fileIn)
***************************************************************************/
void getName(char fileIn[])
{
   // prompt for file
   cout << "What is the filename of the grades file? ";
   cin >> fileIn;
   
   // open target file
   ifstream fin(fileIn);

   // create new if it doesn't exist
   if (fin.fail())
      newFile(fileIn);
         
   fin.close();
}

/**************************************************************************
* creates a new file for grades if specified doesn't exist
*
* PROMPT number of grades
* GET number of grades
* WRITE number of grades
* FOR (counter = 1 to number of grades)
*    PROMPT name of item
*    GET name of item
*    WRITE name of item
*    WRITE 100
*    WRITE -1
* END
***************************************************************************/
bool newFile(char fileIn[])
{
   int numGrades;
   char name[256];
   // open target file
   ofstream fout(fileIn);
   if (fout.fail())
   {
      cout << "Output file opening failed\n";
      return 0;
   }
   
   // prompt to write grade information to file
   cout << "How many records are in the file? ";
   cin >> numGrades;
   fout << numGrades << endl;
   for (int i = 0; i < numGrades; i++)
   {
      cout << "Description for #" << i + 1 << ": ";
      cin >> name;
      fout << name << " " << 100 << " " << -1 << endl;
   }
   fout.close();
   return 1;
}

/***********************************************************************
* Opens a file and reads grades to fill the array
*
* READ number of grades
* FOR (counter = 1 to number of grades)
*    READ name of item
*    READ points possible
*    READ score earned for item
* END
************************************************************************/
bool readFile(int &numGrades, char fileIn[], int points[], int score[],
              char names[][256])
{
   // open target file
   ifstream fin(fileIn);

   // create new if it doesn't exist and re-open
   if (fin.fail())
   {
      cout << "Input file opening failed";
      return 0;
   }

   // get total number of grades
   fin >> numGrades;
   
   // fill arrays with info
   for (int i = 0; i < numGrades; i++)
   {
      fin >> names[i];
      fin >> points[i];
      fin >> score[i];
   }
   fin.close();
   return 1;
}

/************************************************************************
* opens a file and writes values of grades from array to new file
*
* WRITE number of grades
* FOR (counter = 1 to number of grades)
*    WRITE name of item
*    WRITE points possible
*    WRITE score earned for item
* END
*************************************************************************/
bool writeFile(int numGrades, char fileIn[], int points[], int score[],
               char names[][256])
{
   // open target file
   ofstream fout(fileIn);
   if (fout.fail())
   {
      cout << "Output file opening failed";
      return 0;
   }
   
   // get total number of grades
   fout << numGrades << endl;
   
   // write to file with info from arrays
   for (int i = 0; i < numGrades; points[i++ ])
   {
      fout << names[i] << " ";
      fout << points[i] << " ";
      fout << score[i] << " ";
      fout << endl;
   }
   fout.close();
   cout << "File saves successfully\n";
   return 1;
}

/***************************************************************************
* changes the name for a selected item
*
* PROMPT item number
* GET item number
* PROMPT new name
* GET new name
* SET name of item number = new name
****************************************************************************/
void changeName(char names[][256])
{
   int i;
   cout << "Which item do you want to edit? ";
   cin >> i;
   cout << "What is the new name: ";
   cin >> names[i - 1];
}

/***************************************************************************
* changes the number of points an item is worth
*
* PROMPT item number
* GET item number
* PROMPT new points
* GET new points
* SET points of item number = new points
****************************************************************************/
void changePoints(int points[])
{
   int i;
   cout << "Which item do you want to edit? ";
   cin >> i;
   cout << "What is the new points: ";
   cin >> points[i - 1];
}

/***************************************************************************
* changes the earned score for a selected item
*
* PROMPT item number
* GET item number
* PROMPT new score
* GET new score
* SET score of item number = new score
****************************************************************************/
void changeScore(int score[])
{
   int i;
   cout << "Which item do you want to edit? ";
   cin >> i;
   cout << "What is the new score: ";
   cin >> score[i - 1];
}

/***************************************************************************
* clears the score of a selected item
*
* PROMPT item number
* GET item number
* SET score of item number = -1
****************************************************************************/
void clearScore(int score[])
{
   int i;
   cout << "Which item do you want to edit? ";
   cin >> i;
   score[i - 1] = -1;
}

/***********************************************************************
* takes all scores and returns the final grade
*
* FOR (count to number of grades)
*    IF (score < 0)
*       number of grades - 1
*    ELSE
*       sum of grades = sum of grades (score * points)
*       points possible = points possible + points possible of item
* END 
* IF (number of grades > 0)
*    RETURN (sum of grades / points possible)
* ELSE
*    RETURN -1
*
************************************************************************/
int computeFinalGrade(int score[], int points[], int numGrades)
{
   int sumGrades = 0;
   int totalPoints = 0;
   int notEntered = 0; // set to 0 for division counter for function

   // calculate total points possible for items entered
   for (int i = 0; i < numGrades; i++)
   {
      if (score[i] < 0)
         notEntered++;
      else
      {
         sumGrades += (score[i] * points[i]);
         totalPoints += points[i];
      }
   }
   
   // return average of grades
   if (notEntered < numGrades)
      return (sumGrades / totalPoints);
   else
      return -1;
}

/**********************************************************************
* takes number grade and returns appropriate letter
*
*  SWITCH (grade / 10)
*     CASE 10
*     CASE 9
*        RETURN A
*     CASE 8
*        RETURN B
*     CASE 7
*        RETURN C
*     CASE 6
*        RETURN D
*     DEFAULT
*        RETURN F
************************************************************************/
char computeLetterGrade(int finalGrade)
{
   switch (finalGrade / 10)
   {
      case 10:
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
*
* IF (50 > grade < 90)
*    IF (last digit < 3)
*       RETURN -
*       END
*
*    ELSE IF (last digit > 6)
*       RETURN +
*       END
*    ELSE
*       RETURN *
*       END
*
* ELSE IF (grade >= 90)
*
*    IF (last digit < 3)
*       RETURN -
*       END
*    ELSE
*       RETURN *
*       END
*
* ELSE
* RETURN *
************************************************************************/
char computeGradeSign(int finalGrade)
{
   int gradeRange = (finalGrade / 10);
   int sign = (finalGrade % 10);

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

/*************************************************************************
* displays a menu of commands and will keep prompting until user quits
*
* PUT menu options
* SWITCH command
*    CASE n
*       changeName(names)
*    CASE p
*       changePoints(points)
*    CASE s
*       changeScore(score)
*    CASE c
*       clearScore(score)
*    CASE d
*       finalGrade = computeFinalGrade(score, points, numGrades)
*       letterGrade = computeLetterGrade(finalGrade)
*       gradeSign = computeGradeSign(finalGrade)
*       display(points, score, numGrades, names, finalGrade,
*               letterGrade, gradeSign)
*    CASE q
*
*    DEFAULT
*       PUT error message
**************************************************************************/
void interact(int points[], int score[], int numGrades, char names[][256])
{
   int finalGrade;
   char letterGrade;
   char gradeSign;
   char command;

   // set up menu loop

   do
   {
      cout << "Options:\n"
           << "\t(n) : Change the name of an item\n"
           << "\t(p) : Change the number of points an item is worth\n"
           << "\t(s) : Change the earned score on an item\n"
           << "\t(c) : Clear the score on an item\n"
           << "\t(d) : Display the grade list again\n"
           << "\t(q) : Quit\n"
           << "> ";
      cin >> command;
      switch (command)
      {
         case 'n':
            changeName(names);
            break;
         case 'p':
            changePoints(points);
            break;
         case 's':
            changeScore(score);
            break;
         case 'c':
            clearScore(score);
            break;
         case 'd':
            // refresh calculations and then display
            finalGrade = computeFinalGrade(score, points, numGrades);
            letterGrade = computeLetterGrade(finalGrade);
            gradeSign = computeGradeSign(finalGrade);
            display(points, score, numGrades, names, finalGrade,
                    letterGrade, gradeSign);
            break;
         case 'q':
            
            break;
         default:
            cout << "unknown command\n";
      }
   }
   while (command != 'q');
    
}

/*************************************************************************
* displays the current grade list
*
* PUT header
* FOR count = 1 to number of grades
*    PUT line of grades
* PUT footer
**************************************************************************/
void display(int points[], int score[], int numGrades, char names[][256],
             int finalGrade, char letterGrade, char gradeSign)
{
   cout.setf(ios::fixed);
   cout << "Your grades are:\n";

   // set up header
   cout << "\tNumber            Name Points Score\n";
   cout << "\t====== =============== ====== =====\n";

   // display body
   for (int i = 0; i < numGrades; i++)
   {
      cout << "\t" << setw(6) << i + 1
           << setw(16) << names[i]
           << setw(7) << points[i];
      if (score[i] < 0)
         cout << setw(7) << "--\n";
      else
         cout << setw(5) << score[i] << "%" << endl;
   }
   // display footer
   cout << "\t====== =============== ====== =====\n";
   cout << "\t       Total" << setw(22);
   if (finalGrade > -1)
   {
      cout << finalGrade
           << "% "
           << letterGrade;
      if (gradeSign != '*')
         cout << gradeSign;
      cout << endl;
   }
   else
      cout << "-" << "-\n";
}
