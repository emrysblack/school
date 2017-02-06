/***********************************************************************
* Program:
*    Assignment 14, STL 
*    Brother Boyer, CS165
* Author:
*    Brady Field
* Summary: 
*    A simple program to display a text file backwards from end to start
*
*    Estimated:  0.5 hrs   
*    Actual:     0.8 hrs
*      Syntax for vectors
************************************************************************/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

/**********************************************************************
 * opens the file and read in the contents line by line
 **********************************************************************/
bool readFile(vector<string> &text)
{
   char fileName[256];
   string line;
   cout << "Enter the name of the file: ";
   cin >> fileName;

   //open file
   ifstream fin(fileName);
   if (fin.fail())
      return false;
   while (!(fin.eof()))
   {      
      getline(fin,line);
      text.push_back(line);
   }
   fin.close();

   return true;
}

/***********************************************************************
 * displays the text backward
 ***********************************************************************/
void display(vector<string> text)
{
   //index minus 2 to not leave bounds and skip blank line at end of file
   for (int i = text.size() - 2; i >= 0; i--)
      cout << text[i] << endl;
}

/***********************************************************************
 * holds vector and calls functions to read the file and display the
 * contents
 ***********************************************************************/
int main()
{
   vector<string> text;
   readFile(text);
   display(text);
   return 0;
}
