/********************************************************************
 * Header:
 *    Implement your cipher here. You can view 'example.h' to see the
 *    completed Case Cipher example.
 ********************************************************************/
#ifndef CIPHER4_H
#define CIPHER4_H

/********************************************************************
 * CLASS
 *******************************************************************/
class Cipher4 : public Cipher
{
  public:
   virtual std::string getPseudoAuth()  { return "Mackenzie Bodily"; }
   virtual std::string getCipherName()  { return "ROT13"; }
   virtual std::string getEncryptAuth() { return "David Donley"; }
   virtual std::string getDecryptAuth() { return "Bruce Niendorf"; }

   /***********************************************************
    * GET CIPHER CITATION
    * Returns the citation from which we learned about the cipher
    ***********************************************************/
   virtual std::string getCipherCitation()
   {
      return std::string("https://en.wikipedia.org/wiki/ROT13");
   }
   
   /**********************************************************
    * GET PSEUDOCODE
    * Returns the pseudocode as a string to be used by the caller.
    **********************************************************/
   virtual std::string getPseudocode()
   {
      
      std::string str;
      // The encrypt pseudocode
     /*  str =  "get string\n" + "loop through each letter of the string and\n" + "\tfor each letter, convert it to its integer representation\n" +
             "\t\t(the following ensures that it stays in the letters)\n" + 
             "\tif the letter is upper case\n" +
             "\t\tsubtract 90 and add 65\n" +
             "\tif the letter is lower case\n" +
             "\t\tsubtract 122 and add 97\n" +
             "\t\tAdd the character to the output string\n" +
             "\t\tReturn the output string.\n" +
             "--end encryption--\n\n";

             // The decrypt pseudocode
      str += "get string\n" +
             "loop through each letter of the string and\n" +
             "\tget the integer representation of the letter.\n" +
             "\tif it's a space just add space to the final string and move on." +
             "\tsubtract 13" +
             "\tif the character is upper case && less than 65\n" +
             "\t\tor it is lower case and less than 97\n" +
             "\t\tadd 25\n" +
             "\t\tAdd the character to the output string\n" +
             "\t\tReturn the output string\n" +
             "--end decryption--\n\n"; */
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
      std::string encryptString;
      int intRepresent;

      for(int i = 0; i < destination.length(); i++)
      {
         intRepresent = (int)source[i];
         
         if(destination[i] >= 'A' && destination[i] <= 'Z')
         {
            intRepresent = intRepresent - 90;
            intRepresent = intRepresent + 65;
            encryptString += (char)intRepresent;
         }  
         else if(destination[i] >= 'a' && destination[i] <= 'z')
         {
            intRepresent = intRepresent - 122;
            intRepresent = intRepresent + 97;
            encryptString += (char)intRepresent;
         }
      }
      destination = encryptString;
      return destination;
   }

   /**********************************************************
    * DECRYPT
    * TODO: ADD description
    **********************************************************/
   virtual std::string decrypt(const std::string & source, 
                               const std::string & password)
   {
      std::string destination = source;
      
      std::string decryptedString;
      int intRepresentation;
      int altered;
      char space = ' ';
    
      for (int i = 0; i < source.length(); i++)
      {
         intRepresentation = (int)source[i];
         altered = intRepresentation - 13;

         // Check if the current character is a space first
         if (source[i] == space)
         {
            decryptedString += ' ';
         }
         else if ((isupper((char)intRepresentation) && altered < 65) ||
                  (islower((char)intRepresentation) && altered < 97))
         {
            // This is if the regular rotation goes past 'A' or 'a'
            altered = altered + 26;
            decryptedString += (char)altered;
         }
         else
         {
            // This is the regular rotation
            decryptedString += (char)altered;
         }
     }
      destination = decryptedString;
      return destination;
   }
};

#endif // CIPHER4_H
