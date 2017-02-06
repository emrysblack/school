/***************************************************************************
 * Program:
 *    Relations as Connection Matrices
 * Author:
 *    You
 * Purpose:
 *    Exploring and enhancing an implementation of a
 *    representation of relations to discover their basic properties.
 *
 * Summary:
 *    Represents relations as connection (zero-one) matrices, and provides
 *    functionality for testing properties of relations.
 *
 *    NOTE: deliberately (mostly) uncommented!
 *
 ***************************************************************************/
#include <cmath>
#include <iostream>
#include <fstream>
#include <iomanip>
#include "words.h"
using namespace std;

class Relation operator*(const Relation& r1, const Relation& r2);
bool operator<=(const Relation& r1, const Relation& r2);

class Relation
{
private:
   bool** mMatrix;
   int mSize;
   
   // members for easy attribute checking
   bool reflexive;
   bool irreflexive;
   bool antisymmetric;
   bool nonreflexive;
   bool symmetric;
   bool asymmetric;
   bool transitive;
   
   void init()
   {
      mMatrix = new bool*[mSize];
      for (int i = 0; i < mSize; i++)
      {
         mMatrix[i] = new bool[mSize];
      }
   }

public:
   Relation(int size)
   {
      mSize = size;
      init();
   }

   Relation& operator=(const Relation& rtSide)
   {
      if (this == &rtSide)
      {
         return *this;
      }
      else
      {
         mSize = rtSide.mSize;
         for (int i = 0; i < mSize; i++)
         {
            delete [] mMatrix[i];
         }
         delete [] mMatrix;
         init();
         for (int x = 0; x < mSize; x++)
         {
            for (int y = 0; y < mSize; y++)
            {
               mMatrix[x][y] = rtSide[x][y];
            }
         }
      }
      return *this;
   }

   Relation(const Relation& relation)
   {
      mSize = relation.getConnectionMatrixSize();
      init();
      *this = relation;
   }

   ~Relation()
   {
      for (int i = 0; i < mSize; i++)
      {
         delete [] mMatrix[i];
      }
      delete [] mMatrix;
   }

   int getConnectionMatrixSize() const
   {
      return mSize;
   }

   bool* operator[](int row) const
   {
      return mMatrix[row];
   }

   bool operator==(const Relation& relation)
   {
      int size = relation.getConnectionMatrixSize();
      if (mSize != size)
      {
         return false;
      }
      for (int i = 0; i < size; i++)
      {
         for (int j = 0; j < size; j++)
         {
            if (mMatrix[i][j] != relation[i][j])
            {
               return false;
            }
         }
      }
      return true;
   }
   
   /*************************************************************************
    *  Implimented a new function to take care of setting the attributes
    *  and then set functions to return the correspnding attribute
    ************************************************************************/
   void computeAttributes()
   {
      reflexive = true;
      irreflexive = true;
      symmetric = true;
      antisymmetric = true;

      // only run through the matrix one time,
      // checking as many attributes as possible
      // to reduce the need for unnecessary
      // repetition
      for (int i = 0; i < mSize; i++)
      {
         // reflexive and irreflexive
         if (!mMatrix[i][i] && reflexive)
         {
            reflexive = false;
         }
         
         else if (mMatrix[i][i] && irreflexive)
         {
            irreflexive = false;
         }
         
         // symmetric and antisymmetric
         for (int j = 0; j < mSize; j++)
         {
            if (mMatrix[i][j] && mMatrix[j][i] && i != j && antisymmetric)
            {      
               antisymmetric = false;
            }
            
            else if (mMatrix[i][j] != mMatrix[j][i] && symmetric)
            {      
               symmetric = false;
            }
         }
      }

      // nonreflexive
      nonreflexive = !reflexive && !irreflexive;
      
      // asymmetric
      asymmetric = antisymmetric && irreflexive;

      // transitive
      // is the square is less than or equal to the original?
      transitive = *this * *this <= *this;
      
   }
   
   // these are getters for the benefit of possible non-member inquiries
   bool isReflexive() const
   {            
      return reflexive;
   }

   bool isIrreflexive() const
   {     
      return irreflexive;
   }

   bool isNonreflexive() const
   {
      return nonreflexive;
   }

   bool isSymmetric() const
   {
      return symmetric;
   }

   bool isAntisymmetric() const
   {
      return antisymmetric;
   }

   bool isAsymmetric() const
   {
      return asymmetric;
   }

   bool isTransitive() const
   {
      return transitive;
   }
  
   void describe();
};

// binary multiplication operator for matricies
Relation operator*(const Relation& r1, const Relation& r2)
{
   // set up size for product
   const int size = r1.getConnectionMatrixSize();
   Relation product(size);
   for (int i = 0; i < size; i++)
   {
      for (int j = 0; j < size; j++)
      {
         product[i][j] = false;
         for (int k = 0; k < size && !product[i][j]; k++)
         {
            product[i][j] = r1[k][j] && r2[i][k];
         }
      }
   }
   return product;
}

// comparison for matricies
bool operator<=(const Relation& r1, const Relation& r2)
{
   // set up size
   const int size = r1.getConnectionMatrixSize();
   if (size != r2.getConnectionMatrixSize())
   {
      return false;
   }
   for (int i = 0; i < size; i++)
   {
      for (int j = 0; j < size; j++)
      {
         if (r1[i][j] > r2[i][j])
         {
            return false;
         }
      }
   }
   return true;
}

ostream& operator<<(ostream& os, const Relation& relation)
{
   int n = relation.getConnectionMatrixSize();
   for (int i = 0; i < n; i++)
   {
      for (int j = 0; j < n; j++)
      {
         os << relation[i][j] << " ";
      }
      os << endl;
   }
   return os;
}

istream& operator>>(istream& is, Relation& relation)
{
   int n = relation.getConnectionMatrixSize();
   for (int i = 0; i < n; i++)
   {
      for (int j = 0; j < n; j++)
      {
         is >> relation[i][j];
      }
   }
   return is;
}

void Relation::describe()
{
   computeAttributes();
   cout << "\nThe relation represented by the " << mSize << "x" << mSize << " matrix\n";
   cout << *this << "is\n";
   cout << (reflexive ? "" : "NOT ") << "Reflexive;\n";
   cout << (irreflexive ? "" : "NOT ") << "Irreflexive;\n";
   cout << (nonreflexive ? "" : "NOT ") << "Nonreflexive;\n";
   cout << (symmetric ? "" : "NOT ") << "Symmetric;\n";
   cout << (antisymmetric ? "" : "NOT ") << "Antisymmetric;\n";
   cout << (asymmetric ? "" : "NOT ") << "Asymmetric; and\n";
   cout << (transitive ? "" : "NOT ") << "Transitive.\n";
}

/*************************************************************************
 * runOne
 *
 * is a global function declared in /home/cs238/close/closenessCLI.cpp
 * and implemented here.
 *
 * It serves as the interface between the CLI and the Relation class.
 *************************************************************************/
void runOne(string file)
{
   ifstream inFile(file.c_str());

   if (inFile.is_open())
   {
      int size;
      inFile >> size;
      Relation relation(size);
      inFile >> relation;
      inFile.close();
      relation.describe();
   }
   else
   {
      cout << "Unable to open " << file << ".\n";
   }
}

/*************************************************************************
 * learned
 *
 * Tells interested parties what you learned.
 *
 * Use one or more calls to out(...), or else use the whatIlearned
 * script and do the following:
 *
 *   Words words = {
 *   #include "whatIlearned.inc"
 *   nl};
 *   cout << words;
 *   I tried to use the words script provided. It worked up to a point. 
 *   After a certain amount of characters it resulted in a segmentation
 *   fault.
 *************************************************************************/
void learned()
{
   cout << "\n\tThis was a fun exploration. It was a nice review of matrices. This\n"
        << "was the first time I've had exposure to binary matrices. I think the\n" 
        << "hardest part of this exploration was detecting transitivity. I was\n" 
        << "most grateful for the hint in the exploration instructions.  Initially,\n" 
        << "I went about solving this problem using a triple-nested for-loop. I\n" 
        << "then changed my approach to use the square of the matrix to determine\n" 
        << "transitivity. Although, I still had to use a triple-nested for-loop to\n" 
        << "actually square the matrix. As always, I loved optimizing the code to\n" 
        << "make it look elegant and run smoothly. This was a rewarding\n" 
        << "exploration.\n\n";
}

/*************************************************************************
 * usage
 *
 * Tells the user how to use the program.
 *************************************************************************/
void usage(const char * programName)
{
   cout << "usage: " << programName << " [file to open]\n";
   cout << "e.g. " << programName << " exampleInputFile.in\n";
}
