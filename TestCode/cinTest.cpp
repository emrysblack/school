// test to show reading capabilities with multiple variables to read in
// special data ready to use
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Coord
{
   char a;
   float b;
};
   
int main(int argc, char** argv)
{
   char fileName[256] = "cinTest.txt";
   char *file = fileName;
   Coord y;
   
   // can pass in file name on the command line
   if (argc == 2)
   {
      file = argv[1];
   }
   else
   {
      cout << "Enter a file: ";
      cin >> fileName;
   }

   // open the file
   ifstream fin(file);

   if (fin.fail())
   {
      cout << "ERROR: could not open file: " << file << endl;
      return 0;
   }
   // string to show possible string stream
   string s = "X569.21Y32Z567.123456";
   while(fin >> y.a >> y.b)
   {
      if (fin.fail())
      {
         cout << "ERROR in file: " << file << endl;
         break;
      }
      cout << "Axis: " << y.a << endl;
      cout << "Value: " << y.b << endl;
   }
   fin.close();
  
   return 0;
}
