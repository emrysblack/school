/***********************************************************************
* Program:
*    Project 4, Mad Lib
*    Brother Helfrich, CS124
* Author:
*    Brady Field
* Summary: 
*    Opens a file, prompts for keywords, and displays file with keywords
*    and punctuation insructions as a Mad Lib game.
*    
*    Estimated:  8.0 hrs   
*    Actual:     12.0 hrs
*      dynamic multidimensional arrays and display settings
************************************************************************/

#include <iostream>
#include <fstream>
#include <cctype>
using namespace std;

int getNumVar(char *fileName);
void promptText(char *fileName, int numVar, char **text);
void display(char *fileName, char **text);

/**********************************************************************
* sets up variables and calls function to open the file, prompt
* for keywords, and display
*
* PROMPT for file
* numVar = scanFile(fileName)
* promptText(fileName, numVar, text)
* display(fileName, text)
* END
***********************************************************************/
int main()
{
   int numVar;
   char fileName[256];
   char **text;

   // prompt for file
   cout << "Please enter the filename of the Mad Lib: ";
   cin.getline(fileName, 256);
   numVar = getNumVar(fileName);
   
   // set up multidimensional array
   text = new char *[numVar];
   for (int i = 0; i < numVar; i++)
      text[i] = new char[256];
   
   // get user text and display story
   promptText(fileName, numVar, text);
   display(fileName, text);

   // free memory
   delete [] text;
   text = NULL;
   return 0;
}

/**********************************************************************
* opens file to be read and scans file for keywords
*
* WHILE not the end of file
*    IF <
*       IF letter
*          SET numVar + 1
* END
***********************************************************************/
int getNumVar(char *fileName)
{
   ifstream fin(fileName);
   if (fin.fail())
   {
      cout << "Error: could not open target file\n";
      exit(1);
   }
   char temp;   
   int numVar = 0;
   
   // scan file for number of desired inputs
   while (!(fin.eof()))
   {
      fin.get(temp);
      if (temp == '<')
      {
         fin.get(temp);
         if ((temp >= 97) && (temp <= 122))
            numVar++;
      }
   }
   fin.close();   
   return numVar;
}

/**********************************************************************
* prompts user for keywords
*
* WHILE not the end of file
*    IF <
*       IF letter
*          PROMPT text
*          GET text
* END
***********************************************************************/
void promptText(char *fileName, int numVar, char **text)
{
   int array = 0;
   char temp;
   char prompt[256];   

   // open file again
   ifstream fin(fileName);
   if (fin.fail())
   {
      cout << "File Error\n";
      exit(1);
   }

   // scan for places to input   
   while (!(fin.eof()))
   {
      fin.get(temp);
      if (temp == '<')
      {
         fin.get(temp);
         if ((temp >= 97) && (temp <= 122))
         {
            //prompt = new char[256];
            for (int i = 0; temp != '>'; i++)
            {
               if (i == 0)
                  temp = toupper(temp);
               if (temp == '_')
                  temp = ' ';
               prompt[i] = temp;
               fin.get(temp);
            }
            // prompt for keywords
            cout << "\t" << prompt << ": ";
            cin.getline(text[array], 256);
            array++;
         }
      }
   }
   fin.close();   
}
   
/**********************************************************************
* displays the story
*
* WHILE not the end of file
*    READ word
*    IF word is not punctuation or at beginning of a new line
*       PUT space before next word
*    IF keyword
*       IF letter
*          PUT text from prompt
*       ELSE
*          SWITCH
*             # newline
*             { open quote
*             } close quote
*             [ open single quote
*             ] close single quote
*    ELSE normal word
*       PUT word
* IF no new line
*    PUT new line
* END
***********************************************************************/
void display(char *fileName, char **text)
{
   char word[256];
   int i = 0;
   bool space = false;
   bool newline = true;
   
   // open file again
   ifstream fin(fileName);
   if (fin.fail())
   {
      cout << "File Error\n";
      exit(1);
   }

   // display story
   cout << endl;
   while (!(fin.eof()))
   {
      fin >> word;
      // no space if punctuation or a new line
      if (!((word[0] < 47) || (word[0] == 63) || (word[0] == 58) ||
            (word[0] == 59) || (word[1] == 93) || (word[1] == 125) ||
            (word[1] == 35) || (newline)))
         space = true;
      else
         space = false;
      if (space)
      {
         cout << " ";
         newline = false;
      }
      // keyword
      if (word[0] == '<')
      {
         // input word
         if (((word[1] >= 65) && (word[1] <= 90)) || ((word[1] >= 97) &&
                                                      (word[1] <= 122)))
         {
            if (newline)
               newline = false;
            cout << text[i];
            i++;
         }
         // grammer format instruction
         else
         {
            switch (word[1])
            {
               case '#':
                  cout << endl;
                  newline = true;
                  break;
               case '{':
                  newline = true;
               case '}':
                  cout << "\"";
                  break;
               case '[':
                  newline = true;
               case ']':
                  cout << "'";
                  break;
               default:
                  cout << "Error\n";
            }
         }
         continue;
      }
      // normal words
      cout << word;
      newline = false;
   }
   // if no new line output one
   if (word[1] != '#')
      cout << endl;
   fin.close();
}
