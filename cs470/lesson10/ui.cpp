/********************************************************************
* Program:
*    Lecture 3 post-class exercise: Create a cipher
*    Brother Helfrich, CS470
* Author:
*    Jeffery W Schiers
* Summary:
*    This program will be able to encrypt and decrypt text using a
*    variety of ciphers.
*********************************************************************/
#include <iostream>
#include <iomanip>
#include <vector>

#include "cipher.h"   // Base Cipher Class
#include "example.h"  // Bro Helfrich example Cipher
#include "cipher01.h"  // Include the other 35 header files
#include "cipher02.h"
#include "cipher03.h"
#include "cipher04.h"
#include "cipher05.h"
#include "cipher06.h"
#include "cipher07.h"
#include "cipher08.h"
#include "cipher09.h"
#include "cipher10.h"
#include "cipher11.h"
#include "cipher12.h"
#include "cipher13.h"
#include "cipher14.h"
#include "cipher15.h"
#include "cipher16.h"
#include "cipher17.h"
#include "cipher18.h"
#include "cipher19.h"
#include "cipher20.h"
#include "cipher21.h"
#include "cipher22.h"
#include "cipher23.h"
#include "cipher24.h"
#include "cipher25.h"
#include "cipher26.h"
#include "cipher27.h"
#include "cipher28.h"
#include "cipher29.h"
#include "cipher30.h"
#include "cipher31.h"
#include "cipher32.h"
#include "cipher33.h"
#include "cipher34.h"
#include "cipher35.h"

using namespace std;

/********************************************************************
 * UI CLASS
 ********************************************************************/
class UI
{
private:
   vector<Cipher*> cipher;
   string plaintext;
   string password;

public:
   /************************************************************
    * DEFAULT CONSTRUCTOR
    * sets string to null and loads the cipher vector
    ************************************************************/
   UI()
   {
      plaintext = "";
      password = "";

      // load the ciphers into the cipher vector
      cipher.push_back(new Example); // add the example Cipher
      cipher.push_back(new Cipher1); // add other 35 Ciphers
      cipher.push_back(new Cipher2);
      cipher.push_back(new Cipher3);
      cipher.push_back(new Cipher4);
      cipher.push_back(new Cipher5);
      cipher.push_back(new Cipher6);
      cipher.push_back(new Cipher7);
      cipher.push_back(new Cipher8);
      cipher.push_back(new Cipher9);
      cipher.push_back(new Cipher10);
      cipher.push_back(new Cipher11);
      cipher.push_back(new Cipher12);
      cipher.push_back(new Cipher13);
      cipher.push_back(new Cipher14);
      cipher.push_back(new Cipher15);
      cipher.push_back(new Cipher16);
      cipher.push_back(new Cipher17);
      cipher.push_back(new Cipher18);
      cipher.push_back(new Cipher19);
      cipher.push_back(new Cipher20);
      cipher.push_back(new Cipher21);
      cipher.push_back(new Cipher22);
      cipher.push_back(new Cipher23);
      cipher.push_back(new Cipher24);
      cipher.push_back(new Cipher25);
      cipher.push_back(new Cipher26);
      cipher.push_back(new Cipher27);
      cipher.push_back(new Cipher28);
      cipher.push_back(new Cipher29);
      cipher.push_back(new Cipher30);
      cipher.push_back(new Cipher31);
      cipher.push_back(new Cipher32);
      cipher.push_back(new Cipher33);
      cipher.push_back(new Cipher34);
      cipher.push_back(new Cipher35);
   }

   /************************************************************
    * MENU
    * displays the available ciphers and returns the option
    ************************************************************/
   int menu()
   {
      int nOptions = cipher.size();

      // display the options
      cout << "What cipher do you want to test?\n";
      for (int i = 0; i != nOptions; i++)
      {
         string nCipher = cipher[i]->getCipherName();
         if (nCipher.compare("cipher name") != 0)
            cout << setw(4) << i << " .... " 
                 << cipher[i]->getCipherName() << endl;
      }

      // get the users option and return it
      return getOption();
   }

   /************************************************************
    * GET OPTION
    * prompts for the option and returns the correct index
    ************************************************************/
   int getOption()
   {
      int nOptions = cipher.size();
      int option = -1;

      while (option < 0 || option > nOptions)
      {
         cout << "> ";
         cin >> option;
         
         // check for a value that is not an int
         if (cin.fail())
         {
            cout << "ERROR - non-digit entered\n";
            cin.clear();
            cin.ignore(256, '\n');
         }
         else if (option < 0 || option > nOptions)
            cout << "ERROR - value is outside the accepted range\n";
         else
            cin.ignore(); // clear the buffer of any leftovers...
      }

      return option; 
   }

   /************************************************************
    * GET TEXT
    * get the plaintext and password from the user
    ************************************************************/
   void getText()
   {
      // get the text
      cout << "Please enter the text: ";
      getline(cin, plaintext);
      if (plaintext.compare("") == 0)
         plaintext = "I am just \"plain\" text.";

      // get the password
      cout << "Please enter the password: ";
      getline(cin, password);
      if (password.compare("") == 0)
      {
         password = "Passw0rd!";
         cout << "Default password: " << password << endl;
      }
   }

   /************************************************************
    * GET REPORT
    * generates the report for the selected cipher
    ************************************************************/
   void getReport(const int & index)
   {
      string encrypted = cipher[index]->encrypt(plaintext, password);
      string decrypted = cipher[index]->decrypt(encrypted, password);
      cout << "==================================="
           << "===================================\n";
      cout << "Cipher Name:         " 
           << cipher[index]->getCipherName() << endl;
      cout << "Pseudocode Author:   " 
           << cipher[index]->getPseudoAuth() << endl;
      cout << "Code Encrypt Author: " 
           << cipher[index]->getEncryptAuth() << endl;
      cout << "Code Decrypt Author: " 
           << cipher[index]->getDecryptAuth() << endl;
      cout << "==================================="
           << "===================================\n";
      cout << "Citation:\n"
           << cipher[index]->getCipherCitation() << endl;
      cout << "==================================="
           << "===================================\n";
      cout << "Plain text:    " << plaintext << endl;
      cout << "Cipher text:   " << encrypted << endl;
      cout << "Decipher text: " << decrypted << endl;
      cout << "==================================="
           << "===================================\n";
      cout << "Pseudocode:\n"
           << cipher[index]->getPseudocode() << endl;
   }
};

/********************************************************************
 * MAIN
 * drives the UI class
 ********************************************************************/
int main()
{
   UI interface;
   int index;

   index = interface.menu(); // show the menu and get cipher index

   if (index == -1) // if index == -1 then quit
      return 0;

   interface.getText(); // get the plaintext and password
   interface.getReport(index); // generate the report

   return 0;
}
