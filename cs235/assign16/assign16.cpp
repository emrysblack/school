/***********************************************************************
* Program:
*    Homework 16, BoM Word Count
*    Brother Twitchell, CS 235
* Author:
*    Brady Field
* Summary: 
*    reads in text from Book of Mormon and displays 100 most frequent
***********************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <iomanip>
using namespace std;

/**********************************************************************
 * takes input file from command line, processes words and outputs
 **********************************************************************/
int main (int argc, char** argv)
{
   if (argc < 2)
      cout << "ERROR: must specify file name\n";
   else
   {
      ifstream fin(argv[1]);
      if (fin.fail())
         cout << "ERROR: could not open file " << argv[1] << endl;
      else
      {
         int wordCount = 0; // stores total words
         int num = 0; // occurrences of current word
         string input;
         map < string, int > myMap1;
         map < string, int > ::iterator it1;
         multimap < int, string, greater<int> > myMap2;
         multimap < int, string > ::iterator it2;
         while (!fin.eof())
         {
            fin >> input;
            if (fin.good())
            {
               // process words
               for (int i = 0; i < input.size(); i++) // remove punctuation
                  if (!isalpha(input[i]) && input[i] != '-')
                     input.erase(i--,1); // go back a character to not skip
               for (int i = 0; i < input.size(); i++)
                  input[i] = tolower(input[i]); // convert to lower case
               // store words
               it1 = myMap1.find(input);
               if (it1 == myMap1.end()) // is first entry
                  num = 1;
               else
                  num = myMap1[input] + 1; // get number already there
               myMap1[input] = num;
               wordCount++;
            }
         }
         fin.close();
         
         // order elements in order of occurrence
         num = 0;
         for (it1 = myMap1.begin(); it1 != myMap1.end(); it1++)
            myMap2.insert( pair < int, string > (it1->second, it1->first));
         
         // display result
         cout << "\nNumber of words processed: " << wordCount << endl;
         cout << "100 most common words found and their frequencies:\n";
         int i;
         for (it2 = myMap2.begin(), i = 0; i < 100; it2++, i++)
         {
            cout << setw(23);
            cout << it2->second << " - ";
            cout << it2->first << endl;
         }
      }
   }
   return 0;
}
