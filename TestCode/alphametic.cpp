// alphametic test
#include <iostream>
#include <string>
using namespace std;

bool possible(int letters[], string word1, string word2, string key)
{
	// check for uniqueness
   for (int i = 0; i < 26; i++)
   {
      for (int j = 0; j < 26; j++)
      {
         if (i != j)
         {
            if (letters[i] == letters[j] && letters[i] != -1)
            {
               return false;
            }
         }
      }
   }
      // check for non-zero
   if (letters[tolower(word1[0]) - 'a'] == 0 || letters[tolower(word2[0]) - 'a'] == 0 || letters[tolower(key[0]) - 'a'] == 0)
   {
	   return false;
   }
   return true;
}
bool addAndVerify(int letters[], string word1, string word2, string key)
{
   int w1[256];
   int w2[256];
   int k[256];
   int answer[256];
   
   // prepare variables for math, store backwards to make easier
   for (int i = 0; i < 256; i++)
   {
	   answer[i] = 0;
	   w1[i] = 0;
	   w2[i] = 0;
   }
   for (int i = 0; i < word1.length(); i++)
   {
	   w1[word1.length() - i - 1] = letters[tolower(word1[i]) - 'a'];
   }
   for (int i = 0; i < word2.length(); i++)
   {
	   w2[word2.length() - i - 1] = letters[tolower(word2[i]) - 'a'];
   }
   for (int i = 0; i < key.length(); i++)
   {
	   k[key.length() - i - 1] = letters[tolower(key[i]) - 'a'];
   }
   int maxLength = (word1.length() > word2.length() ? word1.length(): word2.length());
   for (int i = 0; i < maxLength; i++)
   {
	   answer[i + 1] = (answer[i] + w1[i] + w2[i]) / 10; // carry 
	   answer[i] = (answer[i] + w1[i] + w2[i]) % 10; // digit
   }
   
   // compare to key
   for (int i = 0; i < key.length(); i++)
   {
	   if (answer[i] != k[i])
	   {
		   return false;
	   }
   }
   if (answer[key.length()]) // check for extra carry
   {
	   return false;
   }
   
   return true;
}

int main(int argc, char ** argv)
{
   string word1 = argv[1];
   string word2 = argv[2];
   string key = argv[3];
   cout << word1 << " + " << word2 << " = " << key << endl << endl;
	
   int letters[26];
   // prefill with emptys
   for (int i = 0; i < 26; i++)
   {
      letters[i] = -1;
   }
   // fill with letters
   for (int i = 0; i < word1.length(); i++)
   {
      letters[tolower(word1[i]) - 'a'] = 0;
   }
   for (int i = 0; i < word2.length(); i++)
   {
      letters[tolower(word2[i]) - 'a'] = 0;
   }
   for (int i = 0; i < key.length(); i++)
   {
      letters[tolower(key[i]) - 'a'] = 0;
   }

   // the brute-force way
   int solutions = 0;
   int i = 0;
   while(i >= 0)
   {
      // simulate nested loops for all non-negative values
      i = 25;
      do 
      {
         letters[i] = letters[i] % 10;
         for (i = i - 1; letters[i] == -1; i--)
         {
         }
         letters[i]++;
      } while(letters[i] >= 10 && i >= 0);

      // check current values
      if (possible(letters, word1, word2, key))
      { 
         if (addAndVerify(letters, word1, word2, key))
         {
            solutions++;
            cout << "Solution " << solutions << endl;
            for (int j = 0; j < 26; j++)
            {
               if (letters[j] != -1)
               {
                  cout << char('a' + j) << ": " << letters[j] << " ";
               }
            }
            cout << endl << endl;
         }
      }
   }
   cout << "found " << solutions
        << (solutions == 1 ? " solution\n" : " solutions\n");
   return 0;
}
