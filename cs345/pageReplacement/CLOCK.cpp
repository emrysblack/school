/***********************************************************************
* Program:
*    Lab PageReplacementT2
*    Brother Jones, CS 345
* Author:
*    Brady Field
* Summary:
*    Clock page replacement
************************************************************************/
/*
**====================================================================**
* The following will be filled out for the second submission.  For the
* first submission, you may leave it in your code or delete it.
*
* The second submission should be submitted to labPageReplacementT2.
* (Which means the third line of the headers in CLOCK.cpp, FIFO.cpp and
* LRU.cpp files need to have a "T2" added onto the name of the lab.)
**====================================================================**
*
* Changes made to my code for the re-submission:
*   - added helpful comments
*   - fixed a bug caused by failure to set bits for new pages
************************************************************************/

#include "vmalgorithm.h"

/**************************************************************************
 * Function:
 *    void CLOCK::execute() - Executes the CLOCK page replacement algorithm
 * Inherited Variables and Methods:
 *    int NUM_FRAMES: How many frames there are in 'memory'. (eg. 4)
 *    int frames[NUM_FRAMES]: The array that contains the pages resident
 *          in memory.  Use this array for the pages in memory.  
 *          See Also: NUM_FRAMES
 *    int hit(int page): Function that scans the 'frames[]' array, searching
 *          for 'page'.  If 'page' is found, it will return the index of 
 *          the 'frames[]' array.  If the page is not found, the function
 *          returns '-1'.
 *    int myPageFactory->getPage(): Returns the next page the psuedo-program 
 *          requests.  When there are no more pages to return, this function
 *          returns a -1.
 *    void display(int page, int frames[], bool fault): Function to display
 *          the information to stdout.  The parameter 'page' is the current
 *          page (the one returned from myPageFactory->getPage()), 'frames[]'
 *          is the array of the current resident set, and when 'fault' is 
 *          true, the display function will indicate it to the screen. 
 *          This function must be called for every page that is accessed.
 *************************************************************************/ 
void CLOCK::execute()
{
   int position = 0; // keeps track of fifo position
   bool bits[NUM_FRAMES];
   int num;
   for (int  i = 0; i < NUM_FRAMES; i++)
   {
      bits[i] = false;
   }
     // Keep track of faults
  bool fault;

  // Holds the accessed page
  int page;

  while ( (page = myPageFactory->getPage()) != -1 )
  {
     num = hit(page);
     fault = num == -1; // assume false until we have a fault.
     if ( fault )
     {
        while(bits[position])
        {
           //std::cerr << "clear\n";
           bits[position] = false;
           position = (position + 1) % NUM_FRAMES;
        }
        // if the page was not found, replace next page.        
        frames[position] = page;
        bits[position] = true; // set bit for new page
        position = (position + 1) % NUM_FRAMES;
     }
     else
     {
        bits[num] = true;
     }
     
     display(page, frames, fault);
  }
}

