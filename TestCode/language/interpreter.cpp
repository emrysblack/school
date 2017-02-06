#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <stack>
#include <map>
#include <cmath>
#include "lexer.h"
#include "parser.h"
#include "var.h"
#include "evaluator.h"
using namespace std;

/*
* get initial scope ready
*/
void readySystem()
{
  // loads vars
  createScope();
}


int main(int argc, char ** argv)
{
   ifstream fin;
   bool file = false;
   long long lineCount = 0;
   if (argc > 1)
   {
      fin.open(argv[1]);
      if (fin.fail())
      {
        cout << "Error, could not open the specified file\n";
        return 0;
      }
      file = true;
   }
   else
   {
     cout << "Welcome to the Lindy Interpretter\n";
     cout << "Type 'exit' when finished\n";
   }
   string input;
   vector<string> history;
   readySystem();

   do
   {
      if (!file)
      {
         cout << "\n>> ";
         getline(cin, input);
         history.push_back(input);
      }
      else
      {
        getline(fin, input);
        if (fin.eof())
        {
          input = "exit";
        }
      }
      try
      {
        lineCount++;
        Evaluator::execute(Parser::parse(Lexer::tokenize(input)));
      }
      catch (string exception)
      {

        if (file)
        {
          cout << "\nLine " << lineCount << ": ";
          input = "exit"; // stop executing bad file
        }
        cout << "Error! "<< exception << endl << endl;
      }
   } while (input != "exit");
   if (file)
   {
     fin.close();
   }
   return 0;
}
