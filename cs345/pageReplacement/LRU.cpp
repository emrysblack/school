/***********************************************************************
* Program:
*    Lab PageReplacementT2
*    Brother Jones, CS 345
* Author:
*    Brady Field
* Summary:
*    LRU page replacement
************************************************************************/

#include "vmalgorithm.h"

/**************************************************************************
 * Function:
 *    void LRU::execute() - Executes the LRU page replacement algorithm
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
void LRU::execute()
{
   // keeps track of usage for each frame
   int positions[NUM_FRAMES];
   int position = 0;
   // fill it
   for (int i = 0; i < NUM_FRAMES; i++)
   {
      positions[i] = NUM_FRAMES;
   }
     // Keep track of faults
  bool fault;
  // Holds the accessed page
  int page;

  while ( (page = myPageFactory->getPage()) != -1 )
  {
     position = hit(page); // assume false until we have a fault.
     fault = position == -1;
     
     if ( fault )
     {
        // find next position for replacement
        position = 0;
        for(int i = 0; i < NUM_FRAMES; i++)
        {
           if (positions[i] > positions[position])
           {
              position = i;
           }
        }
        // if the page was not found, replace next page.    
        frames[position] = page;
     }
     
     // age all elements
     for (int i = 0; i < NUM_FRAMES; i++)
   {
      positions[i]++;
   }
   // reset most recently used
     positions[position] = 1;
     display(page, frames, fault);
  }
}

