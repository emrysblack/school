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
#include <cctype>
#include <string>
using namespace std;

bool readBoard(int board[9][9], int readOnlyBoard[9][9]);
bool writeBoard(int board[9][9]);
void menu();
void display(int board[9][9]);
void getOption(int board[9][9], int readOnlyBoard[9][9]);
bool editSquare(int board[9][9], int readOnlyBoard[9][9]);
void showValues(int board[9][9]);
bool computeValues(int board[9][9], int row, int col, int value);
bool getCoordinates(string &cell, int &row, int &col);
bool isFixedSquare(int readOnlyBoard[9][9], int row, int col);

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
   int readOnlyBoard[9][9];
   
   readBoard(board, readOnlyBoard);
   menu();
   display(board);
   getOption(board, readOnlyBoard);
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
*       PUT dash separator before next row
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
            cout << num[r][c];
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
void getOption(int board[9][9], int readOnlyBoard[9][9])
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
            editSquare(board, readOnlyBoard);
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
bool readBoard(int board[9][9], int readOnlyBoard[9][9])
{
   char fileName[256];
   char readOnly;
   bool setSquares;
   
   cout << "Where is your board located? ";
   cin >> fileName;

   // open file
   ifstream fin(fileName);
   if (fin.fail())
   {
      cout << "Error: input file failed\n";
      return false;
      exit(1);
   }

   // fill board numbers and set read only values
   for (int row = 0; row < 9; row++)
   {
      for (int col = 0; col < 9; col++)
      {
         fin >> board[row][col];
         if (board[row][col] > 0)
            readOnlyBoard[row][col] = 1;
         else
            readOnlyBoard[row][col] = 0;
      }
   }
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
      cout << "Error: output file failed\n";
      return false;
      exit(1);
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
* IF not valid coordinates
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
bool editSquare(int board[9][9], int readOnlyBoard[9][9])
{
   string cell;
   int col;
   int row;
   int value;
   bool isValid;
   bool fixedSquare;

   isValid = getCoordinates(cell, row, col);   
   if (!(isValid))
      return false;
   // if square is read only, cannot edit square
   fixedSquare = isFixedSquare(readOnlyBoard, row, col);
   if (fixedSquare)
   {
      cout << "ERROR: Square "
           << cell
           << " is read-only\n";
      return false;
   }
   
   // get new value for square
   cout << "What is the value at '" 
        << cell
        << "': ";
   cin >> value;
   isValid = computeValues(board, row, col, value);
   if ((value < 0) || (value > 9) || (!(isValid)))
   {
      cout << "Error: Value '" << value << "' in square '"
           << cell
           << "' is invalid\n";
      return false;
   }
   board[row][col] = value;
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
   string cell;
   int row;
   int col;
   bool firstNum = true;
   bool isValid;
   
   isValid = getCoordinates(cell, row, col);
   if (isValid)
   {
      cout << "The possible values for '"
           << cell
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
* SWITCH column number modulus 3
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
bool computeValues(int board[9][9], int row, int col, int value)
{
   if (value == 0)
      return true;
   // check for values in current square
   int r;
   int c;

   //set check marker to top left in current square
   switch ((row + 1) % 3)
   {
      case 2:
         r = row - 1;
         break;
      case 1:
         r = row;
         break;
      case 0:
         r = row - 2;
         break;
      default:
         cout << "ERROR\n";
   }
   switch ((col + 1) % 3)
   {
      case 2:
         c = col - 1;
         break;
      case 1:
         c = col;
         break;
      case 0:
         c = col - 2;
         break;
      default:
         cout << "ERROR\n";
   }
   // walk through current square to check
   for (int counter = 0; counter < 3; counter++, r++)
   {
      for (int i = 0; i < 3; i++, c++)
         if (board[r][c] == value)
            return false;
      // reset column checker position with new row
      c -= 3;
   }
   // check for values in current row
   for (int i = 0; i < 9; i++)
      if (board[i][col] == value)
         return false;

   // check for values in current column
   for (int i = 0; i < 9; i++)
      if (board[row][i] == value)
         return false;
   
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
*    PUT invalid coordinate message
* END
************************************************************************/
bool getCoordinates(string &cell, int &row, int &col)
{
   // prompt for coordinates
   cout << "What are the coordinates of the square: ";
   cin >> cell;

   string coor = cell;
   
   // valid input with row number first
   if ((coor[0] >= '1') && (coor[0] <= '9'))
   {
      if ((coor[1] >= 'a') && (coor[1] <= 'i'))
         coor[1] = toupper(coor[1]);
      if ((coor[1] >= 'A') && (coor[1] <= 'I'))
         if (coor[2] == '\0')
         {            
            row = (int)(coor[0]) - 49;
            col = (int)(coor[1]) - 65;
            return true;
         }
   }
   // valid input with column letter first
   if ((coor[1] >= '1') && (coor[1] <= '9'))
   {
      if ((coor[0] >= 'a') && (coor[0] <= 'i'))
         coor[0] = toupper(coor[0]);
      if ((coor[0] >= 'A') && (coor[0] <= 'I'))
         if (coor[2] == '\0')
         {
            col = (int)(coor[0]) - 65;
            row = (int)(coor[1]) - 49;
            return true;
         }
   }
    
   // output error message for invalid coordinates
   else
   {
      cout << "ERROR: Square '"
           << cell
           << "' is invalid";
      return false;
   }
}

/***********************************************************************
* determines if a square is read only or not
*
* RETURN read only value true or false
* END
************************************************************************/
bool isFixedSquare(int readOnlyBoard[9][9], int row, int col)
{
   return readOnlyBoard[row][col]; // return true or false depending
}
