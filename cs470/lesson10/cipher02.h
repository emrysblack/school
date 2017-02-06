/********************************************************************
* Header:
*    Implement your cipher here. You can view 'example.h' to see the
*    completed Case Cipher example.
********************************************************************/
#ifndef CIPHER2_H
#define CIPHER2_H
#include "math.h"
#include "string.h"

/********************************************************************
 * CLASS
 *******************************************************************/
class Cipher2 : public Cipher
{
public:
   virtual std::string getPseudoAuth()  { return "Devin LaCrosse"; }
   virtual std::string getCipherName()  { return "Columnar Transposition"; }
   virtual std::string getEncryptAuth() { return "Palmer Cluff"; }
   virtual std::string getDecryptAuth() { return "Steven Mckay Smalley"; }

   /***********************************************************
    * GET CIPHER CITATION
    * Returns the citation from which we learned about the cipher
    ***********************************************************/
   virtual std::string getCipherCitation()
   {
      return std::string("arxiv.org/ftp/arxiv/papers/1307/1307.7786.pdf");
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
		
		str += "numCols <- length of password\n"
			"numRows <- ceiling ((plain Text size)/numCols)\n"
			"\n"
			"counter <- 0\n"
			"for i <- 0 upto numRows\n"
			"\tfor j <- 0 upto numCols\n"
			"\t\tif counter >= plainText length\n"
			"\t\t\tarray[i][j] <- -1\n"
			"\t\telse\n"
			"\t\t\tarray[i][j] <- plainText[counter]\n"
			"\t\tcounter <- counter + 1\n"
			"\n"
			"for j <- 0 upto numCols\n"
			"\tlowestIndex <- -1\n"
			"\tfor index <- 0 upto password length\n"
			"\t\tif password[index] != null and (lowest index = -1 or password[lowestIndex] > password[index])\n"
			"\t\t\tlowestIndex <- index\n"
			"\n"
			"\tfor i <- 0 upto numRows\n"
			"\t\tcipherText <- cipherText + array[i][lowestIndex\n"
			"\tpassword[lowestIndex] <- null\n\n";

      // The decrypt pseudocode
      str += "insert the decryption pseudocode\n";
		
		str += "numCols <- length of password\n"
			"numRows <- ceiling ((plain Text size)/numCols)\n"
			"\n"
			"counter <- 0\n"
			"for j <- 0 upto numCols\n"
			"\tfor i <- 0 upto numRows\n"
			"\t\tarray[i][j] <- plainText[counter]\n"
			"\t\tcount <- counter + 1\n"
			"\n"
			"for i <- 0 up to password length\n"
			"\tlowestIndex <- -1\n"
			"\tfor index <- 0 upto password length\n"
			"\t\tif password[index] != null and (lowest index = -1 or password[lowestIndex] > password[index])\n"
			"\t\t\tlowestIndex <- index\n"
			"\tpasswordIndex[lowestIndex] <- i\n"
			"\tpassword[lowestIndex] <- null\n"
			"\n"
			"for i <- 0 upto numRows\n"
			"\tfor j <- 0 upto numCols\n"
			"\t\tif array[i][passwordIndex[j]] != -1\n"
			"\t\t\tplainText += array[i][passwordIndex[j]]\n";

      return str;
   }

   /**********************************************************
    * ENCRYPT
    **********************************************************/
   virtual std::string encrypt(const std::string & source, 
                               const std::string & password)
   {
      std::string destination;

      // Determine size of rectangle used to create cipher
      int numCols = password.length();
      int numRows = ceil(((float)source.length())/((float)password.length()));

      // Create the framework to cipher the plaintext
      char ** array = new char*[numRows];
      for (int i = 0; i < numRows; i++)
         array[i] = new char[numCols];

      // Read plain text into the multi dimensional array
      for (int i = 0, sourceCounter = 0; i < numRows; i++)
      {
         for (int j = 0; j < numCols; j++, sourceCounter++)
         {
            // Filler field for the remaining indexes
            if(sourceCounter >= source.length())
               array[i][j] = -1;
            // Plug the plain text character into the array
            else
               array[i][j] = source[sourceCounter];
         }
      }

      // temp variable, 'crosses out' columns as they are used
      std::string passwordCrossOut = password;

      // Loops through and generates cipher text in order
      // of ascii values of the head of the columns
      for(int j = 0; j < numCols; j++)
      {
         int lowestIndex = -1;
         // Determine which column is next
         for (int index = 0; index < passwordCrossOut.length(); index++)
         {
            if (passwordCrossOut[index] != '\0' && (lowestIndex == -1 ||
                                                    passwordCrossOut[lowestIndex] > passwordCrossOut[index]))
               lowestIndex = index;
         }

         // Read row by row to create ciphertext
         for (int i = 0; i < numRows; i++)
         {
            destination += array[i][lowestIndex];
         }

         // Indicates the column has been used
         passwordCrossOut[lowestIndex] = '\0';
      }

      // free memory
      for (int i = 0; i < numRows; i++)
         delete [] array[i];
      delete [] array;

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
      // TODO - Add your code here
      //set rows and cols
      int numCols = password.length();
      int numRows = ceil(((float)source.length())/((float)password.length()));

      //set 2d array
      char ** array = new char*[numRows];
      for(int i =0; i < numRows; i++)
      {
         array[i] = new char[numCols];
      }

      //read in chars
      for(int j = 0, sourceCounter = 0; j < numCols; j++)
      {
         for(int i = 0; i < numRows; i++, sourceCounter++)
         {
            array[i][j] = source[sourceCounter];
         }
      }

      int * passwordIndex = new int[password.length()];
      std::string passwordCrossOut = password;


      //determine the password row combinations
      for(int i = 0; i < password.length(); i++)
      {
         int lowestIndex = -1;
         for(int index = 0; index < passwordCrossOut.length(); index++)
         {
            if(passwordCrossOut[index] != '\0' &&
               (lowestIndex == -1 ||
                passwordCrossOut[lowestIndex] > passwordCrossOut[index]))
            {
               lowestIndex = index;
            }
         }
         passwordIndex[lowestIndex] = i;
         passwordCrossOut[lowestIndex] = '\0';
      }

      //decrypt the messege
      for(int i = 0; i < numRows; i++)
      {
         for(int j = 0; j < numCols; j++)
         {
            if(array[i][passwordIndex[j]] != -1)
            {
               destination += array[i][passwordIndex[j]];
            }
         }
      }

      //clear memory
      for(int i =0; i < numRows; i++)
      {
         delete [] array[i];
      }
      delete [] array;
      delete [] passwordIndex;

      return destination;
   }
};

#endif // CIPHER2_H
