// This is the header
// file for the
// Chess Board class

#ifndef BOARD_H
#define BOARD_H
#include <string>
#include <vector>
#include "piece.h"
using namespace std;
class Board
{
  public:
   Board();
   void reset();
   void display();
   bool move();
   bool makeMove();
   bool isValid();
   bool validMove();
   void moveSpecial();
   bool validFile(string fileName);
   void movePiece();
   string getPlayer() { return player; };
   void changePlayer() { if (player == "(White)") player = "(Black)";
                             else player = "(White)"; };
   string cmd;
   bool test;
   bool done;
   vector <string> moves;
   
  private:
   bool isWhiteSquare[8][8]; // board colors
   Piece *pieces[8][8]; // position of pieces
   King k1; // all piece types, one
   King k2;
   Queen q1;
   Queen q2;
   Rook r1;
   Rook r2;
   Knight n1;
   Knight n2;
   Bishop b1;
   Bishop b2;
   Pawn p1;
   Pawn p2;
   Space s;
   string player;
};

#endif // BOARD_H
