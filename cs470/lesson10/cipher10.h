/********************************************************************
* Header:
*    Implement your cipher here. You can view 'example.h' to see the
*    completed Case Cipher example.
********************************************************************/
#ifndef CIPHER10_H
#define CIPHER10_H
#include <sstream>
#include <ctype.h>
/********************************************************************
 * CLASS
 *******************************************************************/
class Cipher10 : public Cipher
{
public:
   virtual std::string getPseudoAuth()  { return "Brady Field"; }
   virtual std::string getCipherName()  { return "Beaufort Cipher"; }
   virtual std::string getEncryptAuth() { return "Salvador Ernesto Afane"; }
   virtual std::string getDecryptAuth() { return "Ryan Muse"; }

   /***********************************************************
    * GET CIPHER CITATION
    * Returns the citation from which we learned about the cipher
    ***********************************************************/
   virtual std::string getCipherCitation()
   {
      return std::string("http://practicalcryptography.com/ciphers/beaufort-cipher/");
   }

   /**********************************************************
    * GET PSEUDOCODE
    * Returns the pseudocode as a string to be used by the caller.
    **********************************************************/
   virtual std::string getPseudocode()
   {
      std::string str;

      // TODO: please format your pseudocode
      // The encrypt pseudocode
      str =  "---encryption---\n";
      str += "FOR source length\n";
      str += "   IF password[current letter mod length of password is a character]\n";
      str += "      source[current letter] make upper case\n";
      str += "      password[current letter mod length of password is a character] make upper case\n";
      str += "      source[current letter] = (password[current letter mod length of password] + 26 - source[current letter]) % 26 + 'A'\n\n";

      // The decrypt pseudocode
      str += "---decryption---\n";
      str += "FOR source length\n";
      str += "   IF password[current letter mod length of password is a character]\n";
      str += "      source[current letter] make upper case\n";
      str += "      password[current letter mod length of password is a character] make upper case\n";
      str += "      source[current letter] = (password[current letter mod length of password] + 26 - source[current letter]) % 26 + 'A'\n\n";

      return str;
   }

   /**********************************************************
    * ENCRYPT
    * TODO: ADD description
    **********************************************************/
   virtual std::string encrypt(const std::string & source,
                               const std::string & password)
   {
      std::string destination = source;
      for (int i = 0; i < source.length(); i++)
      {
         if (isalpha(destination[i]) && isalpha(password[i % password.length()]))
      	 {
            destination[i] = toupper(source[i]);
            
            destination[i] = (((toupper(password[i % password.length()]) + 26 - destination[i])) % 26 + 'A');
      	 }
          if (islower(source[i]))
          {
             destination[i] = tolower(destination[i]);
          }
      }
      return destination;
   }

   /**********************************************************
    * DECRYPT
    * TODO: Decrypts using a method based on the Beaufort Cipher
    **********************************************************/
   virtual std::string decrypt(const std::string & source,
                               const std::string & password)
   {
      std::string destination = source;
      for (int i = 0; i < source.length(); i++)
      {
         if (isalpha(source[i]) && isalpha(password[i % password.length()]))
         {
            char sourceChar = (toupper(source[i]) - 65);
            char passwordChar = (toupper(password[i % password.length()]) - 65);
            destination[i] = ((passwordChar - sourceChar + 26) % 26) + 65;
            if (islower(source[i]))
            {
               destination[i] = tolower(destination[i]);
            }
         }
      }

     return destination;
   }
};

#endif // CIPHER10_H
