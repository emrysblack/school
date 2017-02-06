/***********************************************************************
* Program:
*    Lab ShellHistory  
*    Brother Jones, CS 345
* Author:
*    Your Name
* Summary:
*    This program implements the history feature of a shell program.  It
*    prompts the user to input commands (a string of text as far as this
*    program is concerned) with the prompt: " COMMAND-> "
*
*    The program displays the last ten commands entered by the user when
*    a period (.) is entered as the only input on a command line.
*
*    An example execution:
*
*      COMMAND-> ls
*        command executed: ls
*       COMMAND-> date
*        command executed: date
*       COMMAND-> ls -l
*        command executed: ls -l
*       COMMAND-> who
*        command executed: who
*       COMMAND-> who -i
*        command executed: who -i
*       COMMAND-> sleep 3
*        command executed: sleep 3
*       COMMAND-> who -d
*        command executed: who -d
*       COMMAND-> .
*         0  ls
*         1  date
*         2  ls -l
*         3  who
*         4  who -i
*         5  sleep 3
*         6  who -d
*       COMMAND->
*      
*    This code allows for an 'r' command or 'r x' command to find commands
*    in the history and re-execute them.
*
*    The history feature is implemented by using a circular buffer
*    which stores the user keyboard input (commands).
*
*    This program uses a read system call to get user keyboard input.  It 
*    also exits when the user enters 'exit' to the program.
************************************************************************/

#include <iostream>
#include <iomanip>
#include <signal.h>
#include <cstring>
#include <unistd.h>
#include <wait.h>
#include <sstream>
#include <cstdlib>

/* 80 chars per line, per command, should be enough. */
#define MAX_LINE 81
/* The size of the history buffer */
#define HIST_SIZE 10
/* Maximum number of commands until count rolls over. */
#define MAX_NUM_CMDS 1000

using namespace std;

// A global array of strings and a count of the number of valid strings in it.
string commands[HIST_SIZE];
int goodStringCount = 0;
      
/*************************************************************************
* add2History() adds a command to the history buffer and increments the
* number of commands that have been entered up to a maximum count.  If the
* history buffer is full, the oldest command is overwritten.    
**************************************************************************/
void add2History (string input)
{
   commands[goodStringCount % HIST_SIZE] = input;
   goodStringCount++;  

   // Roll over the count if it hits the maximum allowed for printing 
   if ( goodStringCount >= MAX_NUM_CMDS )
      goodStringCount = HIST_SIZE;    /* Leave a full buffer of commands */
}
      
/*************************************************************************
* findCommandInHistory() searches backward for the first command that
* begins with a particular character (char c) in the history buffer.
* If a string is found that begins with the character, the string is
* passed back to the calling function.  If the character being looked
* for is a NULL then the most recent command is returned.  In both of
* the preceeding cases, the return value is set to true.  If no matching
* string is found, the return value is set to false.
**************************************************************************/
bool findCommnandInHistory(char c, string& stringFound)
{
   int temp = goodStringCount;
   stringFound = "";

   // If the character being looked for is a null, then return the most
   // recent command, if there was one.
   if (c == '\0')
   {
      if (goodStringCount)
      {
         stringFound = commands[ (goodStringCount - 1) % HIST_SIZE ];
         return true;
      }
      else
      {
         return false; 
      }
   }
   
   // Look back through the history for a command staring with the letter
   // given in the first argument to this function.
   for (temp; temp >= 0 && temp != temp - HIST_SIZE; --temp)
   {            
      if (commands[temp % HIST_SIZE][0] == c)
      {
         stringFound = commands[temp % HIST_SIZE];
         return true;
      }
   }
         
   return false;
}


/*************************************************************************
* Display the contents of the history buffer of commands with the number
* of the command listed on the beginning of the line.
**************************************************************************/
void displayHistory( )
{
   int start;
   
   if (goodStringCount > HIST_SIZE)
      start = goodStringCount - HIST_SIZE;
   else
      start = 0;

   for (int i = start; i < goodStringCount; ++i)
   {            
      cout << " " << setw(3) << i << "  " << commands[i % HIST_SIZE] << endl;
   }
   
   return;
}


/*************************************************************************
* This program displays a prompt for the user to enter a command.  If a '.'
* is the only thing entered a history of the last commands entered is
* printed.
**************************************************************************/
int main ()
{
   string tmpString;
   int length = -1;
   bool goodCmd = true;
   char inputBuffer[MAX_LINE]; /* buffer to hold the command entered */
   
   while (1)
   {
      length = -1;
      goodCmd = true;

      while (length < 0)
      {
         cout << " COMMAND-> ";
         cout.flush();   
         length = read(STDIN_FILENO, inputBuffer, MAX_LINE);
         // removes the newline and makes this a c-string 
         inputBuffer[length - 1] = '\0';
      }

      if ( length == 1 )
      {
         // If the user just entered a newline, then the length of the
         // input will be 1 and we just want to give the prompt again.
         // (Ignoring the newline input.)
         goodCmd = false;
      }
      else if (inputBuffer[0] == '.' && inputBuffer[1] == '\0')
      {
         displayHistory( );
         goodCmd = false;
      }
      else if ( length == 0 || (! strncmp( inputBuffer, "exit", MAX_LINE )) )
      {
         // End of file or exit command given
         exit(0);
      }
      else if (inputBuffer[0] == 'r' && 
                     (inputBuffer[1] == '\0' || inputBuffer[1] == ' ') )
      {         
         // If an 'r' command was given and a matching command is found in the
         // history, then put the command to be repeated in the buffer.
         // If an 'r' was given with no argument the most recent command
         // should be executed.  This is indicated with a null.
         if (inputBuffer[1] == '\0') inputBuffer[2] = '\0';

         goodCmd = findCommnandInHistory(inputBuffer[2], tmpString);

         if ( goodCmd )
         { 
            strncpy (inputBuffer, tmpString.c_str(), MAX_LINE);
         }
         else
         {
            cout << "Command not found\n";
            cout.flush();   
         }
         
      }

      if ( goodCmd )
      {
         add2History( (string) inputBuffer );
         cout << "  command executed: " << inputBuffer << endl;
      }

   // end:  while(1)
   }

// end of main()
}


