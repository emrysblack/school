// ercanbrack 165 assignment 1 data types and casting
#include <iostream>
#include <iomanip>
#include <cmath>
#include <limits>
#include <cfloat>
using namespace std;

void display(unsigned long long num);
bool hasOverflow(unsigned long long num, int bits);

/*********************************************************************
 * prompts for a number and calls display will keep re-prompting until  
 * user enters a q for quit
 *********************************************************************/
int main()
{
   unsigned long long num;
   char quit = 'z';
   do
   {
      cout << "\nEnter a number (q to quit): ";
      cin >> num;
      if (cin.fail())
      {
         cin.clear();
         cin >> quit;         
         cin.ignore(256, '\n');
      }
      else
      {
         display(num);
      }
   } while (quit != 'q');
   return 0;
}

/*********************************************************************
 * displays a header and then type casts into different data types
 * and displays capacity, data representiontions and overflow info for
 * for each item
 *********************************************************************/
void display(unsigned long long num)
{
   // display header
   cout << fixed << dec << endl;
   cout << "Original input value: " << num << endl << endl;
   cout << "   Data Type       Bytes      Value (Dec)           Value (Hex)";
   cout << "       Overflow\n";
   cout << "------------------ -----  --------------------  ---------------";
   cout << "-----  --------\n";
   // display data
   cout << left << setw(19) << "bool" << right << setw(3)
        << sizeof (bool) << setw(24) << dec << (bool)num
        << setw(22) << hex << (bool)num << setw(10) << "N/A\n";
   
   cout << left << setw(19) << "char" << right << setw(3)
        << sizeof (char) << setw(24) << dec;
   isalpha((char)num) ? cout << (char)num : cout << (int)(char)num;
   cout << setw(22) << hex << (int)(char)num << setw(8);
   (hasOverflow(num, sizeof (char) * 8 -1)) ? cout << "T\n" : cout << "F\n";

   cout << left << setw(19) << "unsigned char" << right << setw(3)
        << sizeof (unsigned char) << setw(24) << dec;
   isalpha ((unsigned char)num) ? cout << (unsigned char)num :
      cout << (int)(unsigned char) num;
   cout << setw(22) << hex;
   cout << (int)(unsigned char)num;
   cout << setw(8);
   (hasOverflow(num, sizeof (unsigned char) * 8)) ?
      cout << "T\n" : cout << "F\n";

   cout << left << setw(19) << "short" << right << setw(3)
        << sizeof (short) << setw(24) << dec << (short)num
        << setw(22) << hex << (short)num << setw(8);
   (hasOverflow(num, sizeof (short) * 8 -1)) ? cout << "T\n" : cout << "F\n";

   cout << left << setw(19) << "unsigned short" << right << setw(3)
        << sizeof (unsigned short) << setw(24) << dec << (unsigned short)num
        << setw(22) << hex << (unsigned short)num << setw(8);
   (hasOverflow(num, sizeof (unsigned short) * 8)) ?
      cout << "T\n" : cout << "F\n";

   cout << left << setw(19) << "int" << right << setw(3)
        << sizeof (int) << setw(24) << dec << (int)num
        << setw(22) << hex << (int)num << setw(8);
   (hasOverflow(num, sizeof (int) * 8 -1)) ? cout << "T\n" : cout << "F\n";

   cout << left << setw(19) << "unsigned int" << right << setw(3)
        << sizeof (unsigned int) << setw(24) << dec << (unsigned int)num
        << setw(22) << hex << (unsigned int)num << setw(8);
   (hasOverflow(num, sizeof (unsigned int) * 8)) ?
      cout << "T\n" : cout << "F\n";

   cout << left << setw(19) << "long" << right << setw(3)
        << sizeof (long) << setw(24) << dec << (long)num
        << setw(22) << hex << (long)num << setw(8);
   (hasOverflow(num, sizeof (long) * 8 -1)) ? cout << "T\n" : cout << "F\n";
 
   cout << left << setw(19) << "unsigned long" << right << setw(3)
        << sizeof (unsigned long) << setw(24) << dec << (unsigned long)num
        << setw(22) << hex << (unsigned long)num << setw(8);
   (hasOverflow(num, sizeof (unsigned long) * 8)) ?
      cout << "T\n" : cout << "F\n";

   cout << left << setw(19) << "long long" << right << setw(3)
        << sizeof (long long) << setw(24) << dec << (long long)num
        << setw(22) << hex << (long long)num << setw(8);
   (hasOverflow(num, sizeof (long long) * 8 -1)) ?
      cout << "T\n" : cout << "F\n";

   cout << left << setw(19) << "unsigned long long" << right << setw(3)
        << sizeof (unsigned long long) << setw(24) << dec
        << (unsigned long long)num
        << setw(22) << hex << (unsigned long long)num << setw(8);
   (hasOverflow(num, sizeof (unsigned long long) * 8)) ?
      cout << "T\n" : cout << "F\n";

   cout << dec << left << setw(19) << "float" << right << setw(3)
        << sizeof (float) << setw(24) << fixed << setprecision(0) << (float)num
        << setw(22) << scientific << setprecision(5) << (float)num << setw(8);
   (num != (unsigned long long)(double)num) ? cout << "T\n" : cout << "F\n";

   cout << dec << left << setw(19) << "double" << right << setw(3)
        << sizeof (double) << setw(24) << fixed << setprecision(0)
        << (double)num << setw(22) << scientific << setprecision(5)
        << (double)num << setw(8);
   (num != (unsigned long long)(double)num) ? cout << "T\n" : cout << "F\n";

   cout << dec << left << setw(19) << "long double" << right << setw(3)
        << sizeof (long double) << setw(24) << fixed << setprecision(0)
        << (long double)num << setw(22) << scientific << setprecision(5)
        << (long double)num << setw(8);
   (num != (unsigned long long)(long double) num) ? cout << "T\n" : cout << "F\n";
}

/*********************************************************************
 * takes in original number and the number of bits a data type can hold
 * then it sees if original number is larger than the capacity of new
 *********************************************************************/
bool hasOverflow(unsigned long long num, int bits)
{
   //cerr << endl << dec << num << " " << bits << endl;
   return num > pow(2, bits) - 1;
}
