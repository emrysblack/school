/********************************************************************
 * Header:
 *    Implement your cipher here. You can view 'example.h' to see the
 *    completed Case Cipher example.
 ********************************************************************/
#ifndef CIPHER6_H
#define CIPHER6_H

#include <stdlib.h>
#include <cstring>

/********************************************************************
 * CLASS
 *******************************************************************/
class Cipher6 : public Cipher
{
  public:
   virtual std::string getPseudoAuth()  { return "Hanlet Escano"; }
   virtual std::string getCipherName()  { return "Caesar Method"; }
   virtual std::string getEncryptAuth() { return "Bruce Niendorf"; }
   virtual std::string getDecryptAuth() { return "Gizmo Bentim"; }

   /***********************************************************
    * GET CIPHER CITATION
    * Returns the citation from which we learned about the cipher
    ***********************************************************/
   virtual std::string getCipherCitation()
   {
      return std::string("http://samples.sainsburysebooks.co.uk/9780470516195_sample_388942.pdf, page 18 (section 2.1)");
   }
   
   /**********************************************************
    * GET PSEUDOCODE
    * Returns the pseudocode as a string to be used by the caller.
    **********************************************************/
   virtual std::string getPseudocode()
   {
      std::string str;

      
      
      str = "begin encrypt(string, key)\n";
      str += "   encrypted_string => \"\"\n\n";
      
      str += "   if key is not numeric";
      str += "       key => key.length % 26";
      
      str += "   foreach character char in your string\n";
      str += "      if char is space\n";
      str += "         append space to encrypted_string\n";
      str += "      else\n";
      str += "         charCase => (char >= 'A' && char <= 'Z' ? 'A' : 'a')\n";
      str += "         new_char => (char)(((char + key - charCase + 26) % 26) + charCase)\n";
      str += "         append new_char to encrypted_string\n";
      str += "      end if\n";
      str += "   end foreach\n\n";

      str += "   return encrypted_string\n";
      str += "end encrypt\n\n\n";
      
      str += "--------------------------------------------------\n";
      
      str += "begin decrypt(string, key)\n";
      str += "   decrypted_string => \"\"\n\n";

      str += "   if key is not numeric";
      str += "       key => key.length % 26";
      
      str += "   foreach character char in your string\n";
      str += "      if char is space\n";
      str += "         append space to decrypted_string\n";
      str += "      else\n";
      str += "         charCase => (char >= 'A' && char <= 'Z' ? 'A' : 'a')\n";
      str += "         new_char => (char)(((char - key - charCase + 26) % 26) + charCase)\n";
      str += "         append new_char to encrypted_string\n";
      str += "      end if\n";
      str += "   end foreach\n\n";

      str += "   return decrypted_string\n";
      str += "end encrypt\n";

      return str;
   }

   /**********************************************************
    * ENCRYPT
    *   This function will take the ascii values of the input
    *   and shift them according to the key value
    **********************************************************/
   virtual std::string encrypt(const std::string & source, 
                               const std::string & password)
   {
      std::string destination = source;
         
      std::string encryptedString;
      char newChar;
      char charCase;
      char currentChar;
      char space = ' ';
      int key; 

      // Convert the password to an int, if necessary
      if (!isdigit(password[0]))
      {
         key = password.length();
      }
      else
      {
         key = atoi(password.c_str());
      }

      // Loop through the string and shift
      for (int i = 0; i < destination.length(); i++)
      {
         currentChar = destination[i];
         if (currentChar == space)
         {
            encryptedString += ' '; // add a space, which doesn't get encrypted
         }
         else
         {
            // Ternary operation to determine if character is uppercase or not
            charCase = ((currentChar >= 'A' && currentChar <= 'Z') ? 'A' : 'a');
            newChar = (char)(((currentChar - key - charCase + 26) % 26) + charCase);
            encryptedString += newChar;
         }
      }
    
      destination = encryptedString;
      return destination;
   }

   /**********************************************************
    * DECRYPT
    * TODO: ADD description
    **********************************************************/
   virtual std::string decrypt(const std::string & source, 
                               const std::string & password)
   {
      std::string destination = source;

      std::string decryptedString;

      char newChar;
      char charCase;
      char currentChar;
      char space = ' ';
      int key;

      if (!isdigit(password[0]))
         key = password.length();
      else
         key = atoi(password.c_str());

      // Loop through the string and shift
      for (int i = 0; i < destination.length(); i++)
      {
         currentChar = destination[i];
         if (currentChar == space)
            decryptedString += ' ';
         else
         {
            // Ternary operation to determine if character is uppercase or not
            charCase = ((currentChar >= 'A' && currentChar <= 'Z') ? 'A' : 'a');
            newChar = (char)(((currentChar + key - charCase + 26) % 26) + charCase);
            decryptedString += newChar;
         }
      }

      destination = decryptedString;
         
      return destination;
   }
};

#endif // CIPHER6_H
