/***********************************************************************
* Program:
*    Lab UnixShellT2, Operating Systems 
*    Brother Jones, CS 345
* Author:
*    Brady Field
* Summary:
*    This program is a shell with a history feature built in
*    Thank you to Justin, Mackenzie, and super group for helping me
*    to work out the bugs and giving me pointers
************************************************************************
* no changes were made
************************************************************************/
#include <iostream>
#include <iomanip>
#include <signal.h>
#include <cstring>
#include <unistd.h>
#include <wait.h>
#include <sstream>
#include <cstdlib>
#include <stdio.h>

#define BUFFER_SIZE 50

/* 80 chars per line, per command, should be enough. */
#define MAX_LINE 80
/* The size of the history buffer */
#define HIST_SIZE 10
/* Maximum number of commands until count rolls over. */
#define MAX_NUM_CMDS 1000

using namespace std;

// A global array of strings and a count of the number of valid strings in it.
string commands[HIST_SIZE];
int goodStringCount = 0;
bool executeProcess(char *args[], int background);
void displayHistory( );
static char msg4handler2print[BUFFER_SIZE];
struct sigaction handler;

void handle_SIGQUIT(int junk)
{
   int lenOfMsg;

   lenOfMsg = strnlen(msg4handler2print, BUFFER_SIZE);
   write(STDOUT_FILENO, msg4handler2print, lenOfMsg);
   displayHistory();

   return;
}

void parseInput(char inputBuffer[], char *args[], int & argc, int length, int &background )
{    
    int start;  /* index where beginning of next command parameter is */
   int ct;     /* index of where to place the next parameter into args[] */
    
   ct = 0;
    
    start = -1;            /* Used as a flag to indicate that we are looking
                           * for the start of the command or an argument if
                           * it is a -1, or stores the starting position of
                           * the command or argument to be put in args[].
                           */
    
    /* examine every character in the inputBuffer */
   for (int i = 0; i < length; i++)
   {    
      switch (inputBuffer[i])
      {
         case ' ':
                if(i == 1 && length > 2 && inputBuffer[0] == 'r')
                    break;
            
         case '\t' :               /* argument separators */
            if(start != -1)        /* found the end of the command or arg */
            {
               args[ct] = &inputBuffer[start]; /* set up pointer in args[] */
               ct++;
            }
            inputBuffer[i] = '\0'; /* add a null char; make a C string */
            start = -1;
            break;

         case '\n':                 /* should be the final char examined */
            if (start != -1)        /* if in the command or an argument */
            {
               args[ct] = &inputBuffer[start]; /* set up pointer in args[] */ 
               ct++;
            }
            inputBuffer[i] = '\0';
            args[ct] = NULL; /* no more arguments to this command */
            break;
                
         default :             /* some other character */
            if (start == -1 && inputBuffer[i] != '&')
               start = i;      /* starting position of the command or arg */
            if (inputBuffer[i] == '&')
            {
               background  = 1;
               inputBuffer[i] = '\0';
            }
      }  /* end of switch */
   }  /* end of for loop looking at every character */
   args[ct] = NULL; /* just in case the input line was > 80 */
    argc = ct;
}

int setup(char inputBuffer[], char *args[], int & argc, int &background)
{
   int length; /* # of characters in the command line */
   int i;      /* loop index for accessing inputBuffer array */
    
   /* read what the user enters on the command line */
   length = read(STDIN_FILENO, inputBuffer, MAX_LINE);  
    
   if (length == 0)
      exit(0);            /* ^d was entered, end of user command stream */
   if (length < 0)
   {
      perror("error reading the command");
      exit(-1);           /* terminate with error code of -1 */
   }

   /* examine every character in the inputBuffer */
   parseInput(inputBuffer, args, argc, length, background );
    
    return length;
} 
      
/*************************************************************************
* add2History() adds a command to the history buffer and increments the
* number of commands that have been entered up to a maximum count.  If the
* history buffer is full, the oldest command is overwritten.    
**************************************************************************/
void add2History (string input, char* args[], int argc, int &background)
{
   commands[goodStringCount % HIST_SIZE] = input;
    //cout << "This is input: " << input << endl;
    for(int i = 1; i < argc; i++)
    {
        commands[goodStringCount % HIST_SIZE] += " " + (string) args[i];
    }
    
    if(background == 1)
        commands[goodStringCount % HIST_SIZE] += '&';
    
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
* the preceding cases, the return value is set to true.  If no matching
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
            cout << "Command not found\n";
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
   
   cout << "No matching command in history\n";   
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
   
    //imported stuff
   int background;             /* equals 1 if a command is followed by '&' */
   char *args[MAX_LINE/2];   /* command line (of 80) has max of 40 arguments */
    int argc = 0;
    
   sigemptyset (&handler.sa_mask);
   handler.sa_flags = SA_RESTART;

   handler.sa_handler = handle_SIGQUIT;

   sigaction(SIGQUIT, &handler,NULL);
      
   /*set up the message we want printed when USR1 is seen */
   strncpy( msg4handler2print, "\n", BUFFER_SIZE );
    
   while (1)
   {
      length = -1;
      goodCmd = true;

      while (length < 0)
      {
            background = 0;
         cout << " COMMAND-> ";
         cout.flush();   
         length = setup(inputBuffer, args, argc, background);
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
      /*else if (inputBuffer[0] == '.' && inputBuffer[1] == '\0')
      {
         displayHistory( );
         goodCmd = false;
      }*/
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
         if (inputBuffer[1] == '\0' )
            {
                inputBuffer[2] = '\0';
            }

         goodCmd = findCommnandInHistory(inputBuffer[2], tmpString);

         if ( goodCmd )
         {
                //parseInput expects a new line at the end of the string.
                tmpString += '\n';
            strncpy (inputBuffer, tmpString.c_str(), MAX_LINE);
                parseInput(inputBuffer, args, argc, tmpString.length(), background );
         }
         else
         {
            cout.flush();   
         }
         
      }

      if ( goodCmd )
      {
            executeProcess(args, background);
            add2History( (string) inputBuffer, args, argc, background );
      }

   // end:  while(1)
   }

// end of main()
}

bool executeProcess(char *args[], int background)
{
    pid_t pid = fork();

    if (pid < 0)
    {
        fprintf(stderr, "Fork Failed");
        exit(1);
    }
    else if (pid == 0)
    {
        if (execvp(args[0], args) != 0)
        {
            printf("command not found\n");
            exit(1);
        }
    }
        
    if (background != 1)
    {
        waitpid(pid, NULL, 0);
    }
    
    return true;
}
