/***********************************************************************
* Program:
*    Assignment 25, Dem Bones
*    Brother Helfrich, CS124
* Author:
*    Brady Field
* Summary: 
*    This program will display the words to the song Dem Bones by
*    using the string class
*
*    Estimated:  1.0 hrs   
*    Actual:     0.2 hrs
*      It was easy! Way better then C-Strings!
************************************************************************/

#include <iostream>
#include <string>
using namespace std;

/********************************************************************
 * GENERATE SONG
 * This function will generate one long string that constitutes the
 * complete song "Dem Bones."  Note that the list of bones is provided
 * by the parameter list
 ********************************************************************/
string generateSong(string list[], int num)
{
   string output;

   for (int i = 0; i < 8; i++)
   {
      output += list[i] + " bone connected to the " + list[i + 1] + " bone\n";
   }

   return output;
}

/**********************************************************************
 * MAIN
 * In this program, MAIN is a driver program.  It will feed to generateSong()
 * the list of bones and get back the complete song as a string.  MAIN will
 * then display the song
 ***********************************************************************/
int main()
{
   string list[9] =
   {
      "toe",
      "foot",
      "leg",
      "knee",
      "hip",
      "back",
      "neck",
      "jaw",
      "head"
   };

   // generate the song
   string song = generateSong(list, 9);

   // display the results
   cout << song;
   
   return 0;
}
