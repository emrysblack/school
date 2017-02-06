/********************************************************************
* Header:
*    Implement your cipher here. You can view 'example.h' to see the
*    completed Case Cipher example.
********************************************************************/
#ifndef CIPHER35_H
#define CIPHER35_H

#include <string>
#include <vector>

const char ALPHABET[] =
              "abcdefghijklmnopqrstuvwxyz" \
              "ABCDEFGHIJKLMNOPQRSTUVWXYZ" \
              "1234567890"\
   " ~!@#$%^&*(),./<>?;':\"[]{}\\|";
const int ALPHABET_SIZE = sizeof(ALPHABET) - 1;


/********************************************************************
 * CLASS
 *******************************************************************/
class Cipher35 : public Cipher
{
public:
   virtual std::string getPseudoAuth()  { return "Br. Helfrich"; }
   virtual std::string getCipherName()  { return "Multi-alphabet"; }
   virtual std::string getEncryptAuth() { return "Br. Helfrich"; }
   virtual std::string getDecryptAuth() { return "Br. Helfrich"; }

   /*****************************************************
    * INDEX FROM ALPHABET
    * Find the offset of a character in the ALPHABET string
    *******************************************************/
   int indexFromAlphabet(char letter)
   {
      for (const char * p = ALPHABET; *p; p++)
         if (*p == letter)
            return (int)(p - ALPHABET);
      return 0;
   }
   
   
   /***********************************************************
    * GET CIPHER CITATION
    * Returns the citation from which we learned about the cipher
    ***********************************************************/
   virtual std::string getCipherCitation()
   {
      return std::string("citation");
   }

   /**********************************************************
    * GET PSEUDOCODE
    * Returns the pseudocode as a string to be used by the caller.
    **********************************************************/
   virtual std::string getPseudocode()
   {
      std::string str;

      // The encrypt pseudocode
      str =  "encryptMulti(source, password)\n" \
         "    FOR each letter in password\n" \
         "       offset[i] = indexFromAlphabet(letter)\n" \
         "\n" \
         "    FOR each letter in source\n" \
         "      index = (indexFromAlphabet(letter) + offset[i % numOffsets]\n"\
         "      destination += alphabet[index % alphabetSize]\n" \
         "    RETURN destination\n" \
         "\n";

      // The decrypt pseudocode
      str +=  "decryptMulti(source, password)\n" \
         "    FOR each letter in password\n" \
         "       offset[i] = alphabetSize - indexFromAlphabet(letter)\n" \
         "\n" \
         "    FOR each letter in source\n" \
         "      index = (indexFromAlphabet(letter) + offset[i % numOffsets]\n"\
         "      destination += alphabet[index % alphabetSize]\n" \
         "    RETURN destination\n" \
         "\n";

      return str;
   }

   /**********************************************************
    * ENCRYPT
    **********************************************************/
   virtual std::string encrypt(const std::string & source, 
                               const std::string & password)
   {
      // turn the password into a series offset
      std::vector <int> offsets;
      for (const char *p = password.c_str(); *p; p++)
         offsets.push_back(indexFromAlphabet(*p));

      // now build the ciphertext
      std::string destination;
      for (int i = 0; i < source.length(); i++)
      {
         int index = indexFromAlphabet(source[i]) +
            offsets[i % offsets.size()];
         destination += ALPHABET[index % ALPHABET_SIZE];
      }

      // make like a tree
      return destination;
   }

   /**********************************************************
    * DECRYPT
    **********************************************************/
   virtual std::string decrypt(const std::string & source, 
                               const std::string & password)
   {
      // turn the password into a series offset
      std::vector <int> offsets;
      for (const char *p = password.c_str(); *p; p++)
         offsets.push_back(ALPHABET_SIZE - indexFromAlphabet(*p));

      // now build the ciphertext
      std::string destination;
      for (int i = 0; i < source.length(); i++)
      {
         int index = indexFromAlphabet(source[i]) +
            offsets[i % offsets.size()];
         destination += ALPHABET[index % ALPHABET_SIZE];
      }

      // make like a tree
      return destination;
   }
};

#endif // CIPHER35_H
