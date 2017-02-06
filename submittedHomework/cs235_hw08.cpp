/***********************************************************************
* Program:
*    Homework 08, Polynomials
*    Brother Twitchell, CS 235
* Author:
*    Brady Field
* Summary: 
*    This program reads two polynomials from a file, displays them,
*    adds them together, evaluates the result for a given value of x and
*    displays the result.
***********************************************************************/
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <math.h>
using namespace std;

/******************************************************************************
*  Author: Brother Cameron, 10/9/2001
*
*  Purpose: Defines classes for a Term and a Polynomial
******************************************************************************/
class Term
{
   private:
      float coeff;
      int expon;
 
   public:
      Term();                  // --- Creates empty Term
      Term(float c, int e);    // --- Creates Term object with coeff. c 
                               //and expon. e
      float getCoeff(void);    // --- returns coeff of term
      int getExpon(void);      // --- returns expon of term
      void setCoeff(float c);  // --- sets term's coeff. to c
      void setExpon(int c);    // --- sets term's expon to c
};

/***********************************************************************
* Class containing an array of Terms and the functions to operate on them
***********************************************************************/
class Poly
{
   private:
      int numTerms;            // number of terms in polynomial
      int maxItems;            // array capacity
      Term *terms;             // dynamically allocated array of terms

   public:
      Poly();                  // creates empty polynomial
      Poly(const Poly &poly);  // copy constructor
      ~Poly();                 // destructor free dynamically allocate ptrs.
      void insertTerm(Term t); // inserts Term t into polynomial
      int getNumTerms(void);   // returns number of terms in array
      Term getTerm(int index); // returns term at index
      Poly& operator = (const Poly& rightSide);//overloaded assignment operator
      float operator () (float x);
};

ostream& operator << (ostream& outFile, Poly& op1);
istream& operator >> (istream& inFile, Poly& op1);
Poly operator + (Poly& op1, Poly& op2);


/***********************************************************************
* Main reads the file, outputs the polynomials, adds them together and
* displays the results.  Don't modify this function!!!!!
***********************************************************************/
int main(int argc, char* argv[])
{
   ifstream inFile;
   inFile.open(argv[argc - 1]);
   if (inFile.fail())
   {
      cout << "open file error " << argv[argc - 1] << endl;
      exit(1);
   }
   
   Poly f;
   Poly g;
   Poly p;

   int value (0); // value of x for evaluation
   inFile >> f;
   inFile >> g;

   cout << "F(x) =  " << f << endl;
   cout << "G(x) =  " << g << endl;

   // make copies of the polynomials
   Poly temp1(f);
   Poly temp2(g);

   // add polynomials f and g
   p = f + g;
   cout << "\nP(x) = (F + G)(x) = " << p << endl;

   // read in a value for X
   inFile >> value;

   // evaluate the polynomial
   cout << "P(" << value << ") = " << p(value) << endl << endl;

   // swap temp1 and temp2 - shouldn't change f & g
   Poly temp3(temp2);
   temp2 = temp1;
   temp1 = temp3;

   // Insert a new term 8x^6
   temp1.insertTerm(Term(8,6));

   cout << "temp1(x) is same as 8x^6 + G(x) or " << temp1 << endl;
   cout << "temp2(x) is same as F(x) or " << temp2 << endl;
   cout << "temp3(x) is same as G(x) or " << temp3 << endl << endl;

   cout << "Original functions were:" << endl;
   cout << "F(x) =  " << f << endl;
   cout << "G(x) =  " << g << endl;

   inFile.close();
   return 0;
}

/*****************************************************************************
*
*  Function: Term
*
*  Parameters - none
*  Return Value - none
*
*  Purpose - Constructor function for Term class.  Creates empty Term.
****************************************************************************/
Term::Term(void)
{
   coeff = 0.0;
   expon = -1;  // --- guarantees insert will occur
}

/*****************************************************************************
*
*  Function: Term
*
*  Parameters - a float that is the coefficient and a int that is the expon.
*  Return Value - None
*
*  Purpose: Creates a Term object set to coefficient and expon.
****************************************************************************/
Term::Term(float c, int e)
{
   coeff = c;
   expon = e;
}

/*****************************************************************************
*
*  Function: getCoeff
*
*  Parameters: None
*  Return Value - an integer representing coeff.
*
*  Purpose: Returns the coefficient data member of Term class
****************************************************************************/
float Term::getCoeff(void)
{
   return (coeff);
}

/***************************************************************************
*  Function: getExpon
*  Purpose: Returns the expon data member of Term class
*
*  Parameters - none
*  Return value - integer, representing expon.
***************************************************************************/
int Term::getExpon(void)
{
   return (expon);
}

/***************************************************************************
*  Function: setCoeff
*  Purpose: sets c to data member coeff in Term class
*
*  Parameters - float representing coeff
*  Return value - none
**************************************************************************/
void Term::setCoeff(float c)
{
   coeff = c;
}

/***************************************************************************
*  Function: setExpon
*  Purpose: sets e to data member expon in Term class
*
*  Parameters - int representing expon
*  Return value - none
**************************************************************************/
void Term::setExpon(int e)
{
   expon = e;
}

/***************************************************************************
*
*  Function: Poly
*  Purpose:  Poly class constructor to create an empty Poly object of 50 
*            term.
*
*  Parameters - none
*  Return value - none
**************************************************************************/
Poly::Poly()
{
   numTerms = 0;
   terms = new Term [50];
   maxItems = 50;
}

/********************************************
 * Destructor
 *********************************************/
Poly::~Poly()
{
   delete terms;
}

/*******************************************
 * copy constructor
 ********************************************/
Poly::Poly(const Poly &poly)
{
   terms = new Term [50];
   *this = poly;
}

/*******************************************
 * overloaded Assignment operator
 ********************************************/
Poly& Poly::operator = (const Poly &rightSide)
{
   
   delete terms;
   terms = new Term [50];
   numTerms = rightSide.numTerms;
   maxItems = rightSide.maxItems;
   for (int i = 0; i < numTerms; i++)
      terms[i] = rightSide.terms[i];
}




/***********************************************************************
* Inserts a term into a polynomial in the proper location.  If a term
* is inserted with a duplicate exponent, the terms are combined.  If any
* coefficient goes to zero that term is removed from the polynomial.
***********************************************************************/
void Poly::insertTerm(Term t)
{
   // insert new term
   terms[numTerms] = t;
   numTerms++;
   // reorder terms with swap sort
   for (int i = 0; i < numTerms - 1; i++)
      for (int j = 0; j < numTerms - 1; j++)
      {
         int a = terms[j].getExpon();
         int b = terms[j + 1].getExpon();
         if (a < b) //swap
         {
            Term a = terms[j];
            terms[j] = terms[j + 1];
            terms[j + 1] = a;
         }
      }
   
}

/***********************************************************************
* Accessor function that returns the number of Terms in the array
***********************************************************************/
int Poly::getNumTerms()
{
   return (numTerms);
}

/***********************************************************************
* Accessor function that returns the Term at a given index
***********************************************************************/
Term Poly::getTerm(int index)
{
   return (terms[index]);
}

/***********************************************************************
* overloaded () operator that evaluates the polynomial for the value
* within the parentheses
***********************************************************************/
float Poly::operator () (float x)
{
   float result = 0;
   for (int i = 0; i < numTerms; i++)
      result += (terms[i].getCoeff() * pow(x, terms[i].getExpon()));
      
   return result;
}

/***********************************************************************
* overloaded + operator that combines two polynomials and returns the
* result as a polynomial
***********************************************************************/
Poly operator + (Poly& op1, Poly& op2)
{
   Poly poly1;
   Poly poly2;
   Term term;
   
   // fill poly
   for (int i = 0; i < op1.getNumTerms(); i++)
      poly1.insertTerm(op1.getTerm(i));
   for (int i = 0; i < op2.getNumTerms(); i++)
      poly1.insertTerm(op2.getTerm(i));
   // combine like terms
   for (int i = 0; i < poly1.getNumTerms(); i++)
   {
      int a = poly1.getTerm(i).getExpon();
      int b = poly1.getTerm(i + 1).getExpon();
      if (a == b) // combine same coefficients
      {
         float coeff = poly1.getTerm(i).getCoeff() + 
               poly1.getTerm(i + 1).getCoeff();
         if (coeff != 0)
         {
            term.setCoeff(coeff);
            term.setExpon(a);
            poly2.insertTerm(term);          
         }
         i++; // increase counter to skip over combined term
      }
      else // insert term
         poly2.insertTerm(poly1.getTerm(i));
   }
   
   return poly2;
}

/***********************************************************************
* overloaded << operator that outputs the polynomial in the proper format
***********************************************************************/
ostream& operator << (ostream& outFile, Poly& op1)
{
   float coeff;
   int expon;
   
   for (int i = 0; i < op1.getNumTerms(); i++)
   {
      coeff = op1.getTerm(i).getCoeff();
      expon = op1.getTerm(i).getExpon();
      
      // output next operator
      if (coeff < 0)
      {
         if (i != 0)
            cout << " - "; 
         else
            cout << "-";
         if (expon == 0 || coeff != -1)
            cout << coeff * -1;
      }
      else
      {
         if (i != 0)
            cout << " + ";
         if (expon == 0 || coeff != 1)
            cout << coeff;
      }
      
      if (expon == 0) // output variable with exponents
         ;
      else if (expon == 1)
         cout << "x";
      else
         cout << "x^" << expon;
   }
   return outFile; // return the out stream to allow for linking
}

/***********************************************************************
* overloaded >> operator that reads an entire polynomial into an array
* of Terms in the proper order.
***********************************************************************/
istream& operator >> (istream& inFile, Poly& op1)
{
   int numTerms;
   float coeff;
   int expon;
   Term term;
   
   inFile >> numTerms;
   
   for (int i = 0; i < numTerms; i++)
   {
      inFile >> coeff;
      term.setCoeff(coeff);
      inFile >> expon;
      term.setExpon(expon);
      op1.insertTerm(term);
   }
}
