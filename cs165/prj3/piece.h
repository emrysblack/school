// Header file for all different
// types of pieces used
// in the Chess game

#ifndef PIECE_H
#define PIECE_H
#include <vector>
using namespace std;

class Piece
{
  public:
   void setName(char text) { name = text; };
   char getName() { return name; };
   void setID(char text) { id = text; };
   char getID() { return id; };
   char getOwner() { return owner; };
   void setOwner(char text) { owner = text; };
   virtual bool getMoves(int r, int c, int dr, int dc,
                         const char ownerMap[8][8]);
  private:
   char name;
   char id;
   char owner;   
};

class Space : public Piece
{
  public:
   Space() { setName(' '); setID(' '); setOwner('n'); };
   bool getMoves(int r, int c, int dr, int dc,
                 const char ownerMap[8][8]);
};

class Pawn : public Piece
{
  public:
   Pawn() { setName('p'); };
   bool getMoves(int r, int c, int dr, int dc,
                 const char ownerMap[8][8]);
};

class Knight : public Piece
{
  public:
   Knight() { setName('N'); };
   bool getMoves(int r, int c, int dr, int dc,
                 const char ownerMap[8][8]);
};

class Bishop : public Piece
{
  public:
   Bishop() { setName('B'); };
   bool getMoves(int r, int c, int dr, int dc,
                 const char ownerMap[8][8]);
};

class Rook : public Piece
{
  public:
   Rook() { setName('R'); };
   bool getMoves(int r, int c, int dr, int dc,
                 const char ownerMap[8][8]);
};

class Queen : public Piece
{
  public:
   Queen() { setName('Q'); };
   bool getMoves(int r, int c, int dr, int dc,
                 const char ownerMap[8][8]);
};

class King : public Piece
{
  public:
   King() { setName('K'); };
   bool getMoves(int r, int c, int dr, int dc,
                 const char ownerMap[8][8]);
};

#endif // PIECE_H
