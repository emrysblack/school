/***********************************************************************
* Program:
*    Test 3, Fix the text
*    Brother Helfrich, CS124
* Author:
*    Brady Field
* Summary: 
*    Reads in a file with disorganized text, displays the number of 
*    letters and then the actual word from the text to the user.
*    Estimated:  0.7 hrs   
*    Actual:     0.0 hrs
*      Please describe briefly what was the most difficult part
************************************************************************/

#include <iostream>
#include <fstream>
using namespace std;

void getName(char filename[]);
bool readFile(char filename[], char text[]);
int countLetters(char text[]);
void display(int numLetters, char text[]);

/**********************************************************************
* Add text here to describe what the function "main" does. Also don't forget
* to fill this out with meaningful text or YOU WILL LOOSE POINTS.
***********************************************************************/
int main()
{
   char filename[256];
   char text[256];
   int numLetters;


   getName(filename);
   readFile(filename, text);
   numLetters = countLetters(text);
   display(numLetters, text);
   return 0;
}

/**********************************************************************
* opens a file and reads its contents into an array
***********************************************************************/
bool readFile(char filename[], char text[])
{
   // open file
   ifstream fin;
   fin.open(filename);
   if (fin.fail())
   {
      cout << "Unable to open the file "
           << filename
           << endl;
      return 0;
   }

   // fills the array
   int i;
   for (i =0; text[i] != '.'; i++)
      fin >> text[i];

   fin.close();
   return 1;
}

/**********************************************************************
* prompts for the name of the file to be opened
***********************************************************************/
void getName(char filename[])
{
   cout << "Please specify the file name: ";
   cin >> filename;
}

/**********************************************************************
* counts the number of letters in a file
***********************************************************************/
int countLetters(char text[])
{
   int numLetters = 0;
   for (int i = 0; text[i] != '.'; i++)
      numLetters++;
   return numLetters;
}
                 
/**********************************************************************
* displays the number of letters and the contents of file
***********************************************************************/
void display(int numLetters, char text[])
{
   cout << "There are "
        << numLetters
        << " letters in the file.\n";
   cout << "The word is \"";
   
   for (int i = 0; i < numLetters; i++)
      cout << text[i];
   cout << "\"\n";
}
