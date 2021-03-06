/***********************************************************************
* Program:
*    Project 5, Sudoku
*    Brother Helfrich, CS124
* Author:
*    Brady Field
* Summary: 
*    Loads a Sudoku board and allows user to edit and save the game
*
*    Estimated:  10.0 hrs   
*    Actual:     8.0 hrs
*      Checking for valid squares
************************************************************************/

#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

bool readBoard(int board[9][9]);
bool writeBoard(int board[9][9]);
void menu();
void display(int board[9][9]);
void getOption(int board[9][9]);
bool editSquare(int board[9][9]);
void showValues(int board[9][9]);
bool computeValues(int board[9][9], int r, int c, int value);
bool getCoordinates(int &row, int &col);

/**********************************************************************
* reads the board, displays the options menu and then the board, and
* then prompts for user options
*
* RUN readBoard
* RUN menu
* RUN display
* RUN getOption
* END
***********************************************************************/
int main()
{   
   int board[9][9];
   
   if(readBoard(board))
   {
      menu();
      display(board);
      getOption(board);
   }
   return 0;
}

/**********************************************************************
* displays an interactive menu
*
* PUT options header
* PUT show instructions option
* PUT display board option
* PUT edit square option
* PUT show possible values option
* PUT save and quit option
* END
***********************************************************************/
void menu()
{
   
   // display menu
   cout << "Options:\n";
   cout << "   ?  Show these instructions\n"
        << "   D  Display the board\n"
        << "   E  Edit one square\n"
        << "   S  Show the possible values for a square\n"
        << "   Q  Save and Quit\n"
        << endl;
}

/***********************************************************************
* displays the board
*
* header
* FOR 9x
*    PUT A, B, C, etc
* body
* FOR 9x
*    row
*    PUT row number
*    FOR 9x
*       PUT value
*    IF end of table
*       EXIT loop
*    IF new row needed
*       PUT dash separater before next row
* END
************************************************************************/
void display(int num[9][9])
{
   // header
   cout << "   ";
   for (int i = 0; i < 9; i++)
   {
      cout << (char)(i + 65);
      if (i < 8)
         cout << " ";
   }
   // body
   cout << endl;
   for (int r = 0; r < 9; r++)
   {
      // display row
      cout << r + 1 << "  ";
      for (int c = 0; c < 9; c++)
      {
         if (num[r][c] != 0)
            if (num[r][c] > 0)
               cout << num[r][c];
            else
               cout << -num[r][c];
         else
            cout << " ";
         if (c == 8)
            ;
         else if ((c + 1) % 3 == 0)
            cout << "|";
         else
            cout << " ";
      }
      cout << endl;
      // check for end of table
      if (r == 8)
         ;
      // check to see if 3 by 3 square complete
      else if ((r + 1) % 3 == 0)
      {
         cout << "   "
              << "-----"
              << "+"
              << "-----"
              << "+"
              << "-----\n";
      }
   }
}

/***********************************************************************
* takes user option
*
* WHILE not done
*    PROMPT command
*    GET command
*    SWITCH command
*       CASE ?
*          menu
*       CASE d
*          display
*       CASE e
*          edit square
*       CASE s
*          show possible values
*       CASE q
*          save
*          SET done = true
* END
************************************************************************/
void getOption(int board[9][9])
{
   char cmd = 'z';
   bool done = false;

   // loop for command
   while (!(done))
   {
      cout << endl;
      cout << "> ";
      cin >> cmd;

      switch (cmd)
      {
         case '?':
            menu();
            break;
         case 'D':
         case 'd':
            display(board);
            break;
         case 'E':
         case 'e':
            editSquare(board);
            break;
         case 'S':
         case 's':
            showValues(board);
            break;
         case 'Q':
         case 'q':
            writeBoard(board);
            done = true;
            break;
         default:
            cout << "Error: Invalid command\n";
            menu();
            break;
      }
   }
}

/***********************************************************************
* loads the board and sets read only values
*
* PROMPT input file name
* GET input file name
* IF open input file fails
*    PUT error message
* FOR 9x
*    FOR 9x
*       READ value
*       IF already a value present
*          SET position to read only
*       ELSE
*          SET position to read write
* END
************************************************************************/
bool readBoard(int board[9][9])
{
   char fileName[256];
    
   cout << "Where is your board located? ";
   cin >> fileName;

   // open file
   ifstream fin(fileName);
   if (fin.fail())
   {
      cout << "Error: input file failed\n";
      return false;
   }

   // fill board numbers and set read only values
   for (int row = 0; row < 9; row++)
      for (int col = 0; col < 9; col++)
         fin >> board[row][col];
   fin.close();
   return true;
}

/***********************************************************************
* writes the board to a text file
*
* PROMPT file destination
* GET file destination
* IF file open fails
*    PUT error message
* FOR 9x
*    FOR 9x
*       WRITE square value
*       IF no new line
*          WRITE space
*    IF new line needed
*       WRITE new line
* RETURN true
* END
************************************************************************/
bool writeBoard(int board[9][9])
{
   char fileName[256];
   
   cout << "What file would you like to write your board to: ";
   cin >> fileName;

   // open file
   ofstream fout(fileName);
   if (fout.fail())
   {
      cout << "ERROR: output file failed\n";
      return false;
      //exit(1);
   }

   // write board numbers
   for (int r = 0; r < 9; r++)
   {
      for (int c = 0; c < 9; c++)
      {
         fout << board[r][c];
         if (c < 8)
            fout << " ";
      }
      if  (r < 8)
         fout << endl;
   }
   fout.close();
   cout << "Board written successfully\n";
   return true;
}

/***********************************************************************
* prompts for a single square to edit
*
* IF not valid coordintes
*    RETURN false
* IF read only square
*    PUT error message for read only
*    RETURN false
* PROMPT new value
* GET new value
* IF new value is invalid
*    PUT error message
*    RETURN false
* SET board square = value
* RETURN true
* END
************************************************************************/
bool editSquare(int board[9][9])
{
   int col;
   int row;
   int value;
      
   if (!(getCoordinates(row, col)))
      return false;
   
   // if square is read only, cannot edit square
   if (board[row][col] > 0)
   {
      cout << "ERROR: Square '"
           << char(col + 'A')
           << row + 1
           << "' is filled\n";
      return false;
   }
   
   // get new value for square
   cout << "What is the value at '" 
        << char(col + 'A')
        << row + 1
        << "': ";
   cin >> value;
   
   if ((value < 0) || (value > 9) ||
       (!(computeValues(board, row, col, value))))
   {
      cout << "ERROR: Value '" << value << "' in square '"
           << char(col + 'A')
           << row + 1
           << "' is invalid\n";
      return false;
   }
   board[row][col] = -value;
   return true;
}

/***********************************************************************
* shows the possible values for a given square
*
* IF valid coordinates
*    PUT message for possible values
*    FOR 9x
*       IF valid entry and first num listed
*          PUT list num
*          SET first num listed = false
*       ELSE IF valid entry
*          PUT space and comma and then list num
* END
************************************************************************/
void showValues(int board[9][9])
{
   int row;
   int col;
   bool firstNum = true;
   bool isValid;
      
   if (getCoordinates(row, col))
   {
      cout << "The possible values for '"
           << char(col + 'A')
           << row + 1
           << "' are: ";
      for (int i = 1; i <= 9; i++)
      {
         isValid = computeValues(board, row, col, i);
         if (isValid && firstNum)
         {
            cout << i;
            firstNum = false;
         }
         else if (isValid)
            cout << ", " << i;
      }
      cout << endl;
   }
}

/***********************************************************************
* computes the possible values for a given square
*
* IF user clears square
*    RETURN true
* SWITCH row number modulus 3
*    CASE 2
*       SET marker = row - 1
*    CASE 1
*       SET marker = row
*    CASE 0
*       SET marker = row - 2
*    DEFAULT
*       PUT error message
* SWITCH cloumn number modulus 3
*    CASE 2
*       SET marker = column - 1
*    CASE 1
*       SET marker = column
*    CASE 0
*       SET marker = column - 2
*    DEFAULT
*       PUT error message
* FOR counter 3x
*    FOR column 3x
*       IF value already in square
*          RETURN false
*    SET row + 1 and column - 3
* FOR 9x
*    IF value is already in row
*       RETURN false
* FOR 9x
*    IF value is already in column
*       RETURN false
* RETURN true
* END
************************************************************************/
bool computeValues(int board[9][9], int r, int c, int value)
{
   if (value == 0)
      return true;

   // check for values in current row
   for (int i = 0; i < 9; i++)
      if (abs(board[i][c]) == value)
         return false;

   // check for values in current column
   for (int i = 0; i < 9; i++)
      if (abs(board[r][i]) == value)
         return false;
   
   //set check marker to top left in current square
   r -= r % 3;
   c -= c % 3;
   
   // walk through current square to check
   for (int i = 0; i < 3; i++, r++)
   {
      for (int j = 0; j < 3; j++, c++)
         if (abs(board[r][c]) == value)
            return false;
      // reset column checker position with new row
      c -= 3;
   }
   
   return true;
}

/***********************************************************************
* sets row and column value for a given square
*
* PROMPT for coordinates
* GET coordinates
* IF row number first
*    IF column letter is lowercase set to uppercase
*    IF column letter is uppercase
*       CHECK to make sure no additional symbols were entered
*          SET row to first input
*          SET column to second input
* IF column letter first
*    IF column letter is lowercase set to uppercase
*    IF column letter is uppercase
*       CHECK to make sure no additional symbols were entered
*          SET row to second input
*          SET column to first input
* ELSE
*    PUT invlaid coordinate message
* END
************************************************************************/
bool getCoordinates(int &row, int &col)
{
   char coor[3];
   // prompt for coordinates
   cout << "What are the coordinates of the square: ";
   cin >> coor;
      
   // valid input with row number first
   if (((coor[0] >= '1') && (coor[0] <= '9')) &&
      ((toupper(coor[1]) >= 'A') &&
       (toupper(coor[1]) <= 'I')) &&
       (coor[2] == '\0'))
   {                               
      row = (int)(coor[0]) - 49;
      col = (int)(toupper(coor[1])) - 65;
      return true;
   }

   // valid input with column letter first
   else if (((coor[1] >= '1') && (coor[1] <= '9')) &&
            ((toupper(coor[0]) >= 'A') &&
             (toupper(coor[0]) <= 'I')) &&
            (coor[2] == '\0'))
   {
      col = (int)(toupper(coor[0])) - 65;
      row = (int)(coor[1]) - 49;
      return true;
   }

    
   // output error message for invalid coordinates
   else
   {
      cout << "ERROR: Square '"
           << coor
           << "' is invalid\n";
      return false;
   }
}
