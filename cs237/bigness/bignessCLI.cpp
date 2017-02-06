/*************************************************************************
 * Exploring the RSA Cryptosystem
 *************************************************************************/
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <NTL/ZZ.h>

NTL_CLIENT

/*************************************************************************
 * What was learned.
 *************************************************************************/
void learned();

/*************************************************************************
 * How to use this program.
 *************************************************************************/
void usage(const char *);

/*************************************************************************
 * Find b^n % m.
 *************************************************************************/
ZZ modPow(ZZ b, ZZ n, ZZ m);

/*************************************************************************
 * Find i such that a * i is congruent to 1 (mod m).
 *************************************************************************/
ZZ findInverse(ZZ a, ZZ m);

/*************************************************************************
 * Convert from a text message
 * representing a base 27 number to a ZZ number.
 *************************************************************************/
ZZ fromBase27(string message);

/*************************************************************************
 * Convert from a ZZ number to a base 27 number
 * represented by a text message.
 *************************************************************************/
string toBase27(ZZ n);

/*************************************************************************
 * Find a suitable e for a ZZ number that is the "totient" of two primes.
 *************************************************************************/
ZZ findE(ZZ t);

/*************************************************************************
 * Find suitable primes p and q
 * for encrypting a ZZ number that is the message.
 *************************************************************************/
void findPandQ(ZZ m, ZZ& p, ZZ& q);

/*************************************************************************
 * Replace all '@' characters in a string with ' ' (space) characters.
 *************************************************************************/
void replaceAllAtSignsWithSpaces(string& message)
{
   size_t index = 0;
   while ((index = message.find_first_of('@', index)) >= 0 &&
          index <= message.length())
   {
      message.replace(index++, 1, 1, ' ');
   }
}

/**************************************************************************
 * encrypts a message
 **************************************************************************/
void encrypt(string message)
{
   ZZ m = fromBase27(message);
   ZZ p;
   ZZ q;
   findPandQ(m, p, q);

   ZZ n = p * q;
   ZZ t = (p - 1) * (q - 1);
   ZZ e = findE(t);

   ZZ encrypted = modPow(m, e, n);

   cout << encrypted << " " << p << " " << q << " " << e << endl;

   replaceAllAtSignsWithSpaces(message);

   // output verbose results to standard error to not interfere with test
   cerr << endl
        << "Text (base 27) = " << message << endl
        << "Message        = " << m << endl
        << "Encrypted      = " << encrypted << endl
        << endl
        << "p = " << p << endl
        << "q = " << q << endl
        << "n = " << n << endl
        << "t = " << t << endl
        << "e = " << e << endl
        << endl;
}

/**************************************************************************
 * decrypts a message given two primes and the encryption exponent
 **************************************************************************/
void decrypt(ZZ p, ZZ q, ZZ e, ZZ encrypted)
{
   ZZ n = p * q;
   ZZ t = (p - 1) * (q - 1);
   ZZ d = findInverse(e, t);

   ZZ m = modPow(encrypted, d, n);

   string message = toBase27(m);

   replaceAllAtSignsWithSpaces(message);

   cout << message << endl;

   // output verbose results to standard error to not interfere with test
   cerr << endl
        << "Encrypted      = " << encrypted << endl
        << "Message        = " << m << endl
        << "Text (base 27) = " << message << endl
        << endl
        << "p = " << p << endl
        << "q = " << q << endl
        << "n = " << n << endl
        << "t = " << t << endl
        << "e = " << e << endl
        << "d = " << d << endl
        << endl;
}

/**************************************************************************
 * run drives the RSA Encryption/Decryption process.
 **************************************************************************/
void run(vector<string> args)
{
   if (isalpha(args[0][0])) // if message is alphabetic (encrypting)
   {
      // Get the message to encrypt
      string message;

      for (int i = 0; i < args.size(); i++)
      {
         for (int j = 0; j < args[i].size(); j++)
         {
            if (isalpha(args[i][j])) // Make sure chars are text
            {
               message += toupper(args[i][j]);
            }
            else
            {
               cerr << "\n--ERROR--  Can only use text and spaces.\n\n";
               exit(1);
            }
         }
         if (i != args.size() - 1) // if not the last word
         {
            message += "@";
         }
      }
      encrypt(message);
   }
   else // if message is a number (decrypting)
   {
      ZZ encrypted = to_ZZ(args[0].c_str());

      ZZ p = to_ZZ(args[1].c_str());
      ZZ q = to_ZZ(args[2].c_str());
      ZZ e = to_ZZ(args[3].c_str());

      decrypt(p, q, e, encrypted);
   }
}

/**************************************************************
 * main looks at its command-line parameters.
 * If none, it calls two functions in order, namely
 *   learned
 *   usage
 * Otherwise it calls run with the parameters recast as
 * a vector of strings.
 ***************************************************************/
int main(int argc, const char* argv[])
{
   if (argc == 1)
   {
      learned();
      usage(argv[0]);
   }
   else
   {
      vector<string> args;
      for (int i = 1; i < argc; i++)
      {
         args.push_back(string(argv[i]));
      }
      run(args);
   }
   return 0;
}   
