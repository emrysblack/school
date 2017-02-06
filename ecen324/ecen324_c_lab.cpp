/***********************************************************************
* Program:
*    Lab C_lab, ECEN 324 Learning C Lab
*    Brother Jones, ECEN 324
* Author:
*    Your Name
* Summary:
*    Descriptive text ...
************************************************************************/

#include <iostream>
#include <iomanip>
using namespace std;

#define PI 3.1415926

/***********************************************************************
* descriptive text goes here
***********************************************************************/
int main (void)
{
   // Printing various items
 
   const char LETTER = 'A';
   cout << 24 << '\n';
   cout << PI << endl;
   cout << LETTER << endl;
 
   float payRate = 10.50;
   int hours = 40;
 
   cout << "Users pay rate: $" << payRate << endl; 
   cout << " Hours worked: " << hours << endl;
   cout << "    Gross Pay: $" << hours * payRate << endl;
 
   int number;
   cerr << "Enter number: ";
   cin >> number;
   cout << "Twice " << number << " is " << number * 2 << endl;
 
   /*********************************************************************/
   /*********************** Output an Integer ***************************/
   /*********************************************************************/
   int anInt = 99;
   float aFloat = 43.2;
 
   // Output the integer with the default formatting.
   //
   cout << endl;                      // output a blank line
   cout << "Integer: " << anInt << " ###\n";
 
   // Output the integer in a fixed field width of 10.
   // The setw() manipulator takes effect only for the next output object.
   // The object will be right justified in the field.
   //
   cout << "Integer: " << setw(10) << anInt << " ###\n";
 
   // Output the integer in a fixed field width of 10
   // and left justified in the field.
   //
   cout << setiosflags(ios::left);
   cout << "Integer: " << setw(10) << anInt << " ###\n\n";
 
   
   /*********************************************************************/
   /************************* Output a Float ****************************/
   /*********************************************************************/
 
   // Output the float with the default formatting.
   //
   cout << "  Float: " << aFloat << " ###\n";
 
   // Output the float in a fixed field width of 10.
   // The setw() manipulator takes effect only for the next output object.
   // The float object is left justified in the field because the setiosflags()
   // done previously is still in effect.
   //
   cout << "  Float: " << setw(10) << aFloat << " ###\n";
 
   // Output the float right justified in a field width of 10 with  
   // a precision of 2 places after the decimal point for the float. 
   //
   cout << "  Float: " 
        << setw(10) << setprecision(2)
        << resetiosflags( ios::left )
        << setiosflags( ios::fixed | ios::showpoint )
        << aFloat << " ###" << endl;
 
   // Output the float with 3 places of precision after the decimal point but
   // not giving a field width.
   //
   cout << "  Float: " << setprecision(3) << aFloat << " ###\n";
 
   // Output the float with 3 places of precision after the decimal point with
   // a field width of 10.  The other flags set above are still in effect.
   //
   cout << "  Float: " << setprecision(3) << setw(10) 
        << aFloat << " ###\n";
  
   // Output the float with 4 places of precision after the decimal point with 
   // a field width of 10 and left justify the number.
   //
   cout << setprecision(4) << setiosflags( ios::left );
   cout << "  Float: " << setw(10) << aFloat << " ###\n\n";
 
   /*********************************************************************
    *************** Create some code to output a table ******************
    *********************************************************************
 
    * The following table has a leading tab.
 
        Oct   Dec   Hex   Char
        ----------------------
        141   97    61    a
        142   98    62    b
        143   99    63    c
        144   100   64    d
        145   101   65    e
        146   102   66    f
        147   103   67    g
        150   104   68    h
        151   105   69    i
        152   106   6a    j
        153   107   6b    k
        154   108   6c    l
        155   109   6d    m
        156   110   6e    n
        157   111   6f    o
        160   112   70    p
        161   113   71    q
        162   114   72    r
        163   115   73    s
        164   116   74    t
        165   117   75    u
        166   118   76    v
        167   119   77    w
        170   120   78    x
        171   121   79    y
        172   122   7a    z
 
    *********************************************************************/
 
   /*********************************************************************
    *************** Now play with pointers to finish up *****************
    *********************************************************************/
 
   int *p1;
   int *p2;
 
   p1 = new int;
   *p1 = 42;
   p2 = p1;
   cout << "*p1 == " << *p1 << endl;
   cout << "*p2 == " << *p2 << endl;
 
   *p2 = 53;
   cout << "*p1 == " << *p1 << endl;
   cout << "*p2 == " << *p2 << endl;
 
   p1 = new int;
   *p1 = 88;
   cout << "*p1 == " << *p1 << endl;
   cout << "*p2 == " << *p2 << endl;
 
   cout << "Hope you got the point of this example!\n";
 
   delete p1;
   delete p2;

   return 0;
}

