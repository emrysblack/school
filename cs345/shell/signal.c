/**************************************************************************
*
* This code is a modified version of sample code found in "Operating
* Systems Concepts," Seventh Edition, by Silberschatz, Galvin and Gagne
* page 124.  The sample code in the book catches a ctrl-c.  This catches
* a SIGUSR1.  Similar code should be placed in your Unix shell code.
*
* To see this code work, compile it and run it.  In another window, send
* a USR1 signal using the kill command to the running program.
*     kill -USR1 process_pid
*
* You may find the 'process_pid' of the process to send the signal to
* using the ps command.
*
***************************************************************************/
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 50

static char msg4handler2print[BUFFER_SIZE];

/* the signal handler function */
/*   note: If compiling this with gcc the definition may be:
 *             void handle_SIGUSR1()
 *         For g++ this works:   void handle_SIGUSR1( int )
 *         Both gcc and g++ like:   void handle_SIGUSR1( int junk )
 */
void handle_SIGUSR1( int junk )
{
   int lenOfMsg;
   lenOfMsg = strnlen(msg4handler2print, BUFFER_SIZE);
   write(STDOUT_FILENO, msg4handler2print, lenOfMsg);
   /* this handler could exit, but typically would return so that you
    * continue execution of the program after handling the signal. */
   //exit(0);
   return; 
}

int main(int argc, char *argv[]) 
{
   /* set up the signal handler */
   struct sigaction handler;
   handler.sa_handler = handle_SIGUSR1;   /* function the handler will call */
   sigaction(SIGUSR1, &handler, NULL);    /* handler to call for USR1 signal */

   /* set up the message we want printed when USR1 is seen */
   strncpy( msg4handler2print, "Caught signal USR1\n", BUFFER_SIZE );

   /* Execute an infinite loop.
    * A SIGUSR1 will send us to the handler routine which is
    *    handle_SIGUSR1()
    */
   while (1)
   {
      sleep(3);
      printf("Waiting for a signal ...\n");
   }

   return 0;
}

