// conatins function definitions
// for piece class and all
// subclasses

#include <vector>
#include <string>
#include "piece.h"
using namespace std;

/**********************************************
 * PIECE: GET MOVES
 * should never be called. redefined for all
 * subclasses
 **********************************************/
bool Piece::getMoves(int r, int c, int dr, int dc,
                     const char ownerMap[8][8])
{
   return true;
}

/**********************************************
 * PIECE: GET MOVES
 * should never be called. redefined for all
 * subclasses
 **********************************************/
bool Space::getMoves(int r, int c, int dr, int dc,
                     const char ownerMap[8][8])
{
   return true;
}

/**********************************************
 * PAWN: GET MOVES
 * fills vector with possible pawn moves
 **********************************************/
bool Pawn::getMoves(int r, int c, int dr, int dc,
                    const char ownerMap[8][8])
{
   int numSpaces;
   char owner = ownerMap[r][c];
   bool firstMove = false;
   if (owner == 'W')
   {
      if (r == 6)
         firstMove = true;
      numSpaces = -1;
   }
   else if (owner == 'B')
   {
      if (r == 1)
         firstMove = true;
      numSpaces = 1;
   }
   if (ownerMap[dr][dc] == 'n')
   {
      if (c == dc)
      {
         if (r + numSpaces == dr) // normal move
            return true;
         else if (firstMove)
            if (r + numSpaces * 2 == dr) // first move
               return true;
      }
      else if ((c + 1 == dc) || (c - 1 == dc)) // en passant
      {
         if (c + 1 == dc) // right
         {
            if (r + numSpaces == dr)
               if (ownerMap[r][c + 1] != owner)
                  if (ownerMap[r][c + 1] != 'n')
                     return true;
         }
         else if (c - 1 == dc) // left
         {
            if (r + numSpaces == dr)
               if (ownerMap[r][c - 1] != owner)
                  if (ownerMap[r][c - 1] != 'n')
                     return true;
         }
      }
   }
   else
   {
      
      if ((c + 1 == dc) || (c - 1 == dc))
      {
         if (r + numSpaces == dr)
            if (c + 1 == dc) // capture right
               return true;
            else if (c - 1 == dc) // capture left
               return true;
      }
      
   }
   return false;
}

/**********************************************
 * ROOK: GET MOVES
 * fills vector with possible rook moves
 **********************************************/
bool Rook::getMoves(int r, int c, int dr, int dc,
                    const char ownerMap[8][8])
{
   if ((c == dc) && (r != dr)) // move up or down
   {
      int numSpaces = dr - r; // spaces between rook and goal
      if (numSpaces > 0)
         for (int i = 1; i < numSpaces; i++) // move down
         {
            if (ownerMap[r + i][c] != 'n')
               return false;
         }
      else if (numSpaces < 0)
         for (int i = -1; i > numSpaces; i--) // move up
         {
            if (ownerMap[r + i][c] != 'n')
               return false;
         }
      return true;
   }
   
   else if ((c != dc) && (r == dr)) // move right or left
   {
      int numSpaces = dc - c; // spaces between rook and goal
      if (numSpaces > 0)
         for (int i = 1; i < numSpaces; i++) // move right
         {
            if (ownerMap[r][c + i] != 'n')
               return false;
         }
      else if (numSpaces < 0)
         for (int i = -1; i > numSpaces; i--) // move left
         {
            if (ownerMap[r][c + i] != 'n')
               return false;
         }
      return true;
   }
   return false;
}

/**********************************************
 * KNIGHT: GET MOVES
 * fills vector with possible knight moves
 **********************************************/
bool Knight::getMoves(int r, int c, int dr, int dc,
                      const char ownerMap[8][8])
{
   // check all possible moving patterns
   if ((c + 1 == dc) || (c - 1 == dc)) // up two over one
   {
      if ((r + 2 == dr) || (r - 2 == dr))
         return true;
   }
   else if((c + 2 == dc) || (c - 2 == dc)) // up one over two
      if ((r + 1 == dr) || (r - 1 == dr))
         return true;
   return false;
}

/**********************************************
 * BISHOP: GET MOVES
 * fills vector with possible bishop moves
 **********************************************/
bool Bishop::getMoves(int r, int c, int dr, int dc,
                      const char ownerMap[8][8])
{
   if ((c != dc) && (r != dr)) // move diagonal
   {
      int tr = dr - r; // set target row
      int tc = dc - c; // set target column

      if ((tr == tc) || (tr + tc == 0)) // make sure is diagonal move
      {
         int numSpaces = tr; // spaces between bishop and goal
         if (numSpaces > 0)
         {
            if(tc > 0)
               for (int i = 1; i < numSpaces; i++) // move down and right
               {
                  if (ownerMap[r + i][c + i] != 'n')
                     return false;
               }
            else if (tc < 0)
               for (int i = 1; i < numSpaces; i++) // move down and left
               {
                  if (ownerMap[r + i][c - i] != 'n')
                     return false;
               }
         }
         else if (numSpaces < 0)
            {
            if(tc < 0)
               for (int i = -1; i > numSpaces; i--) // move up and left
               {
                  if (ownerMap[r + i][c + i] != 'n')
                     return false;
               }
            else if (tc > 0)
               for (int i = -1; i > numSpaces; i--) // move up and right
               {
                  if (ownerMap[r + i][c - i] != 'n')
                     return false;
               }
         }
         return true;
      }
   }
   return false;
}

/**********************************************
 * QUEEN: GET MOVES
 * fills vector with possible queen moves
 **********************************************/
bool Queen::getMoves(int r, int c, int dr, int dc,
                     const char ownerMap[8][8])
{
   if ((c == dc) && (r != dr)) // move up or down
   {
      int numSpaces = dr - r; // spaces between queen and goal
      if (numSpaces > 0)
         for (int i = 1; i < numSpaces; i++) // move down
         {
            if (ownerMap[r + i][c] != 'n')
               return false;
         }
      else if (numSpaces < 0)
         for (int i = -1; i > numSpaces; i--) // move up
         {
            if (ownerMap[r + i][c] != 'n')
               return false;
         }
      return true;
   }
   
   else if ((c != dc) && (r == dr)) // move right or left
   {
      int numSpaces = dc - c; // spaces between queen and goal
      if (numSpaces > 0)
         for (int i = 1; i < numSpaces; i++) // move right
         {
            if (ownerMap[r][c + i] != 'n')
               return false;
         }
      else if (numSpaces < 0)
         for (int i = -1; i > numSpaces; i--) // move left
         {
            if (ownerMap[r][c + i] != 'n')
               return false;
         }
      return true;
   }
   else if ((c != dc) && (r != dr)) // move diagonal
   {
      int tr = dr - r; // set target row
      int tc = dc - c; // set target column

      if ((tr == tc) || (tr + tc == 0)) // make sure is diagonal move
      {
         int numSpaces = tr; // spaces between bishop and goal
         if (numSpaces > 0)
         {
            if(tc > 0)
               for (int i = 1; i < numSpaces; i++) // move down and right
               {
                  if (ownerMap[r + i][c + i] != 'n')
                     return false;
               }
            else if (tc < 0)
               for (int i = 1; i < numSpaces; i++) // move down and left
               {
                  if (ownerMap[r + i][c - i] != 'n')
                     return false;
               }
         }
         else if (numSpaces < 0)
            {
            if(tc < 0)
               for (int i = -1; i > numSpaces; i--) // move up and left
               {
                  if (ownerMap[r + i][c + i] != 'n')
                     return false;
               }
            else if (tc > 0)
               for (int i = -1; i > numSpaces; i--) // move up and right
               {
                  if (ownerMap[r + i][c - i] != 'n')
                     return false;
               }
         }
         return true;
      }
   }
   return false;
}

/**********************************************
 * KING: GET MOVES
 * fills vector with possible king moves
 **********************************************/
bool King::getMoves(int r, int c, int dr, int dc,
                    const char ownerMap[8][8])
{   
   if (dc == c) // move up or down one
   {
      if ((dr - r == 1) || (dr - r == -1))
         return true;
   }
   else if (dr == r) // move right or left
   {
      if ((dc - c == 1) || (dc - c == -1))
         return true;
      else
      {
         if (c + 2 == dc) // short castle
         {
            if (ownerMap[dr][c + 1] == 'n')
               if (ownerMap[dr][dc] == 'n')
                  return true;
         }
         else if (c - 2 == dc) // long castle
            if (ownerMap[dr][c - 1] == 'n')
               if (ownerMap[dr][dc] == 'n')
                  if (ownerMap[dr][c - 3] == 'n')
                     return true;
      }
   }
   else // move diagonal
   {
      if ((dr - r == 1) || (dr - r == -1))
         if ((dc - c == 1) || (dc - c == -1))
            return true;
   }   
   return false;
}
