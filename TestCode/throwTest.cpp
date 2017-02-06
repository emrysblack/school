// test for throwing and catching exceptions
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(int argc, char **argv)
{
   string file;
   if (argc < 2)
   {
    cout << "Enter a filename: ";
    cin >> file;
   }
   else
      file = argv[1];
   try
   {
      ifstream fin(file.c_str());
      if (fin.fail())
      {
         
         // either throw string or typecast
         string errorM = "Error with file\n";
         
         // must typecast or type is const char *
         throw (string)"Error with file\n";
      }
      cout << "opened\n";
      fin.close();
   }
   catch (string message)
   {
      cout << message;
   }
   cout << "End\n";
   return 0;
}
