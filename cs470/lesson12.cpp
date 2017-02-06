/***********************************************************************
* Program:
*    Lesson 12, Homographs
*    Brother Smithb, CS470
* Author:
*    Brady Field
* Summary: 
*    This program takes two file paths and determines if they point
*    to the same file or not
************************************************************************/

#include <iostream>
#include <string>
#include <unistd.h> // for cwd command
using namespace std;

bool isSamePath(string pathA, string pathB);
string normalizePath(string path);

/******************************************************
 * MAIN
 ******************************************************/
int main()
{
   string pathA;
   string pathB;
   
   // prompt for file paths
   cout << "Specify the first filename:  ";
   getline(cin, pathA);
   cout << "Specify the second filename: ";
   getline(cin, pathB);
   // resolve and output results
   cout << "The files are" << (isSamePath(pathA, pathB) ? " " : " NOT " ) 
        << "homographs\n";

   return 0;
}

/******************************************************
 * compares two normalized paths
 ******************************************************/
bool isSamePath(string pathA, string pathB)
{
   // normalize paths and compare
   return normalizePath(pathA) == normalizePath(pathB);
}

/******************************************************
 * takes a path and returns a normalized, absolute
 * path
 ******************************************************/
string normalizePath(string path)
{
   string newPath;
   
   // relative path to absolute if necessary
   if (path[0] != '/')
   {
      char cwd [256];
      getcwd(cwd, sizeof(cwd)); // current working directory
      path = (string)cwd + (string)"/" + path; // full path to requested file
   }

   // build new path by parsing and normalizing given path
   for (int i = 0, j = 0; i < path.length(); i++)
   {
      // test for special cases
      if (path[i] == '.' && path[i + 1] == '/') // current directory
      {
         i++; // skip over
      }
      else if (path[i] == '.' && path[i + 1] == '.' // parent directory
               && path[i + 2] == '/')
      {
         i += 2; // skip over
         
         // go up a directory
         if (j > 1) // only go up if parent folder exists
            j--;
         do
         {
            j--;
         }
         while (newPath[j] != '/');
         j++; // next writeable character
         newPath = newPath.substr(0, j); //erase end
      }
      else
      {
         newPath.insert(j,1, path[i]); // insert will size properly
         j++; // next writeable character
      }
   }
   
   return newPath;
}
