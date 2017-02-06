/********************************************************************
* Header:
*    Implement your cipher here. You can view 'example.h' to see the
*    completed Case Cipher example.
********************************************************************/
#ifndef CIPHER15_H
#define CIPHER15_H
#include <sstream>
/********************************************************************
 * CLASS
 *******************************************************************/
class Cipher15 : public Cipher
{
public:
   virtual std::string getPseudoAuth()  { return "Ryan Muse"; }
   virtual std::string getCipherName()  { return "Caesar Cipher"; }
   virtual std::string getEncryptAuth() { return "Brady Field"; }
   virtual std::string getDecryptAuth() { return "decrypt author"; }

   /***********************************************************
    * GET CIPHER CITATION
    * Returns the citation from which we learned about the cipher
    ***********************************************************/
   virtual std::string getCipherCitation()
   {
      std::string url =
         "http://www.codeabbey.com/index/task_view/caesar-shift-cipher\n";
      url += "http://mathworld.wolfram.com/CaesarsMethod.html";

      return std::string(url);
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
      str =  "get password\n";
      str += "set offset to 0\n";
      str += "for each character in password\n";
      str += "\tset offset to offset + numberValueOfCharacter\n";
      str += "set offset to offset mod alphabet Size\n";
      str += "if offset equals 0\n";
      str += "\tset offset to 1\n";
      str += "get text\n";
      str += "set cipherText to empty string\n";
      str += "loop for iterator equals text start to iterator equals";
      str += " text length\n";
      str += "\tset numberValue to number value of text character";
      str += " at iterator\n";
      str += "\tset cipherNumberValue to numberValueplus offset";
      str += " mod alphabet Size\n";
      str += "\tset cipherLetter to letter value of cipherNumberValue\n";
      str += "\tset cipherText character at same iterator position as";
      str += " text to cipherLetter\n";
      str += "\tincrement iterator\n";
      str += "return cipherText\n";

      // The decrypt pseudocode
      str += "get password\n";
      str += "set offset to 0\n";
      str += "for each character in password\n";
      str += "\tset offset to offset + numberValueOfCharacter\n";
      str += "set offset to offset mod alphabetSize\n";
      str += "if offset equals 0\n";
      str += "\tset offset to 1\n";
      str += "get cipherText\n";
      str += "set plainText to empty string\n";
      str += "loop for iterator equals cipherText start to iterator equals";
      str += " cipherText length\n";
      str += "\tset cipherNumberValue to number value of cipherText";
      str += " character at iterator\n";
      str += "\tset plainNumberValue to cipherNumberValue minus offset mod";
      str += " alphabetSize\n";
      str += "\tset plainLetter to letter value of plainNumberValue\n";
      str += "\tset plainText character at same iterator position as";
      str += " cipherText to plainLetter\n";
      str += "\tincrement iterator\n";
      str += "return plainText\n";

      return str;
   }

   /**********************************************************
    * ENCRYPT
    **********************************************************/
   virtual std::string encrypt(const std::string & source,
                               const std::string & password)
   {
      std::string destination = source;
      int offset = 0;
      std::istringstream (password) >> offset; // convert text to number for key
      offset %= 26;
      for(int i = 0; i < source.length(); i++)
      {
         if(isalpha(destination[i]))
         {
            destination[i] = ((toupper(source[i]) + offset - 'A') % 26) + 'A';
            if (islower(source[i]))
            {
               destination[i] = tolower(destination[i]);
            }
         }
      }
      return destination;
   }

   /**********************************************************
    * DECRYPT
    **********************************************************/
   virtual std::string decrypt(const std::string & source,
                               const std::string & password)
   {
      std::string destination = source;
      // TODO - Add your code here
      return destination;
   }
};

#endif // CIPHER15_H
