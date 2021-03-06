/***********************************************************************
* Program:
*    assignment 01, White List
*    Brother Smithb, cs470
* Author:
*    Brady Field
* Summary: 
*    Takes user input and sanitizes it for submission to a blog or forum 
************************************************************************/
#include <iostream>
#include <string>
#include <stack> // for tag ordering
using namespace std;

/***********************************************************************
* checks an input tag against a white list of allowed tags and
* return true if in white list and false if not   
************************************************************************/
bool isValidTag(const string & tag)
{
   string validclose[] = 
   {
    "</a>", "</abbr>","</acronym>", "</b>", "</blockquote>", "</cite>",
    "</code>", "</del>", "</em>", "</i>", "</q>", "</strike>", "</strong>", "end"
    };
    //check closing tags
    for (int i = 0; validclose[i] != "end"; i++)
    {
       if (tag == validclose[i])
       {
          return true;
       }
    }
    
   string valids[] = 
   {
    "<a>", "<abbr>", "<acronym>", "<b>", "<blockquote>", "<cite>",
    "<code>", "<del>", "<em>", "<i>", "<q>", "<strike>", "<strong>", "end"
    };
    
    // check opening tags
    for (int i = 0; valids[i] != "end"; i++)
    {
       if (tag == valids[i])
       {
          return true;
       }
    }

    // check open anchor tag
    if (tag.find("<a href=\"") != string::npos)
       return true;
    
    return false;
}

/***********************************************************************
* takes a string, scans through for tags, removes any not in white list,
* and checks the tags for proper opening and closing
************************************************************************/
string sanitize (string text) 
{ 
  
   string sanitized;
   string input;
   stack <string> opentags;
   // scan for invalid tags
   for (int i = 0; text[i];)
   {
      // get regular word
      if (text[i] != '<')
      {
         while ( text[i] != '<' && text[i])
         {
            sanitized += text[i];
            i++;
         }
      }
      else
      {
         // get tag
         input = "";
         while ( text[i] != '>' && text[i])
         {
            input += text[i];
            i++;
         }
         input += '>';
         i++;

         if (isValidTag(input) && input[1] != '/')
         {
            opentags.push(input);
            sanitized += input;
         }
         else if (isValidTag(input) && opentags.top().substr(1) == input.substr(2))
         {
            sanitized += input;
            opentags.pop();
         }
         // check anchor close 
         else if (input == "</a>" && opentags.top().find("<a href=\"") != string::npos )
         {
            sanitized += input;
            opentags.pop();
         }
         else
         {
            // clean
            sanitized += "&lt;";
            for (int j = 1; input[j] != '>'; j++)
            {
               sanitized += input[j];
            }
            sanitized += "&gt;";
         }
      }
   }
   // scan for and fix unclosed tags
   while (!opentags.empty())
   {
      sanitized += "</" + opentags.top().substr(1);
      opentags.pop();
   }
   
   return sanitized;
} 

/***********************************************************************
* prompts the user for input, sanitizes the input, and displays the
* result    
************************************************************************/
int main (void) 
{ 
   string input = "input";
   while (input != "quit")
   {
      cout << "> ";
      getline(cin, input);
      cout << "\t" << sanitize(input) << endl;
   }
   return 0;
}
