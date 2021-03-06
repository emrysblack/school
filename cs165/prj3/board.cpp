// contains all function definitions
// for Board class

#include <iostream>
#include <cstdlib>
#include "board.h"
using namespace std;

/***********************************
 * BOARD: DEFUALT CONSTRUCTOR
 ***********************************/
Board::Board()
{
   
   test = false;
   done = false;
   
   // set up all id chars and for pieces
   k1.setID('K');
   k2.setID('k');
   q1.setID('Q');
   q2.setID('q');
   r1.setID('R');
   r2.setID('r');
   n1.setID('N');
   n2.setID('n');
   b1.setID('B');
   b2.setID('b');
   p1.setID('P');
   p2.setID('p');

   //set up owner according to piece id
   k1.setOwner('B');
   k2.setOwner('W');
   q1.setOwner('B');
   q2.setOwner('W');
   r1.setOwner('B');
   r2.setOwner('W');
   n1.setOwner('B');
   n2.setOwner('W');
   b1.setOwner('B');
   b2.setOwner('W');
   p1.setOwner('B');
   p2.setOwner('W');

   reset();
}

/**************************************
 * RESET: resets position of pieces
 * on board to starting location
 **************************************/
void Board::reset()
{
   player = "(White)"; // first player
   moves.clear();
   
   // set square colors for board
   for(int r = 0; r < 8; r++) 
      for (int c = 0; c < 8; c++)
      {
         if (r % 2 == 0)
            if (c % 2 == 0)
               isWhiteSquare[r][c] = true;
            else
               isWhiteSquare[r][c] = false;
         else
            if (c % 2 == 0)
               isWhiteSquare[r][c] = false;
            else
               isWhiteSquare[r][c] = true;
         if (r == 0) // set black pieces
         {
            if ((c == 0) || (c == 7))
               pieces[r][c] = &r1;
            else if ((c == 1) || (c == 6))
               pieces[r][c] = &n1;
            else if ((c == 2) || (c == 5))
               pieces[r][c] = &b1;
            else if (c == 3)
               pieces[r][c] = &q1;
            else if (c == 4)
               pieces[r][c] = &k1;
         }
         else if (r == 1) // set black pawns
            pieces[r][c] = &p1;
         else if (r == 6) // set white pawns
            pieces[r][c] = &p2;
         else if (r == 7) // set white pieces
         {
            if ((c == 0) || (c == 7))
               pieces[r][c] = &r2;
            else if ((c == 1) || (c == 6))
               pieces[r][c] = &n2;
            else if ((c == 2) || (c == 5))
               pieces[r][c] = &b2;
            else if (c == 3)
               pieces[r][c] = &q2;
            else if (c == 4)
               pieces[r][c] = &k2;
         }
         else
            pieces[r][c] = &s; //set spaces
      }
}

/**************************************
 * MOVE PIECE: move a piece
 **************************************/
void Board::movePiece()
{
    // set coordinates to proper array position
      int sr = 56 - (int)cmd[1]; // source array row and column
      int sc = (int)cmd[0] - 97; 
      int dr = 56 - (int)cmd[3]; // destination array row and column
      int dc = (int)cmd[2] - 97; 

      // move the piece and clear old square
      pieces[dr][dc] = pieces[sr][sc];
      pieces[sr][sc] = &s;
}

/**************************************
 * BOARD: DISPLAY
 * displays a header and then board
 **************************************/
void Board::display()
{
   if (!test)
   {
      // display header
      system("clear");
      cout << "  ";
      for (char i = 'a'; i <= 'h'; i++)
         cout << " "
              << i
              << " ";
      cout << endl;
      // display board
      for (int r = 0; r < 8; r++)
      {
         cout << 8 - r
              << " ";
         for (int c = 0, pos = 0; c <= 7; c++, pos++)
         {
            if (!isWhiteSquare[r][c])
               if (pieces[r][c]->getID() <= 'R')
                  cout << "\E[30;41m" << " " << pieces[r][pos]->getName()
                       << " " << "\E[0m"; // black square, black piece or blank
               else
                  cout << "\E[37;41m" << " " << pieces[r][pos]->getName()
                       << " " << "\E[0m"; // black square, white piece
            else
               if (pieces[r][c]->getID() <= 'R')
                  cout << "\E[30;47m" << " " << pieces[r][pos]->getName()
                       << " " << "\E[0m"; // white square, black piece or blank
               else
                  cout << "\E[31;47m" << " " << pieces[r][pos]->getName()
                       << " " << "\E[0m"; // white square, white piece
         }
         cout << endl;
      }
   }
   else
   {
      cout << "  ";
      for (char i = 'a'; i <= 'h'; i++)
         cout << i;
      cout << endl;
      // display board
      for (int r = 0; r < 8; r++)
      {
         cout << 8 - r
              << " ";
         for (int c = 0, pos = 0; c <= 7; c++, pos++)
         {
            cout << pieces[r][pos]->getID();               
         }
         cout << endl;
      }
   }
}

/****************************************************
 * MAKE MOVE: sees if input move is valid,
 * performs move, and redisplays board
 ****************************************************/
bool Board::makeMove()
{
   try
   {
      if (move())
         return true;
   }
   catch (int e)
   {
      if (e == 1)
         cout << "Error in move '"
              << cmd
              << "': Illegal to move your opponent's piece\n";         
      else if (e ==2)
         cout << "Error in move '"
              << cmd
              << "': Illegal to move onto your own piece\n";
      else if (e == 3)
         cout << "Error in move '"
              << cmd
              << "': Piece not present in source coordinate\n";
      else if (e == 4)
         cout << "Error in move '"
              << cmd
              << "': "
              << "Invalid specification of destination coordinates\n";
      else if (e == 5)
         cout << "Error in move '"
              << cmd
              << "': Unknown promotion piece specification\n";
      else if (e == 6)
         cout << "Error in move '"
              << cmd
              << "': Invalid specification of source coordinates\n";
      else if (e == 7)
         cout << "Error in move '"
              << cmd
              << "': Illegal move.  The piece cannot move to this location.\n";
      cout << "\tType ? for more options\n";
      return false;
   }
}

/*************************************************************************
 * BOARD: MOVE checks move for errors and special cases. Switches
 * current player if move is completely valid
 *************************************************************************/
bool Board::move()
{
   if (validMove())
      if(isValid())
      {
         moveSpecial();
         changePlayer();
         return true;
      }
      else
         return false;
   else
      return false;
   
}

/*************************************************************************
 * BOARD: VALID MOVE gets possible moves from source piece and checks
 * against destination
 *************************************************************************/
bool Board::validMove()
{
      // set coordinates to proper array position
      int sr = 56 - (int)cmd[1]; // set source array row
      int sc = (int)cmd[0] - 97; // set source array column
      int dr = 56 - (int)cmd[3]; // set destination array row
      int dc = (int)cmd[2] - 97; // set destination array column
      char s = cmd[4];
      char name = pieces[sr][sc]->getName();      
      char ownerMap[8][8]; // so pieces can see where other pieces are

      // only check if coordinates are valid board locations
      if ((sr >= 0) && (sr <= 7) && (dr >=0) && (dr <= 7)) // valid rows
           if ((sc >= 0) && (sc <= 7) && (dc >= 0) && (dc <= 7)) // valid columns
           {
              // set up piece map to be passed in
              for (int r = 0; r < 8; r++)
              {
                 for (int c = 0; c < 8; c++)
                    ownerMap[r][c] = pieces[r][c]->getOwner();
              }
              // ignore invalid coordinates
              // check move for that piece
              
              if (ownerMap[sr][sc] != 'n')
                 if (pieces[sr][sc]->getMoves(sr, sc, dr, dc, ownerMap))
                    return true;
                 else
                    throw 7;
           }
      return true;
}

/*************************************************************************
 * BOARD: VALID FILE plugs file input to checks for movements
 * and handles any possible errors for file input
 *************************************************************************/
bool Board::validFile(string fileName)
{
   try
   {
      if (move())
         return true;
   }
   catch (int e)
   {
      if (e == 1)
         cout << "ERROR in file "
              << fileName
              << " with move '"
              << cmd
              << "': Illegal to move your opponent's piece\n";         
      else if (e ==2)
         cout << "ERROR in file "
              << fileName
              << " with move '"
              << cmd
              << "': Illegal to move onto your own piece\n";
      else if (e == 3)
         cout << "ERROR in file "
              << fileName
              << " with move '"
              << cmd
              << "': Piece not present in source coordinate\n";
      else if (e == 4)
         cout << "ERROR in file "
              << fileName
              << " with move '"
              << cmd
              << "': "
              << "Invalid specification of destination coordinates\n";
      else if (e == 5)
         cout << "ERROR in file "
              << fileName
              << " with move '"
              << cmd
              << "': Unknown promotion piece specification\n";
      else if (e == 6)
         cout << "ERROR in file "
              << fileName
              << " with move '"
              << cmd
              << "': Invalid specification of source coordinates\n";
      else if (e == 7)
         cout << "ERROR in file "
              << fileName
              << " with move '"
              << cmd
              << "': Illegal move.  The piece cannot move to this location.\n";
      return false;
   }   
}

/*************************************************************************
 * BOARD: IS VALID
 * determines if a move is valid, or if a command is valid
 *************************************************************************/
bool Board::isValid()
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
                (cmd[4] == 'c') || (cmd[4] == 'C') || (cmd[4] == 'E') ||
                (cmd[4] == 'b') || (cmd[4] == 'r') || (cmd[4] == 'n') ||
                (cmd[4] == 'q') || (cmd[4] == 'k'))
               if (cmd[3] >= '1' && cmd[3] <= '8')
                  if (pieces[sr][sc]->getOwner() != 'n')
                     if (pieces[sr][sc]->getOwner() != pieces[dr][dc]->getOwner())
                        if(player[1] == pieces[sr][sc]->getOwner())
                           return true;
                        else
                           throw 1;
                     else
                        throw 2;
                  else
                     throw 3;
               else
                  throw 4;      
            else
               throw 5;      
   }
   else
      throw 6;
   return false;
}

/*************************************************************************
 * BOARD: MOVE SPECIAL
 * executes special moves like promotions, en passant, etc.
 *************************************************************************/
void Board::moveSpecial()
{
   int sr = 56 - (int)cmd[1]; // set source array row
   int sc = (int)cmd[0] - 97; // set source array column
   int dr = 56 - (int)cmd[3]; // set destination array row
   int dc = (int)cmd[2] - 97; // set destination array column
   
   
   if (cmd[4] != '\0')
   {
      char special = cmd[4];
      char name = pieces[sr][sc]->getName();
      char id = pieces[sr][sc]->getID();
      char owner = pieces[sr][sc]->getOwner();
      
      if (special == 'E')
      {
         // en passant
         if (id == 'p')
            pieces[dr + 1][dc] = &s;
         else if (id == 'P')
            pieces[dr - 1][dc] = &s;
      }
      else if (special == 'c')
      {
         // short castle
         if (name == 'K')
            if (dc == 6)
               if (pieces[dr][7]->getName() == 'R')
                  if (pieces[dr][7]->getOwner() == owner)
                  {
                     if (dr == 0)
                        pieces[dr][dc - 1] = &r1;
                     else if (dr == 7)
                        pieces[dr][dc - 1] = &r2;
                     pieces[dr][7] = &s;
                  }
      }
      else if (special == 'C')
      {
         // long castle
         if (name == 'K')
            if (dc == 2)
               if (pieces[dr][0]->getName() == 'R')
                  if (pieces[dr][0]->getOwner() == owner)
                  {
                     if (dr == 0)
                        pieces[dr][dc + 1] = &r1;
                     else if (dr == 7)
                        pieces[dr][dc + 1] = &r2;
                     pieces[dr][0] = &s;
                  }
      }
      // pawn promotions
      else if (special == 'Q')
      {
         // promotion to queen
         if (name == 'p')
            if (dr == 0)
               pieces[sr][sc] = &q2;
            else if (dr == 7)
               pieces[sr][sc] = &q1;
         
      }
      else if (special == 'R')
      {
         // promotion to rook
         if (name == 'p')
            if (dr == 0)
               pieces[sr][sc] = &r2;
            else if (dr == 7)
               pieces[sr][sc] = &r1;
         
      }
      else if (special == 'N')
      {
         // promotion to knight
         if (name == 'p')
            if (dr == 0)
               pieces[sr][sc] = &n2;
            else if (dr == 7)
               pieces[sr][sc] = &n1;
         
      }
      else if (special == 'B')
      {
         // promotion to bishop
         if (name == 'p')
            if (dr == 0)
               pieces[sr][sc] = &b2;
            else if (dr == 7)
               pieces[sr][sc] = &b1;
         
      }      
   }
}
