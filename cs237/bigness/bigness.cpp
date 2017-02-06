/***********************************************************************
 * Program:
 *    Exploration 3, Bigness
 *    Brother Neff, CS237
 *
 * Author:
 *    Brady Field
 *
 * Summary:
 *    RSA Encryption/Decryption Function Definitions using ZZ 
 *
 ***********************************************************************/

#include <cassert>
#include <cstdlib>
#include <NTL/ZZ.h>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <string>

NTL_CLIENT

/*****************************************************************************
 * Find b^n % m.
 *****************************************************************************/
ZZ modPow(ZZ b, ZZ n, ZZ m)
{
   // use the NTL library's built in functionality for
   // an elegant and optimized solution
   return PowerMod(b % m, n, m);
}

/*****************************************************************************
 * Find s such that a * s is congruent to 1 (mod m).
 *****************************************************************************/
ZZ findInverse(ZZ a, ZZ m)
{
   // the NTL library has a nice implementation
   // of finding modular inverses
   return InvMod(a, m);
}

/****************************************************************************
 * Convert from a text message representing a base 27 number to a ZZ number.
 ****************************************************************************/
ZZ fromBase27(string message)
{
   // used for base arithmetic
   ZZ ZZ_27 = to_ZZ(27);
   // resulting number
   ZZ base10;
   for (int i = 0; i < message.size(); i++)
   {
      // go through and sum up all the power positions of the numbers
      // also use the power method of NTL library to support large numbers
      base10 += to_ZZ((message[i] - '@') * power(ZZ_27, message.size()-i-1));
   }
   return base10;
}

/****************************************************************************
 * Convert from a ZZ number to a base 27 number represented by a text message.
 ****************************************************************************/
string toBase27(ZZ n)
{
   string base27;
   // convert using standard base conversion method
   // ASCII @ and A - Z are valid characters
   // use an insert to place most significant digits at beginning
   // or we would have to reverse the string at the end for the right
   // order
   for (;n > 0; base27.insert(0, 1, (n % 27) + '@'), n /= 27);
   return base27;
}

/****************************************************************************
 * Find a suitable e for a ZZ number that is the "totient" of two primes.
 ****************************************************************************/
ZZ findE(ZZ t)
{
   // 3 is the first possible solution
   ZZ relPrime = to_ZZ(3);
   // only check odd numbers
   for (;GCD(relPrime, t) != 1; relPrime += 2);
   return relPrime;
}

/*****************************************************************************
 * Find suitable primes p and q for encrypting a ZZ number that is the message.
 *****************************************************************************/
void findPandQ(ZZ m, ZZ& p, ZZ& q)
{
   // use the square root to ensure that
   // when multiplied together, our two primes 
   // will be larger than our message
   NextPrime(p, SqrRoot(m));
   NextPrime(q, p + 1);
}

/*************************************************************************
 * What was learned.
 *************************************************************************/
void learned()
{
   cout << "\tI was thinking that I would have to manually program the Chinese Remainder Theorem,\n"
        << "the Extended Euclidean Algorithm, Fermat’s Little Theorem, and then hook them up to get\n" 
        << "the parts I needed for doing RSA Encryption. After studying the NTL documentation, I found\n" 
        << "that these things had already been implemented. In fact, I could get all the parts I needed\n" 
        << "for RSA by calling functions that use these algorithms in very efficient ways. Even the prime\n" 
        << "number generation was relatively trivial. I was thinking that I would have to run a loop to generate\n" 
        << "some big numbers and then use Fermat’s Little Theorem to test it for primality, but the NTL had\n" 
        << "several options for prime generation that was much more efficient than what I had in mind.\n" 
        << "The RSA Theory PDF file was helpful in learning how RSA works.  On page 2 it made a reference to the\n" 
        << "Chinese Remainder Theorem.\n\n"
        << "\tI was most worried about generate my prime numbers, and my first algorithm was inefficient. I was generating\n" 
        << "primes, multiplying them together and then comparing their product to my message to see if it was big enough to\n" 
        << "use without losing the one-to-one functionality of my modulus. This worked for small messages, but not for big ones.\n" 
        << "Bro. Neff helped me out by showing me that I could generate a prime starting from a requested number. By using the\n" 
        << "square root of my message as a starting number and then getting the next two primes, I could mathematically ensure that\n" 
        << "their product would be larger than my message without using checks or loops. This worked much more quickly than my\n" 
        << "original implementation.\n\n"
        << "\tAlso, I ran into a little hiccup whilst converting from a base 27 number into a base 10 number. I was using\n" 
        << "the pow function from the cmath library and it takes an int data type which is too small for some of the exponents\n" 
        << "I needed. The NTL library had its own version of exponentiation supporting large numbers called the power function.\n" 
        << "I used this and everything went smoothly.\n\n"
        << "\tAll in all, I think the biggest thing I learned was that you need to take adequate time before coding to familiarize\n" 
        << "yourself with the tools at your disposal. Don’t reinvent the wheel. If we hadn’t been directed to carefully study\n" 
        << "the NTL library I would have attempted to write out all of the necessary algorithms myself instead of using what was\n" 
        << "at my fingertips. These implementations were far superior and a lot more efficient than what I would have done.\n" 
        << "Take time to get to know your tools before you decide to design. Also your first idea isn’t the best one. It should\n" 
        << "be revised. One can rework things or get another’s perspective on them to improve the effectiveness\n" 
        << "of one’s implementation. This was a very fun and rewarding project.";
  
}

/*************************************************************************
 * How to use this program.
 *************************************************************************/
void usage(const char* programName)
{
   cout << "usage: bigness parameters\n\n parameters should be either a string to be encrypted,"
        << " or the resulting numbers for decryption\n"
        << "e.g. bigness [message] (encryption) or \n"
        << "     bigness [encrypted values] [keys] (decryption)\n";
}
