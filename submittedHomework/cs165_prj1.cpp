/***********************************************************************
* Program:
*    Project 1, Procedural Chess 
*    Brother Boyer, CS165
* Author:
*    Brady Field
* Summary:
*    A simple program to play procedural chess.
*
*    Estimated:  10.0 hrs   
*    Actual:     15.0 hrs
*      getting the display settings right
************************************************************************/

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

void interact(int playerBoard[8][8], char pieces[8][8],
              vector <string> &moves);
bool isCommand(string cmd, int playerBoard[8][8],
               char pieces[8][8], vector <string> &moves,
               string &player);
bool isValid(const string cmd, const int playerBoard[8][8],
             const char pieces[8][8]);
void displayOptions();
void displayBoard(const int playerBoard[8][8], const char pieces[8][8]);
bool movePiece(const string cmd, int playerBoard[8][8], char pieces[8][8],
               vector <string> &moves);
bool recordMove(const string cmd, vector <string> &moves);
void quit(const vector <string> &moves);
bool readFile(int playerBoard[8][8], char pieces[8][8], vector <string> &moves,
              string &player);
bool writeFile(string fileName, const vector <string> &moves);
bool isValidFile(const string cmd, const int playerBoard[8][8],
                 const char pieces[8][8], const string fileName);
bool resetBoard(int playerBoard[8][8], char pieces[8][8]);

/**********************************************************************
 * Stores variables for player positions and pieces, and calls interact
 ***********************************************************************/
int main()
{
   vector <string> moves;
   int playerBoard[8][8] = {2,2,2,2,2,2,2,2,
                            2,2,2,2,2,2,2,2,
                            0,0,0,0,0,0,0,0,
                            0,0,0,0,0,0,0,0,
                            0,0,0,0,0,0,0,0,
                            0,0,0,0,0,0,0,0,
                            1,1,1,1,1,1,1,1,
                            1,1,1,1,1,1,1,1};
   char pieces[8][8] = {'R','N','B','Q','K','B','N','R',
                        'p','p','p','p','p','p','p','p',
                        ' ',' ',' ',' ',' ',' ',' ',' ',
                        ' ',' ',' ',' ',' ',' ',' ',' ',
                        ' ',' ',' ',' ',' ',' ',' ',' ',
                        ' ',' ',' ',' ',' ',' ',' ',' ',
                        'p','p','p','p','p','p','p','p',
                        'R','N','B','Q','K','B','N','R',};
   
   interact(playerBoard, pieces, moves);
   return 0;
}

/***********************************************************************
 * displays the board and awaits user to enter a move or a command
 ***********************************************************************/
void interact(int playerBoard[8][8], char pieces[8][8], vector <string> &moves)
{
   string player = "White";
   string cmd;
   bool done = false;

   system("clear");
   displayBoard(playerBoard, pieces);
   
   while (!(done))
   {
      cout << "("
           << player
           << "): ";
      cin >> cmd;
      // check to see if quit command
      if (cmd == "quit")
      {
         quit(moves);
         done = true;
      }
      else if (!(movePiece(cmd, playerBoard, pieces, moves)))
         isCommand(cmd, playerBoard, pieces, moves, player);
      else
      {
         // refresh screen and switch player
         system("clear");
         displayBoard(playerBoard, pieces);
         if (player == "White")
            player = "Black";
         else
            player = "White";
      }
   }
}

/***********************************************************************
 * calls function to display the options or read in a file depending on 
 * user input. returns false if invalid option
 ***********************************************************************/
bool isCommand(string cmd, int playerBoard[8][8],char pieces[8][8],
               vector <string> &moves, string &player)
{
   char option = cmd[0];

   switch (option)
   {
      case '?':
         displayOptions();
         break;
      case 'r':
         // reset board
         resetBoard(playerBoard, pieces);
         if (readFile(playerBoard, pieces, moves, player))
         {
            system("clear"); // refresh screen
            displayBoard(playerBoard, pieces);
         }
         break;
      default:
         return false;
   }
   return true;
}

/************************************************************************
 * displays menu of options
 ************************************************************************/
void displayOptions()
{

   // display menu
   cout << "Options:\n";
   cout << " quit   Leave the game. You will be prompted to save\n"
        << " ?      Display these options\n"
        << " r      Read a saved game from a file\n"
        << " b2b4   Specify a move using the Smith Notation\n";
}

/*************************************************************************
 * determines if a move is valid, or if a command is valid
 *************************************************************************/
bool isValid(const string cmd, const int playerBoard[8][8],
             const char pieces[8][8])
{
   int sr = 56 - (int)cmd[1]; // set source array row
   int sc = (int)cmd[0] - 97; // set source array column
   int dr = 56 - (int)cmd[3]; // set destination array row
   int dc = (int)cmd[2] - 97; // set destination array column

   if (cmd[0] >= 'a' && cmd[0] <= 'h')
   {
      if (cmd[1] >= '1' && cmd[1] <= '8')
         if (cmd[2] >= 'a' && cmd[2] <= 'h')
            if ((cmd[4] == '\0') || (cmd[4] == 'R') || (cmd[4] == 'N') ||
                (cmd[4] == 'B') || (cmd[4] == 'Q') || (cmd[4] == 'p') ||
                (cmd[4] == 'c') || (cmd[4] == 'C') || (cmd[4] == 'E'))
               if (cmd[3] >= '1' && cmd[3] <= '8')
                  if (playerBoard[sr][sc] != 0)
                     if (playerBoard[sr][sc] != playerBoard[dr][dc])
                        return true;
                     else
                        cout << "Error in move '"
                             << cmd
                             << "': Illegal to move onto your own piece\n";
                  else
                     cout << "Error in move '"
                          << cmd
                          << "': Piece not present in source coordinate\n";
               else
                  cout << "Error in move '"
                       << cmd
                       << "': "
                       << "Invalid specification of destination coordinates\n";
            else
               cout << "Error in move '"
                    << cmd
                    << "': Unknown promotion piece specification\n";
   }
   else if ((cmd != "?") && (cmd != "r"))
      cout << "Error in move '"
           << cmd
           << "': Invalid specification of source coordinates\n";
   if ((cmd != "?") && (cmd != "r"))
      cout << "\tType ? for more options\n";
   return false;
}

/*************************************************************************
 * displays the board
 *************************************************************************/
void displayBoard(const int playerBoard[8][8], const char pieces[8][8])
{
   // display header
   cout << "  ";
   for (char i = 'a'; i <= 'h'; i++)
      cout << " "
           << i
           << " ";
   cout << endl;
   // display board
   for (int boardR = 8, r = 0; boardR >= 1; boardR--, r++)
   {
      cout << boardR
           << " ";
      for (int c = 0, pos = 0; c <= 7; c++, pos++)
      {         
         if (boardR % 2 == 0) // even rows, black square first
         {           
            if (playerBoard[r][c] == 2)
               cout << "\E[5;30m" << " " << pieces[r][pos]
                    << " " << "\E[0m"; // black square, black piece
            else if (playerBoard[r][c] == 1)
               cout << "\E[5;31m" << " " << pieces[r][pos]
                    << " " << "\E[0m"; // black square, white piece
            else if (playerBoard[r][c] == 0)
               cout << "\E[5;30m" << " " << pieces[r][pos]
                    << " " << "\E[0m"; // black square, blank
            c++; // next square
            pos++;
            
            // white square after black
            if (playerBoard[r][c] == 2)
               cout << "\E[7;40m" << " " << pieces[r][pos]
                    << " " << "\E[0m"; // white square, black piece
            else if (playerBoard[r][c] == 1)
               cout << "\E[7;41m" << " " << pieces[r][pos]
                    << " " << "\E[0m"; // white square, white piece
            else if (playerBoard[r][c] == 0)
               cout << "\E[7;40m" << " " << pieces[r][pos]
                    << " " << "\E[0m"; // white square, blank
         }       
         else // odd rows, white square first
         {
            if (playerBoard[r][c] == 2)
               cout << "\E[7;40m" << " " << pieces[r][pos]
                    << " " << "\E[0m"; // white square, black piece
            else if (playerBoard[r][c] == 1)
               cout << "\E[7;41m" << " " << pieces[r][pos]
                    << " " << "\E[0m"; // white square, white piece
            else if (playerBoard[r][c] == 0)
               cout << "\E[7;40m" << " " << pieces[r][pos]
                    << " " << "\E[0m"; // white square, blank
            c++; // next square
            pos++;
            
            // black square after white
            if (playerBoard[r][c] == 2)
               cout << "\E[5;30m" << " " << pieces[r][pos]
                    << " " << "\E[0m"; // black square, black piece
            else if (playerBoard[r][c] == 1)
               cout << "\E[5;31m" << " " << pieces[r][pos]
                    << " " << "\E[0m"; // black square, white piece
            else if (playerBoard[r][c] == 0)
               cout << "\E[5;30m" << " " << pieces[r][pos]
                    << " " << "\E[0m"; // black square, blank
         }
      }
      cout << endl;
   }
         
}

/*************************************************************************
 * calls is valid to check move, then moves a piece,
 * clears the old square, and calls function to record the move
 *************************************************************************/
bool movePiece(const string cmd, int playerBoard[8][8], char pieces[8][8],
               vector <string> &moves)
{
   if (isValid(cmd, playerBoard, pieces))
   {
      // set coordinates to proper array position
      int sr = 56 - (int)cmd[1]; // source array row and column
      int sc = (int)cmd[0] - 97; 
      int dr = 56 - (int)cmd[3]; // destination array row and column
      int dc = (int)cmd[2] - 97; 

      // move the piece and clear old square
      playerBoard[dr][dc] = playerBoard[sr][sc];
      pieces[dr][dc] = pieces[sr][sc];
      playerBoard[sr][sc] = 0;
      pieces[sr][sc] = ' ';

      // detect special moves
      if (cmd[4] == 'c') // castling
      {
         if (sr == 0)
         {
            // black side
            pieces[dr][dc - 1] = 'R';
            pieces[sr][7] = ' ';
         }
         else if (sr == 7)
         {
            // white side
            pieces[dr][dc + 1] = 'R';
            pieces[sr][0] = ' ';
         }
      }
      if (cmd[4] == 'C') // long castling
      {
         if (sr == 0)
         {
            // black side
            pieces[dr][dc + 1] = 'R';
            pieces[sr][0] = ' ';
         }
         else if (sr == 7)
         {
            // white side
            pieces[dr][dc - 1] = 'R';
            pieces[sr][7] = ' ';
         }
      }
      
      // record
      recordMove(cmd, moves);
      
      return true;
   }
   return false;
}

/*************************************************************************
 * records the move
 *************************************************************************/
bool recordMove(const string cmd, vector <string> &moves)
{
   moves.push_back(cmd);
   return true;
}

/*************************************************************************
 * if user enters a file name, calls function to write to a file, if not
 * it quits without writing a file
 *************************************************************************/
void quit(const vector <string> &moves)
{
   string fileName;
   
   cout << "To save a game, please specify the filename.\n"
        << "    To quit without saving a file, just press <enter>\n";
   cin.ignore(1, '\n');
   if (getline(cin,fileName))
      if (fileName != "\n")
         writeFile(fileName, moves);
}

/*************************************************************************
 * reads in moves from a file one at a time from a saved game, and passes
 * them to be moved
 *************************************************************************/
bool readFile(int playerBoard[8][8], char pieces[8][8],
              vector <string> &moves, string &player)
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
      temp.push_back(move);
   fin.close();
   // check file for illegal moves
   int i;
   for (i = 0; i < temp.size(); i++)
   {
      if (isValidFile(temp[i], playerBoard, pieces, fileName))
         movePiece(temp[i], playerBoard, pieces, moves);
      else
         return false;
   }      
   if (i % 2 == 0)
      player = "White";
   else
      player = "Black";
   
   return true;
}

/*************************************************************************
 * takes all moves in the game and records them to a specified file
 *************************************************************************/
bool writeFile(string fileName, const vector <string> &moves)
{
   ofstream fout(fileName.c_str());
   if (fout.fail())
      return false;
   for (int i = 0; i < moves.size(); i++)
   {
      fout << moves[i];
      if (i % 2 == 0)
         fout << " ";
      else
         fout << endl;
   }
   fout.close();
   return true;
}

/*************************************************************************
 * determines if a file has all valid moves
 *************************************************************************/
bool isValidFile(const string cmd, const int playerBoard[8][8],
                 const char pieces[8][8], const string fileName)
{
   int sr = 56 - (int)cmd[1]; // set source array row
   int sc = (int)cmd[0] - 97; // set source array column
   int dr = 56 - (int)cmd[3]; // set destination array row
   int dc = (int)cmd[2] - 97; // set destination array column

   if (cmd[0] >= 'a' && cmd[0] <= 'h')
   {
      if (cmd[1] >= '1' && cmd[1] <= '8')
         if (cmd[2] >= 'a' && cmd[2] <= 'h')
            if ((cmd[4] == '\0') || (cmd[4] == 'R') || (cmd[4] == 'N') ||
                (cmd[4] == 'B') || (cmd[4] == 'Q') || (cmd[4] == 'p') ||
                (cmd[4] == 'c') || (cmd[4] == 'C') || (cmd[4] == 'E'))
               if (cmd[3] >= '1' && cmd[3] <= '8')
                  if (playerBoard[sr][sc] != 0)
                     if (playerBoard[sr][sc] != playerBoard[dr][dc])
                        return true;
                     else
                        cout << "Error parsing file "
                             << fileName
                             << " with move '"
                             << cmd
                             << "': Illegal to move onto your own piece\n";
                  else
                     cout << "Error parsing file "
                          << fileName
                          << " with move '"
                          << cmd
                          << "': Piece not present in source coordinate\n";
               else
                  cout << "Error parsing file "
                       << fileName
                       << " with move '"
                       << cmd
                       << "': "
                       << "Invalid specification of destination coordinates\n";
            else
               cout << "Error parsing file "
                    << fileName
                    << " with move '"
                    << cmd
                    << "': Unknown promotion piece specification\n";
   }   
   else 
      cout << "Error parsing file "
           << fileName
           << " with move '"
           << cmd
           << "': Invalid specification of source coordinates\n";
   return false;
}

/*************************************************************************
 *
 *
 *************************************************************************/
bool resetBoard(int playerBoard[8][8], char pieces[8][8])
{
   int playerBoardtmp[8][8] = {2,2,2,2,2,2,2,2,
                            2,2,2,2,2,2,2,2,
                            0,0,0,0,0,0,0,0,
                            0,0,0,0,0,0,0,0,
                            0,0,0,0,0,0,0,0,
                            0,0,0,0,0,0,0,0,
                            1,1,1,1,1,1,1,1,
                            1,1,1,1,1,1,1,1};
   char piecestmp[8][8] = {'R','N','B','Q','K','B','N','R',
                        'p','p','p','p','p','p','p','p',
                        ' ',' ',' ',' ',' ',' ',' ',' ',
                        ' ',' ',' ',' ',' ',' ',' ',' ',
                        ' ',' ',' ',' ',' ',' ',' ',' ',
                        ' ',' ',' ',' ',' ',' ',' ',' ',
                        'p','p','p','p','p','p','p','p',
                        'R','N','B','Q','K','B','N','R',};
 for (int c = 0; c < 8; c++)
    for (int r = 0; r < 8; r++)
    {
       playerBoard[c][r] = playerBoardtmp[c][r];
       pieces[c][r] = piecestmp[c][r];
    }
    
   
   return true;
}
