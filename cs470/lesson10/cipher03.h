/********************************************************************
* Header:
*    Polyalphabetic Substitution
********************************************************************/
#ifndef CIPHER3_H
#define CIPHER3_H
#include <sstream>

/********************************************************************
 * CLASS
 *******************************************************************/
class Cipher3 : public Cipher
{
public:
   virtual std::string getPseudoAuth()  { return "Palmer Cluff"; }
   virtual std::string getCipherName()  { return "Polyalphabetic Substitution"; }
   virtual std::string getEncryptAuth() { return "McKay Smalley"; }
   virtual std::string getDecryptAuth() { return "Devin LaCrosse"; }

   /***********************************************************
    * GET CIPHER CITATION
    * Returns the citation from which we learned about the cipher
    ***********************************************************/
   virtual std::string getCipherCitation()
   {
      return std::string("http://ccis2k.org/iajit/PDF/vol.5,no.1/12-69.pdf");
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
      str = "FUNCTION ENCRYPT\n";
      str += "encode <- source size[]\n";
      // Create the encode from password
      str += "FOR i <- 0 UPTO source size\n";
      str = "FUNCTION ENCRYPT\n";
      str += "encode <- source size[]\n";
      // Create the encode from password
      str += "FOR i <- 0 UPTO source size\n";
      str += "   SET encode[i] to i + password size MOD 3\n"; // password[0..3] ={0,1,2,3}
      str += "END FOR\n";
      // Generate the 'plain key'
      str += "FOR char <- ' ' UPTO '~'\n"; // All printable chars
      str += "   plainkey <- plainkey + char\n"; // Append each character
      str += "END FOR\n";
      // Generate 3 different iterations (cipherkeys)
      // of the characters in the plain key
      str += "FOR i <- 0 UPTO plainkey size\n";
      str += "   cipherkeys[0] <- cipherkeys[0] + (plainkey[i] + 1)\n"; // +1 cipher
      str += "   cipherkeys[1] <- cipherkeys[1] + (plainkey[i] - 1)\n"; // -1 cipher
      str += "   cipherkeys[2] <- cipherkeys[2] + (plainkey[i] + 2)\n"; // +2 cipher
      str += "END FOR\n";
      str += "FOR i <- 0 UPTO source size\n";
      // Determine index of character in plainkey
      str += "   indexOfLetter <- plainkey.find(source[i])\n";
      // The password provides a reference to which cipherkey to use for that character
      str += "   destination <- destination + cipherkeys[encode[i]][indexOfLetter]\n";
      str += "END FOR\n";
      str += "END FUNCTION ENCRYPT\n\n";
      
      // The decrypt pseudocode
      str += "FUNCTION DECRYPT\n";
      str += "encode <- source size[]\n";
      // Create the encode from password
      str += "FOR i <- 0 UPTO source size\n";
      str += "   SET encode[i] to i + password size MOD 3\n"; // password[0..3] ={0,1,2,3}
      str += "END FOR\n";
      // Have the same plain key and cipher keys used to encrypt
      str += "FOR char <- ' ' UPTO '~'\n";
      str += "   plainkey <- char\n";
      str += "END FOR\n";
      str += "For i <- 0 UPTO plainkey.size\n";
      str += "   cipherkeys[0] <- plainkey[i] + 1\n";
      str += "   cipherkeys[1] <- plainkey[i] - 1\n";
      str += "   cipherkeys[2] <- plainkey[i] + 2\n";
      str += "END FOR\n";

      str += "FOR i <- 0 UPTO source size\n";
      // Find the index of the plainkey from the cipher key and the given character
      str += "   indexOfCipher <- cipherkeys[encode[i]].find(source[i])\n";
      // Add the decrypted character to the decrypted message
      str += "   destination <- destination + plainkey[indexOfCipher]\n";
      str += "END FOR\n";
      str += "END FUNCTION DECRYPT\n";

      return str;
   }

   /**********************************************************
    * ENCRYPT
    * TODO: ADD description
    **********************************************************/
   virtual std::string encrypt(const std::string & source, 
                               const std::string & password)
   {
      std::string destination;

      //used for which cipher key is to be used
      int * encode;
      encode = new int[source.size()];

      //create the encode
      for (int i = 0; i < source.size(); i++)
      {
         if ((password.size() + i) % 3 == 0)
         {
            encode[i] = 0;
         }
         else if ((password.size() +
                   i) % 3 == 1)
         {
            encode[i] = 1;
         }
         else
            encode[i] = 2;
      }

      //the standard which all are based on
      std::string plainKey;
      for (char a =  ' '; a <= '~'; a++)
      {
         plainKey += a;
      }

      std::string cipherKeys[3];

      for (int i = 0; i < plainKey.size(); i++)
      {
         if (plainKey[i] == '~')
         {
            cipherKeys[0] += ' ';
         }
         else
         {
            cipherKeys[0] += plainKey[i] + 1;
         }

         //second
         if (plainKey[i] == ' ')
         {
            cipherKeys[1] += '~';
         }
         else
         {
            cipherKeys[1] += plainKey[i] - 1;
         }

         //third
         if (plainKey[i] == '~')
            cipherKeys[2] += '!';
         else if (plainKey[i] == '}')
            cipherKeys[2] += '}';
         else
            cipherKeys[2] += plainKey[i] + 2;
      }

      for (int i = 0; i < source.size(); i++)
      {
         int index = encode[i];
         char putChar = source[i];
         int indexOfLetter = plainKey.find(putChar);

         destination += cipherKeys[index][indexOfLetter];
      }

      delete [] encode;
      
      return destination;
   }

   /**********************************************************
    * DECRYPT
    * TODO: ADD description
    **********************************************************/
   virtual std::string decrypt(const std::string & source, 
                               const std::string & password)
   {
      std::string destination;

      //used for which cipher key is to be used
      int * encode;
      encode = new int[source.size()];

      //create the encode
      for (int i = 0; i < source.size(); i++)
      {
         if ((password.size() + i) % 3 == 0)
         {
            encode[i] = 0;
         }
         else if ((password.size() +
                   i) % 3 == 1)
         {
            encode[i] = 1;
         }
         else
            encode[i] = 2;
      }

      //the standard which all are based on
      std::string plainKey;
      for (char a =  ' '; a <= '~'; a++)
      {
         plainKey += a;
      }

      std::string cipherKeys[3];

      for (int i = 0; i < plainKey.size(); i++)
      {
         if (plainKey[i] == '~')
         {
            cipherKeys[0] += ' ';
         }
         else
         {
            cipherKeys[0] += plainKey[i] + 1;
         }

         //second
         if (plainKey[i] == ' ')
         {
            cipherKeys[1] += '~';
         }
         else
         {
            cipherKeys[1] += plainKey[i] - 1;
         }

         //third
         if (plainKey[i] == '~')
            cipherKeys[2] += '!';
         else if (plainKey[i] == '}')
            cipherKeys[2] += '}';
         else
            cipherKeys[2] += plainKey[i] + 2;
      }

      for (int i = 0; i < source.size(); i++)
      {
         int index = encode[i];
         char putChar = source[i];
         int indexOfLetter = cipherKeys[index].find(putChar);

         destination += plainKey[indexOfLetter];
      }

      delete [] encode;

      return destination;      
   }
};

#endif // CIPHER3_H
