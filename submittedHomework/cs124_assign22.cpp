/***********************************************************************
* Program:
*    Assignment 22, Tic-Tac-Toe
*    Brother Helfrich, CS124
* Author:
*    Brady Field
* Summary: 
*    Reads a Tic-Tac-Toe board in from a file, displays the board,
*    and then prompts to save as a new file
*
*    Estimated:  0.5 hrs   
*    Actual:     1.0 hrs
*      Created an endless loop at first
************************************************************************/

#include <iostream>
#include <fstream>
using namespace std;

void readFile(char *fileName, char move[3][3]);
void writeFile(char *fileName, char move[3][3]);
void display(char move[3][3]);

/**********************************************************************
* prompts to open a file, calls functions to read, display, and then
* prompts for a file name to write to.
***********************************************************************/
int main()
{
   char fileName[256];
   char move[3][3];

   // prompt for file name
   cout << "Enter source filename: ";
   cin >> fileName;
   readFile(fileName, move);
   display(move);
   cout << "Enter destination filename: ";
   cin >> fileName;
   writeFile(fileName, move);
   return 0;
}

/**********************************************************************
* reads in contents of a file into an array
***********************************************************************/
void readFile(char *fileName, char move[3][3])
{
   ifstream fin(fileName);
   if (fin.fail())
      cout << "Error: file does not exist\n";
   // fill the array
   for (int c = 0, r = 0; r < 3; c++)
   {
      fin >> move[r][c];

      // check to see if we need a new row
      if (c > 1)
      {
         r++;
         c = -1;
      }
   }
   fin.close();
}

/**********************************************************************
* writes array into a file
***********************************************************************/
void writeFile(char *fileName, char move[3][3])
{
   ofstream fout(fileName);
   if (fout.fail())
      cout << "Error: could not open output file\n";
   
   // write to file
   for (int c = 0, r = 0; r < 3; c++)
   {
      fout << move[r][c]
           << " ";

      // check to see if we need a new row
      if (c > 1)
      {
         r++;
         fout << endl;
         c = -1;
      }
   }
   fout.close();
   cout << "File written\n";
}

/**********************************************************************
* displays the board
***********************************************************************/
void display(char move[3][3])
{
   for (int c = 0, r = 0; r < 3; c++)
   {
      // replace periods with blank spaces
      cout << " ";
      if (move[r][c] == '.')
         cout << "  ";
      // show moves of X or O
      else
         cout << move[r][c] << " ";
      // test if new line needed
      if (c > 1)
      {
         r++;
         if (r < 3)
         {
            cout << endl;
            cout << "---+---+---\n";
            c = -1;
         }
      }
      else
         cout << "|";
   }
   cout << endl;
}
