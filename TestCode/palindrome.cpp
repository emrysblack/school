// test for palindrome
#include <iostream>
#include <string>
using namespace std;

bool isPalindrome(string word)
{
   for (int i = 0; i < word.length()/2; i++)
   {
      if (tolower(word[i]) != tolower(word[word.length() - 1 - i]))
         return false;
   }

   return true;
}

int main(int argc, char **argv)
{
   string word;

   if (argc > 1)
   {
      for (int i = 1; i < argc; i++)
         word += argv[i];
   }
   else
   {
      cout << "Enter a word: ";
      cin >> word;
   }

   cout << word
        << (isPalindrome(word) ? " is" : " is not")
        << " a palidrome.\n";
   return 0;
}
