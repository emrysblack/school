/********************************************************************
* Header:
*    Implement your cipher here. You can view 'example.h' to see the
*    completed Case Cipher example.
********************************************************************/
#ifndef CIPHER1_H
#define CIPHER1_H
#include <sstream>

/********************************************************************
 * CLASS
 *******************************************************************/
class Cipher1 : public Cipher
{
public:
   virtual std::string getPseudoAuth()  { return "McKay Smalley"; }
   virtual std::string getCipherName()  { return "Caesar Cipher"; }
   virtual std::string getEncryptAuth() { return "Devin LaCrosse"; }
   virtual std::string getDecryptAuth() { return "Palmer Cluff"; }

   /***********************************************************
    * GET CIPHER CITATION
    * Returns the citation from which we learned about the cipher
    ***********************************************************/
   virtual std::string getCipherCitation()
   {
      return std::string("http://www.simonsingh.net/The_Black_Chamber/caesar.html");
   }
   
   /**********************************************************
    * GET PSEUDOCODE
    * Returns the pseudocode as a string to be used by the caller.
    **********************************************************/
   virtual std::string getPseudocode()
   {
      std::string str;

      // The encrypt pseudocode
      str =  "encryptCaesar(source, password)\n"
         "    key = password % 26\n"
         "    FOR each letter in source\n"
         "       destination[i] = source[i]+key\n"
         "       IF destination[i] > 90\n"
         "          destination[i] -= 26\n"
         "    RETURN destination\n\n";
      
      // The decrypt pseudocode
      str += "decryptCausar(source, password)\n"
         "    key = password % 26\n"
         "    FOR each letter in source\n"
         "       destination[i] = source[i]-key\n"
         "       IF destination[i] < 65 AND destination[i] != ' ' \n"
         "          destination[i] += 26\n"
         "    RETURN destination\n";
      
      return str;
   }

   /**********************************************************
    * ENCRYPT
    * First it converts the password to an int, and stores it
    * as the key. Next it loops through and converts each
    * letter in source to upper case, and adds the key to each
    * char. Then, it wraps letters that are greater than 'Z'
    * back to 'A'. Finally it returns the encrypted string.
    **********************************************************/
   virtual std::string encrypt(const std::string & source, 
                               const std::string & password)
   {
      std::string destination = source;
      // TODO - Add your code here
      int key;
      std::stringstream s_str(password);
      s_str >> key; //convert string password to int
      key %= 26;    //ensures that the key will be between 0-25

      //loop through the source
      for (int i = 0; i < destination.length(); ++i)
      {
         //add the key to the uppercase ascii value
         destination[i] = toupper(source[i]) + key;

         //wrap overflow back to the begining of alphabet
         if (destination[i] > 90)
            destination[i] -= 26;
      }
      return destination;
   }

    /**********************************************************
    * DECRYPT
    * First, it converst the password to an int, and stores it
    * as the key. Next, it subtracts the key from each letter
    * and undoes the wrapping done during encryption. Then it
    * returns the destination.
    **********************************************************/
  virtual std::string decrypt(const std::string & source, 
                               const std::string & password)
   {
      std::string destination = source;
      // TODO - Add your code here
      int key;
      std::stringstream s_str(password);
      s_str >> key; //convert string password to int
      key %= 26;    //ensures that the key will be between 0-25

      //loop through the source
      for (int i = 0; i < destination.length(); ++i)
      {
         //subtract the key from the source ascii value
         destination[i] = source[i] - key;

         //wrap underflow to the end of the alphabet (except for spaces)
         if (destination[i] < 65 and destination[i] != ' ')
            destination[i] += 26;
      }
      
      return destination;
   }
};

#endif // CIPHER1_H
