/********************************************************************
* Header:
*    Implement your cipher here. You can view 'example.h' to see the
*    completed Case Cipher example.
********************************************************************/
#ifndef CIPHER33_H
#define CIPHER33_H
#include <sstream>
/********************************************************************
 * CLASS
 *******************************************************************/
class Cipher33 : public Cipher
{
public:
   virtual std::string getPseudoAuth()  { return "Salvador Ernesto Afane"; }
   virtual std::string getCipherName()  { return "Caesar Cipher"; }
   virtual std::string getEncryptAuth() { return "Ryan Muse"; }
   virtual std::string getDecryptAuth() { return "Brady Field"; }

   /***********************************************************
    * GET CIPHER CITATION
    * Returns the citation from which we learned about the cipher
    ***********************************************************/
   virtual std::string getCipherCitation()
   {
      return std::string("http://www.rowanwatson.com/c-caesar-cipher/");
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
      str =  "PROMPT user for text \n"
      " SET message to STRING (from the user) GetLine \n"
      " FOR message LENGTH \n SET output TO CEASAR(message[x]) \n"
      " DISPLAY output \n\n"
      " THE CEASAR FUNCTION \n"
      " FUNCTION header SET CHAR caesar(CHAR a) \n"
      " IF ISALPHA(a) \n SET a TO TOUPPER(a) \n"
      " SET a TO ((a-65)+4) % 26) + 65 \n RETURN a";

      // The decrypt pseudocode
      str += "PROMPT user for encrypting message \n"
      " SET message to STRING (from the user) GetLine \n"
      " FOR message LENGTH \n SET output TO CEASAR(message[x]) \n"
      " DISPLAY output \n\n"
      " THE CEASAR FUNCTION \n "
      " FUNCTION header SET CHAR caesar(CHAR a) \n"
      " IF ISALPHA(a) \n SET a TO TOUPPER(a) \n"
      " SET a TO ((a-65)-4) % 26) + 65 \n RETURN a";
      return str;
   }

   char toCaesar(char plainLetter, int offset)
   {
      char result = plainLetter;
      if (isalpha(plainLetter))
      {
         result = ((toupper(plainLetter) + 26 + offset - 'A') % 26) + 'A';
      }

      if (islower(plainLetter))
      {
         result = tolower(result);
      }

      return result;
   }

   /**********************************************************
    * ENCRYPT
    **********************************************************/
   virtual std::string encrypt(const std::string & source,
                               const std::string & password)
   {
      std::string destination = source;
      // TODO - Add your code here

      int offset = 4;
      std::istringstream (password) >> offset; // convert text to number for key
      for (int i = 0; i < source.length(); i++)
      {
         destination[i] = toCaesar(source[i], offset);
      }
      //" IF ISALPHA(a) \n SET a TO TOUPPER(a) \n"
      //" SET a TO ((a-65)+4) % 26) + 65 \n RETURN a";
      return destination;
   }


   /**********************************************************
    * DECRYPT
    **********************************************************/
   virtual std::string decrypt(const std::string & source,
                               const std::string & password)
   {
      std::string destination = source;
      int offset = 0;
      std::istringstream (password) >> offset; // convert text to number for key
      offset %= 26;
      for(int i = 0; i < source.length(); i++)
      {
         destination[i] = toCaesar(source[i], -offset);
      }
      return destination;
   }
};

#endif // CIPHER33_H
