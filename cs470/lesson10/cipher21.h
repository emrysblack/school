/********************************************************************
* Header:
*    Implement your cipher here. You can view 'example.h' to see the
*    completed Case Cipher example.
********************************************************************/
#ifndef CIPHER21_H
#define CIPHER21_H

/********************************************************************
 * CLASS
 *******************************************************************/
class Cipher21 : public Cipher
{
public:
   virtual std::string getPseudoAuth()  { return "pseudocode author"; }
   virtual std::string getCipherName()  { return "cipher name"; }
   virtual std::string getEncryptAuth() { return "encrypt author"; }
   virtual std::string getDecryptAuth() { return "decrypt author"; }

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

      // TODO: please format your pseudocode
      // The encrypt pseudocode
      str =  "insert the encryption pseudocode\n";

      // The decrypt pseudocode
      str += "insert the decryption pseudocode\n";

      return str;
   }

   /**********************************************************
    * ENCRYPT
    **********************************************************/
   virtual std::string encrypt(const std::string & source, 
                               const std::string & password)
   {
      std::string destination = source;
      // TODO - Add your code here
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

#endif // CIPHER21_H
