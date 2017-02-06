#ifndef _VMALGORITHM
#define _VMALGORITHM

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <stdlib.h>


// Constants
const int PROGRAM_LENGTH = 20;

using namespace std;

class PageFactory
{
   private:
      int pages[PROGRAM_LENGTH];
      int curPage;
   public:
      PageFactory(char* filename)
      {
         curPage = 0;
         ifstream pagesFile(filename);

         if (pagesFile.bad())
         {
            cerr << "Error opening " << filename << ".  Check to make sure "
               << "the filename is correct." << endl;
            exit(-1);
         }

         for (int i = 0; i < PROGRAM_LENGTH; ++i)
         {
             pagesFile >> pages[i];
         }
         pagesFile.close();
      }

      int getPage()
      {
         if (curPage >= PROGRAM_LENGTH)
         {
            return -1;  // -1 means no more pages
         }
         else
         {
            return pages[curPage++];
         }
      }

      void resetPage()
      {
         curPage = 0;
      }
};

class VMManager
{
   protected:
     PageFactory* myPageFactory;
     int* frames;
     int NUM_FRAMES;

     int hit(int page)
     {
        for (int i = 0; i < NUM_FRAMES; ++i)
        {
           if (frames[i] == page)
           {
              return i;
           }
        }
        return -1; // -1 means that page wasn't found.
     }
     
   public:
      void display(int page, int frames[], bool fault)
      {
         cout << "     +";
         for (int i = 0; i < NUM_FRAMES; ++i)
         {
            cout << "---+";            
         }
         cout << "\n" << setw(3) << page << "  | ";
         for (int i = 0; i < NUM_FRAMES; ++i)
         {
            cout << frames[i] << " | ";
         }
         if (fault == true)
         {
            cout << " Fault";
         }
         cout << "\n     +";
         for (int i = 0; i < NUM_FRAMES; ++i)
         {
            cout << "---+";            
         }
         cout << endl;
      } 
};

class LRU: public VMManager
{
   public:
     LRU(PageFactory* thePageFactory, int Num_Frames)
     {
        myPageFactory = thePageFactory;
        NUM_FRAMES = Num_Frames;

        frames = new int[NUM_FRAMES];

        // initialize our frames to 0s
        for (int i = 0; i < NUM_FRAMES; ++i)
        {
           frames[i] = 0;
        }
     }

     void execute();
};

class RANDOM: public VMManager
{
   public:
     RANDOM(PageFactory* thePageFactory, int Num_Frames)
     {
        myPageFactory = thePageFactory;
        NUM_FRAMES = Num_Frames;

        frames = new int[NUM_FRAMES];

        // initialize our frames to 0s
        for (int i = 0; i < NUM_FRAMES; ++i)
        {
           frames[i] = 0;
        }
     }

     void execute();
};


class FIFO: public VMManager
{
   public:
     FIFO(PageFactory* thePageFactory, int Num_Frames)
     {
        myPageFactory = thePageFactory;
        NUM_FRAMES = Num_Frames;

        frames = new int[NUM_FRAMES];

        // initialize our frames to 0s
        for (int i = 0; i < NUM_FRAMES; ++i)
        {
           frames[i] = 0;
        }
     }

     void execute();
};

class CLOCK: public VMManager
{
   public:
     CLOCK(PageFactory* thePageFactory, int Num_Frames)
     {
        myPageFactory = thePageFactory;
        NUM_FRAMES = Num_Frames;

        frames = new int[NUM_FRAMES];

        // initialize our frames to 0s
        for (int i = 0; i < NUM_FRAMES; ++i)
        {
           frames[i] = 0;
        }
     }

     void execute();
};

#endif
