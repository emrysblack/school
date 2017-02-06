/********************************************************************
* Header:
*    Implement your cipher here. You can view 'example.h' to see the
*    completed Case Cipher example.
********************************************************************/
#ifndef CIPHER8_H
#define CIPHER8_H

/********************************************************************
 * CLASS
 *******************************************************************/
class Cipher8 : public Cipher
{
public:
   virtual std::string getPseudoAuth()  { return "Guilherme 'Gizmo' Bentim" ; }
   virtual std::string getCipherName()  { return "Vigenere"; }
   virtual std::string getEncryptAuth() { return "James Richter"; }
   virtual std::string getDecryptAuth() { return "Mackenzie Bodily"; }

   /***********************************************************
    * GET CIPHER CITATION
    * Returns the citation from which we learned about the cipher
    ***********************************************************/
   virtual std::string getCipherCitation()
   {
      return std::string("http://www.cs.trincoll.edu/~crypto/historical/vigenere.html"
                         "http://en.algoritmy.net/article/45623/Vigenere-cipher");
   }
   
   /**********************************************************
    * GET PSEUDOCODE
    * Returns the pseudocode as a string to be used by the caller.
    **********************************************************/
   virtual std::string getPseudocode()
   {
      std::string str;

      str = "encrypt(source, password)"
                        "declare key"

                        "FOR i in size of password"
                           "IF passoword[i] >= 'A' && passoword[i] <= 'Z'"
                              "key += password[i]"
                           "ELSE"
                              "key += password[i] + 'A' - 'a'"


                        "declare output"

                        "FOR i in size of source"
                           "j = 0"
                           "c = source[i]"
                           "IF c >= 'a' && c <= 'z'"
                              "c += 'A' - 'a'"
                           "ELSE IF c < 'A' || c > Z"
                              "continue"

                           "output += (c + key[j] - 2 * 'A') % 26 + 'A'"
                           "j = (j + 1) % size of key"

                        "return output";

      
      str += "decrypt(source, password)"
                        "declare key"

                        "FOR i in size of password"
                           "IF passoword[i] >= 'A' && passoword[i] <= 'Z'"
                              "key += password[i]"
                           "ELSE"
                              "key += password[i] + 'A' - 'a'"

                        "declare output"

                        "FOR i in size of text"
                           "j = 0"
                           "c = text[i]"
                           "IF c >= 'a' && c <= 'z'"
                              "c += 'A' - 'a'"
                           "ELSE IF c < 'A' || c > Z"
                              "continue"

                           "output += (c - key[j] + 26) % 26 + 'A'"
                           "j = (j + 1) % size of key"

                        "reutrn output";
      

      return str;
   }

   /**********************************************************
    * ENCRYPT
    * This is the encryption function for the Vigenere Cipher.
    * It takes a password and creates a string where that 
    * password repeats for the length of the input.
    * Then, it uses a caesar cipher according to the letter
    * of the repeated password.
    **********************************************************/
   virtual std::string encrypt(const std::string & source, 
                               const std::string & password)
   {
      std::string key;

      for (int i = 0; i < password.length(); i++)
      {
         if (password[i] >= 'A' && password[i] <= 'Z')
            key += password[i];
         else
            key += password[i] + 'A' - 'a';
      }
      
      std::string output;

      for (int i = 0; i < source.length(); i++)
      {
         int j = 0;
         char c = source[i];
         if (c >= 'a' && c <= 'z')
            c += 'A' - 'a';
         else if (c < 'A' || c > 'Z')
            continue;

         output += (c + key[j] - 2 * 'A') % 26 + 'A';
         j = (j + 1); // size of key
      }
      
      return output;
   }

   /**********************************************************
    * DECRYPT
    * TODO: ADD description
    **********************************************************/
   virtual std::string decrypt(const std::string & source, 
                               const std::string & password)
   {
      std::string destination = source;
      // TODO - Add your code here


      //this key needs to be declared elsewhere, but in
      //this case a default is supplied.
      std::string key = "LEMON";

      //strips the output so it works.
      for(int i = 0; i < password.length(); i++)
      {
         if(password[i] >= 'A' && password[i] <= 'Z')
         {
            key += password[i];
         }
         else
         {
            key += password[i] + 'A' - 'a';
         }
      }

      std::string output = "";
      //switched from password to text in the psuedo code here
      //but it meant the same thing.
      for(int i = 0; i < password.length(); i++)
      {
         int j = 0;
         char c = password[i];
         if (c >= 'a' && c <= 'z')
         {
            c += 'A' - 'a';
         }
         else if (c < 'A' || c > 'Z')
         {
            continue;
         }
         output += (c - key[j] + 26) % 26 + 'A';
         j = (j + 1) % key.length();
      }
      return output;
   }
};

#endif // CIPHER8_H
