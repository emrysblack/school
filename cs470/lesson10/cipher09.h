/********************************************************************
* Header:
*    Implement your cipher here. You can view 'example.h' to see the
*    completed Case Cipher example.
********************************************************************/
#ifndef CIPHER9_H
#define CIPHER9_H

/********************************************************************
 * CLASS
 *******************************************************************/
class Cipher9 : public Cipher
{
public:
   virtual std::string getPseudoAuth()  { return "James Richter"; }
   virtual std::string getCipherName()  { return "Caesar Cipher"; }
   virtual std::string getEncryptAuth() { return "Gizmo Bentim"; }
   virtual std::string getDecryptAuth() { return "Salvador Ernesto Afane"; }

   /***********************************************************
    * GET CIPHER CITATION
    * Returns the citation from which we learned about the cipher
    ***********************************************************/
   virtual std::string getCipherCitation()
   {
      return std::string("http://www.cs.trincoll.edu/~crypto/historical/caesar.html");
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
      str =  "asciiUpperBound = 126\n"
             "asciiRange = 95\n"
             "for character in source:\n"
             "\tcharacter += 15\n"
             "\tif character > asciiUpperBound:\n"
             "\t\tcharacter -= asciiRange\n\n";

      // The decrypt pseudocode
      str += "asciiLowerBound = 32\n"
             "asciiRange = 95\n"
             "for character in string:\n"
             "\tcharacter -= 15\n"
             "\tif character > asciiLowerBound:\n"
             "\t\tcharacter += asciiRange\n";

      return str;
   }

   /**********************************************************
    * ENCRYPT
    **********************************************************/
   virtual std::string encrypt(const std::string & source, 
                               const std::string & password)
   {
      std::string destination = "";

      int key =  atoi(password.c_str());
    
      int asciiUpperBound = 126;
      int asciiRange = 95;

      for (int i = 0; i < source.length(); i++)
      {
         char character = source[i] + key;
         if (character > asciiUpperBound )
            character -= asciiRange; 
         destination += character;
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
      
      int key =  atoi(password.c_str());
    
      int asciiUpperBound = 126;
      int asciiRange = 95;

      /* for (int i = 0; i < source.length(); i++)
      {
         char character = source[i] + key;
         if (character > asciiUpperBound )
            character -= asciiRange; 
         destination -= character;
      } */
      
      
      return destination;
   }
};

#endif // CIPHER9_H
