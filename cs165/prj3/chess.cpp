/***********************************************************************
* Program:
*    Project 3, Chess with Objects 
*    Brother Boyer, CS165
* Author:
*    Brady Field
* Summary:
*    A program to play an object-oriented version of the chess game.
*    Uses two header files for the board and the pieces. This is just 
*    the driver program for the game.
*
*    Estimated:  20.0 hrs   
*    Actual:     10.0 hrs
*      getting redefined functions to work in piece class
************************************************************************/
#include <iostream>
#include <string>
#include <fstream>
#include "piece.h"
#include "board.h"
using namespace std;

bool recordMove(Board *board);
void getMove(Board &board);
bool isMenu(Board &board);
bool makeMove(Board &board);
void displayMenu();
void quit(Board &board);
bool writeFile(string fileName, Board *board);
bool readFile(Board &board);

/***************************************************
 * MAIN: displays board and starts game loop
 ***************************************************/
int main()
{
   Board board;
   board.display();

   // commandLoop
   while (!board.done)
   {
      getMove(board);
   }
   return 0;
}

/***************************************************
 * GET MOVE: prompts user for move
 ***************************************************/
void getMove(Board &board)
{
   cout << board.getPlayer() << ": ";
   cin >> board.cmd;
   isMenu(board);
      
}

/***************************************************
 * IS MENU: determines if menu command
 ***************************************************/
bool isMenu(Board &board)
{
   if (board.cmd == "?")
      displayMenu();
   else if ((board.cmd == "read") || (board.cmd == "r"))
   {
      board.reset();
      if (readFile(board))
         board.display();
   }
   else if (board.cmd == "help")
      cout << "display possible moves\n";
   else if (board.cmd == "test")
   {
      board.test = true;
      board.display();
   }
   else if (board.cmd == "quit")
   {
      board.done = true;
      quit(board);
   }
   else
      if (board.makeMove())
      {
         board.movePiece();
         recordMove(&board);
         board.display();
         return true;
      }
      else
         return false;
   return true;
}



/****************************************************
 * DISPLAY MENU: displays possbile options
 ****************************************************/
void displayMenu()
{
   cout << "Options:\n"
        << " quit   Leave the game. You will be prompted to save\n"
        << " ?      Display these options\n"
        << " r      Read a saved game from a file\n"
        << " b2b4   Specify a move using the Smith Notation\n";
}

/****************************************************
 * QUIT: prompts for save and exits program
 ****************************************************/
void quit(Board &board)
{
   string fileName;
   
   cout << "To save a game, please specify the filename.\n"
        << "    To quit without saving a file, just press <enter>\n";
   cin.ignore(1, '\n');
   if (getline(cin,fileName))
      if (fileName != "\n")
         writeFile(fileName, &board);
}

/*************************************************************************
 * records the move
 *************************************************************************/
bool recordMove(Board *board)
{
   board->moves.push_back(board->cmd);
   return true;
}

/*************************************************************************
 * takes all moves in the game and records them to a specified file
 *************************************************************************/
bool writeFile(string fileName, Board *board)
{
   ofstream fout(fileName.c_str());
   if (fout.fail())
      return false;
   for (int i = 0; i < board->moves.size(); i++)
   {
      fout << board->moves[i];
      if (i % 2 == 0)
         fout << " ";
      else
         fout << endl;
   }
   fout.close();
   return true;
}

/*************************************************************************
 * reads in moves from a file one at a time from a saved game, and passes
 * them to be moved
 *************************************************************************/
bool readFile(Board &board)
{   
   string fileName;
   string move;
   vector <string> temp;
   cout << "Filename: ";
   cin >> fileName;

   //open file
   ifstream fin(fileName.c_str());
   if (fin.fail())
   {
      cout << "Unable to open file "
           << fileName
           << " for input.\n";
      return false;
   }
   for (int i = 0; fin >> move; i++)
      board.moves.push_back(move);
   fin.close();
      // check file for illegal moves
      for (int i = 0; i < board.moves.size(); i++)
      {
         board.cmd = board.moves[i];
         if (board.validFile(fileName))
            board.movePiece();
         else
            return false;
      }
   return true;
}
