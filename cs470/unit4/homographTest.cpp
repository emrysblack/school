/***********************************************************************
 * Program:
 *    Homograph Test
 * Author:
 *    Br. SmithB
 * Homograph
 *    This program will search for text including homographs
 ***********************************************************************/

#include <iostream>     // for CIN and COUT
#include <fstream>      // for file I/O
#include <sstream>      // to make building strings easier
#include "homograph.h"    // for the String class we are testing
using namespace std;

const char * ALPHA = "/home/cs470/unit4/UC_SimList0.9.txt";

void defineLetters(vector <Homograph> & letters);
string convertWord(vector <Homograph> & letters, String word);
int countWords(string newSearch, vector <Homograph> & letters, string filename, int & count);

/*****************************************************
 * MAIN
 * This is just a trivial driver program
 ****************************************************/
int main()
{
   String search;
   string filename;
   vector <Homograph> letters;
   int count = 0;
   
   // set up homograph dictionary
   defineLetters(letters);
   
   // prompt for search terms
   cout << "Search term: ";
   cin >> search;
   cout << "Filename of the search text: ";
   cin >> filename;
   
   // convert search term
   string newSearch = convertWord(letters, search);
   
   // read file and convert word
   countWords(newSearch, letters, filename, count);

   // display results
   cout << "The term '" << search << "' is found " << count << " time(s) in " << filename << endl;
   return 0;
}

void defineLetters(vector <Homograph> & letters)
{
   ifstream fin(ALPHA);
   string temp, family, entry;

   while (getline(fin, temp))
   {
      istringstream ss(temp);
      ss >> family;
      Homograph letter;
      letter.setFamily(family);
      while (ss >> entry)
      {
         // get code
         int i;
         for (i = 0; entry[i] != ':'; i++)
            ;
         i++;
         int j;
         for(j = i; entry[j] != ':'; j++)
         {
            entry[j] = tolower(entry[j]);
         }

         letter.insert(entry.substr(i, j - i));
      }
      letters.push_back(letter);
   }
   fin.close();
}

string convertWord(vector <Homograph> & letters, String w)
{
   // cycle through word and convert to hex each character
   string word = w.getString();
   string newWord;

   for (int i = 0; i < word.size(); i++)
   {
      string letter;
      if (isalpha(word[i]))
      {
         letter += word[i];
      }
      else
      {

         while (word[i] != ';')
         {
            letter += word[i];
            i++;
         }
         letter += word[i];
      }       
     string code = codeFromString(letter);

      // change to family code
       for (int j = 0; j < letters.size(); j++)
      {
         if (letters[j].isHomograph(code))
         {
            code = letters[j].getFamily();
            break;
         }
      }

      // build character in string
      newWord += characterFromNumbers(code.c_str());
   }

   return newWord;
}

int countWords(string newSearch, vector <Homograph> & letters, string filename, int & count)
{
   String word;
   vector <String> words;
   ifstream fin(filename.c_str());
   if (fin.fail())
   {
      cout << "ERROR: could not open file " << filename << endl;
      return 0;
   }
   while (fin >> word)
   {
      words.push_back(word);
   }
   fin.close();
   
   for (int i = 0; i < words.size(); i++)
   {
     string newWord = convertWord(letters, words[i]);
      
      // compare words
      if (newSearch == newWord)
      {
         count++;
      }
   }
}
