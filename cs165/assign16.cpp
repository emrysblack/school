/***********************************************************************
* Program:
*    Assignment 16, Exception Handling
*    Brother Boyer, CS165
* Author:
*    Brady Field
* Summary: 
*    This program is designed to illustrate the types of information that
*    we can send through the exception handling mechanism.
*
*    Estimated:  1.0 hrs   
*    Actual:     1.0 hrs
*      Syntax a bit
************************************************************************/

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

typedef bool Missing;

string readData(string fileName) throw (string, Missing, int);

/**********************************************************************
 * MAIN: This function will prompt the user for the file and display the
 *       contents on the screen.
 * IMPORTANT: you are not allowed to change any part of main
 ***********************************************************************/
int main()
{
   try
   {
      // get the filename
      string fileName;
      cout << "What is the filename? ";
      getline(cin, fileName);

      // Read the data.  Note that your function should have the
      // appropriate throw list for the 3 data types thrown.
      string data = readData(fileName);

      // display the results:
      cout << "The important fact: \""
           << data
           << "\"\n";
   }
   catch (string s)
   {
      cout << "ERROR: Invalid filename \""
           << s
           << "\"\n";
      return 1;
   }
   catch (Missing)
   {
      cout << "ERROR: No filename specified\n";
      return 1;
   }
   catch (int code)
   {
      switch (code)
      {
         case 0:
            cout << "ERROR: The file was empty\n";
            return 1;
         case 1:
            cout << "ERROR: The message exceeded 140 characters\n";
            return 1;
         case 2:
            cout << "ERROR: The message was longer than 1 line\n";
            return 1;
         default:
            cout << "ERROR: Unexpected error code " << code << endl;
            return 1;
      }
   }
   
   return 0;
}

/**************************************************************************
 * reads in the file or throws exception if various errors are encountered
 **************************************************************************/
string readData(string fileName) throw (string, Missing, int)
{
   string data;

   //test for input file name
   if (fileName == "")
      throw Missing(true);
      
   //open the file
   ifstream fin(fileName.c_str());
   if (fin.fail())
      throw fileName;
   
   getline (fin, data);
   fin.close();

   //test error conditions
   if (data == "")
      throw 0;
   if (data.length() > 140)
      throw 1;
   if (!fin.eof())
      throw 2;
   
   return data;
}
