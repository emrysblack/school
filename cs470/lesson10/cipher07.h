/********************************************************************
* Header:
*    Implement your cipher here. You can view 'example.h' to see the
*    completed Case Cipher example.
********************************************************************/
#ifndef CIPHER7_H
#define CIPHER7_H

/********************************************************************
 * CLASS
 *******************************************************************/
class Cipher7 : public Cipher
{
public:
   virtual std::string getPseudoAuth()  { return "Bruce Niendorf"; }
   virtual std::string getCipherName()  { return "Atbash"; }
   virtual std::string getEncryptAuth() { return "Hanlet Escano"; }
   virtual std::string getDecryptAuth() { return "David Donley"; }

   /***********************************************************
    * GET CIPHER CITATION
    * Returns the citation from which we learned about the cipher
    ***********************************************************/
   virtual std::string getCipherCitation()
   {
      return std::string("http://crypto.interactive-maths.com/atbash-cipher.html\n  http://crypto.interactive-maths.com/atbash-cipher.html\n");
   }
   
   /**********************************************************
    * GET PSEUDOCODE
    * Returns the pseudocode as a string to be used by the caller.
    **********************************************************/
   virtual std::string getPseudocode()
   {
      std::string str;

      // The encrypt pseudocode (no key is needed, so the 'password' can be ignored)
      // Atbash pseudocode
      str = "alphabet ='ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz'\n";
      str+= "atbash ='ZYXWVUTSRQPONMLKJIHGFEDCBAzyxwvutsrqponmlkjihgfedcba'\n";
      str+= "get source\n";
      str+= "  for length of source\n";
      str+= "    for length of alphabet\n";
      str+= "      if source[i] == alphabet[i]\n";
      str+= "        encryptedString += atbash[i]\n";
      str+= "      else encryptedString += source\n"; //This atbash doesn't deal
                                                      //with numbers or spaces

      // The decrypt pseudocode (no key is needed, so the 'password' can be ignored)
      str+= "atbash ='ZYXWVUTSRQPONMLKJIHGFEDCBAzyxwvutsrqponmlkjihgfedcba'\n";
      str = "alphabet ='ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz'\n";
      str+= "get source\n";
      str+= "  for length of source\n";
      str+= "    for length of atbash\n";
      str+= "      if source[i] == atbash[i]\n";
      str+= "        decryptedString += alphabet[i]\n";
      str+= "      else decryptedString += source\n";//This atbash doesn't deal
                                                     //with numbers or spaces

      return str;
   }

   /**********************************************************
    * ENCRYPT
    * TODO: Encrypts a text using the Atbash cipher.
    **********************************************************/
   virtual std::string encrypt(const std::string & source, 
                               const std::string & password)
   {
      std::string destination = "";
      std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
      std::string atbash = "ZYXWVUTSRQPONMLKJIHGFEDCBAzyxwvutsrqponmlkjihgfedcba";
      
      for (int i = 0; i < source.length(); i++)
      {
         for (int j = 0; j < alphabet.length(); j++)
         {
            if (source[i] == alphabet[j])
            {
               destination += atbash[j];
               break; //no need to continue
            }
         }
      }
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
      std::string alphabet ="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
      std::string atbash = "ZYXWVUTSRQPONMLKJIHGFEDCBAzyxwvutsrqponmlkjihgfedcba";
      
      for(int i = 0; i < source.length(); i++)
      {
         for(int j = 0; j < atbash.length(); i++)
         {
            if(source[i] == atbash[i])
            {
               destination += alphabet[i];
            }
         }
      }
      return destination;
   }
};

#endif // CIPHER7_H
