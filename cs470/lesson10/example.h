/********************************************************************
* Header:
*    example.h
*    A simple Case Cipher to show what each header file should contain.
********************************************************************/
#ifndef EXAMPLE_H
#define EXAMPLE_H

/********************************************************************
 * CLASS CIPHER
 *******************************************************************/
class Example : public Cipher
{
public:
   virtual std::string getPseudoAuth()  { return "Brother Helfrich"; } 
   virtual std::string getCipherName()  { return "Case Cipher";      }
   virtual std::string getEncryptAuth() { return "Brother Helfrich"; }
   virtual std::string getDecryptAuth() { return "Brother Helfrich"; }

   /***********************************************************
    * GET CIPHER CITATION
    * Returns the citation from which we learned about the cipher
    ***********************************************************/
   virtual std::string getCipherCitation()
   {
      return std::string("Helfrich, J (2014) _I_Made_This_Up");
   }
   
   /**********************************************************
    * GET PSEUDOCODE
    * Returns the psuedocode as a string to be used by the
    * caller.
    **********************************************************/
   virtual std::string getPseudocode()
   {
      std::string str;

      // The encryptCase pseudocode
      str =  "encryptCase\n";
      str += "   FOR each letter i in source\n";
      str += "      IF isupper for that letter\n";
      str += "         destination[i] = tolower source[i]\n";
      str += "      ELSE\n";
      str += "         destination[i] = toupper source[i]\n";
      str += "   RETURN\n\n";

      // The decryptCase pseudocode
      str += "To decrypt use encryptCase, ";
      str += "This algorithm is symmetric\n";

      return str;
   }

   /**********************************************************
    * ENCRYPT CASE
    * Simple encryption algorithm where we reverse the case.
    * The password field is not used
    **********************************************************/
   virtual std::string encrypt(const std::string & source, 
                               const std::string & password)
   {
      std::string destination;
      for (const char * p = source.c_str(); *p; p++)
         if (isupper(*p))
            destination += tolower(*p);
         else
            destination += toupper(*p);
      return destination;
   }

   /**********************************************************
    * DECRYPT CASE
    * The case "encryption" algorithm is symmetric
    **********************************************************/
   virtual std::string decrypt(const std::string & source, 
                               const std::string & password)
   {
      return encrypt(source, password);
   }
};

#endif // EXAMPLE_H
