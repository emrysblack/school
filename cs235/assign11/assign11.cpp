/***********************************************************************
* Program:
*    Homework 11, Hashing 
*    Brother Twitchell, CS235
* Author:
*    Brady Field
* Summary: 
*     Will read a file list of words into a hash table and display them
************************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <list>
using namespace std;

/**********************************************************************
 * get hash index and pushes input into table
 **********************************************************************/
void insert (list < string > table [67], const string& input)
{
   int value = 0;
   
   // get ascii value total of string and calculate hash index
   for (int i = 0; i < input.length(); i++)
      value += (int)input[i];
   value %= 67;
   table[value].push_back(input);
}

/**********************************************************************
 * displays table
 **********************************************************************/
void display (list < string > table [67])
{
   string word;
   for (int i = 0; i < 67; i++)
   {
      cout << "table[" << i << "]";
      if (i < 10) // keep spacing consistent
         cout << " ";
      cout << "-> ";
      if (table[i].empty())
         cout << "(empty)\n";
      else // display list of words
      {
         list < string > ::iterator j;
         for (j = table[i].begin(); j != table[i].end(); j++)
         {
            if (j != table[i].begin())
               cout << ", "; // only need comma after first word
            cout << *j;
         }
         cout << endl;
      }
   }
}

/**********************************************************************
 * Opens a file, reads contents into hash and displays
 ***********************************************************************/
int main(int argc, char** argv)
{
   string input;
   ifstream in;
   list < string > table [67];
   if (argc < 2) // prompt for file if not given on command line
   {
      cout << "Input file: ";
      cin >> input;
   }
   else
      input = argv[1];
   in.open(input.c_str());
   if (in.fail())
      cout << "ERROR: could not open file " << input << endl;
   else // read in values
   {
      while (in >> input) //only valid data and watch for last item
      {
         insert(table, input); 
      }
      in.close();
      display(table);
   }
   return 0;
}
