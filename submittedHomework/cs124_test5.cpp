/***********************************************************************
* Program:
*    Test 5, Find a word in a file
*    Brother Helfrich, CS124
* Author:
*    Brady Field
* Summary: 
*    Searches a file for a given word
*
*    Estimated:  1.0 hrs   
*    Actual:     1.0 hrs
*      can't fix a segmentation fault
************************************************************************/

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

bool searchFile(string word, char *fileName);
string getWord();
bool getFileName(char *fileName);

/**********************************************************************
* tests command line to see if all needed paramiters are present.
* If not will prompt for needed input, and then searches the file
***********************************************************************/
int main(int argc, char **argv)
{
   string word;
   char *fileName;
   // test if command line paramiters are all present
   if (argc < 3)
   {
      if (argc < 2)
         word = getWord();
      else
         word = argv[1];

      getFileName(fileName);
   }
   else
   {
      word = argv[1];
      fileName = argv[2];
   }
   // searches file
   searchFile(word, fileName);
   
   return 0;
}

/***********************************************************************
 * opens target file and searches for word
 *
 **********************************************************************/
bool searchFile(string word, char *fileName)
{
   bool found = false;
   string temp;

   // opens the file
   ifstream fin(fileName);
   if (fin.fail())
   {
      cout << "Error: could not open target file\n";
      return false;
   }

   // search the file for key word
   while (!(found) && !(fin.eof))
   {
      fin >> temp;
      if (word == temp)
         found = true;
   }

   if (found)
   {
      cout << "The Word \"" << word <<"\" is in " << fileName << endl;
      return true;
   }
   fin.close();
   return false;
}
/***********************************************************************
 * prompts for word
 **********************************************************************/
string getWord()
{
   string word;
   // prompt for the word
   cout << "Please enter the word to search for: ";
   cin >> word;
   return word;
}

/***********************************************************************
 * prompts for file name
 **********************************************************************/
bool getFileName(char *fileName)
{

   // prompt for file name
   cout << "Please enter the filename: ";
   cin >> fileName;
   return true;
}
