/********************************************************************
* Header:
*    Implement your cipher here. You can view 'example.h' to see the
*    completed Case Cipher example.
********************************************************************/
#ifndef CIPHER5_H
#define CIPHER5_H

/********************************************************************
 * CLASS
 *******************************************************************/
class Cipher5 : public Cipher
{
public:
   virtual std::string getPseudoAuth()  { return "David Donley"; }
   virtual std::string getCipherName()  { return "Vigenere Cipher"; }
   virtual std::string getEncryptAuth() { return "Mackenzie Bodily"; }
   virtual std::string getDecryptAuth() { return "Hanlet Escano"; }

   /***********************************************************
    * GET CIPHER CITATION
    * Returns the citation from which we learned about the cipher
    ***********************************************************/
   virtual std::string getCipherCitation()
   {
      return std::string("https://en.wikipedia.org/wiki/Vigen%C3%A8re_cipher");
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
      str =  "encrypt(source, passowrd)\n"
         "     Declare output\n"
         "     Declare Key\n"
         "     FOR each letter in the password\n"
         "        IF the password contains letters between A - Z\n"
         "          key += password[i]\n"
         "        ELSE IF the password containse letters between a - z\n"
         "          key += uppercase password[i]\n"
         "    count = 0"
         "     FOR each letter in the destination\n"
         "        IF destination[i] is a letter between a - z\n"
         "          Change letter to uppercase\n"
         "        output += (destination[i]+ key[count] - 2 * 'A') modulus 26 + 'A'\n"
         "        count = (count + 1) modulus key.length()\n"
         "    return output\n";


      // The decrypt pseudocode
      str += "encrypt(source, passowrd)\n"
         "     Declare output\n"
         "     Declare Key\n"
         "     FOR each letter in the password\n"
         "        IF the password contains letters between A - Z\n"
         "          key += password[i]\n"
         "        ELSE IF the password containse letters between a - z\n"
         "          key += uppercase password[i]\n"
         "     count = 0\n"
         "     FOR each letter in the destination\n"
         "        IF destination[i] is a letter between a - z\n"
         "          Change letter to uppercase\n"
         "     output += (destination[i] - key[count] +26) modulus 26 + 'A'\n"
         "     count = (count + 1) modulus key.length()\n"
         "     return output\n";

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
      // TODO - Add your code here
      std::string out;
      std::string key;

      for(int i = 0; i < password.size(); ++i)
      {
         if(password[i] >= 'A' && password[i] <= 'Z')
            key += password[i];
         else if(password[i] >= 'a' && password[i] <= 'z')
            key += password[i] + 'A' - 'a';
      }

      for(int i = 0, j = 0; i < destination.length(); ++i)
      {
         char c = destination[i];

         if(c >= 'a' && c <= 'z')
            c += 'A' - 'a';
         else if(c < 'A' || c > 'Z')
            continue;

         out += (c + key[j] - 2*'A') % 26 + 'A';
         j = (j + 1) % key.length();
      }

      return out;
   }

  /**********************************************************
    * DECRYPT
    * TODO: Uses Vigenère cipher to decrypt a text.
    **********************************************************/
   virtual std::string decrypt(const std::string & source, 
                               const std::string & password)
   {
      std::string destination = source;
      std::string out;
      std::string key;

      for(int i = 0; i < password.size(); ++i)
      {
         if(password[i] >= 'A' && password[i] <= 'Z')
         {
            key += password[i];
         }
         else if(password[i] >= 'a' && password[i] <= 'z')
         {
            key += toupper(password[i]);
         }
      }

      for(int i = 0, j = 0; i < destination.length(); ++i)
      {
         char c = destination[i];

         if(c >= 'a' && c <= 'z')
         {
            c += toupper(password[i]);
         }
         else if(c < 'A' || c > 'Z')
         {
            continue;
         }

         out += (c - key[j] + 26) % 26 + 'A';
         j = (j + 1) % key.length();
      }

      return out;
   }
};

#endif // CIPHER5_H
