// This is the header file complex.h
// This is the structure used in the main program
// The prototypes are conatined here as well

#ifndef COMPLEX_H
#define COMPLEX_H
#include <iostream>
using namespace std;

struct Complex
{
   double real;
   double imaginary;
};

void prompt(Complex &complex);
void display(const Complex &complex);
void addTo(Complex &lhs, const Complex &rhs);

/*************************************************************
 * IS ZERO: Is the current number zero?
 *   INPUT:  complex number to check
 *   OUTPUT: return whether it is zero
 ************************************************************/
inline bool isZero(const Complex &num)
{
   return (num.real == 0.0 && num.imaginary == 0.0);
}
#endif // COMPLEX_H
