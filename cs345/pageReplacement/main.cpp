#include "vmalgorithm.h"

int main(int argc, char* argv[])
{
   // The number of frames in our memory
   int NUM_FRAMES = 4;
    
   // Check the command-line options
   if (argc < 4)
   {
      cout << "Usage\n\n";
      cout << "./vmalgorithm FRAME_SIZE LRU|CLOCK|FIFO|RANDOM progname.vm\n\n";
      cout << "where: \n";
      cout << "\tFRAME_SIZE\tis the number of frames (eg 4)\n";
      cout << "\tLRU\t\tuse the Least Recently Used replacement algorithm\n";
      cout << "\tCLOCK\t\tuse the Clock replacement algorithm\n";
      cout << "\tFIFO\t\tuse the First In First Out replacement algorithm\n";
      cout << "\tRANDOM\t\tuse the Random replacement algorithm\n";
      cout << "\tprogname.vm\tis the name of the file to 'run'\n" << endl;
      return -1;
   }

   NUM_FRAMES = atoi(argv[1]);
   if (NUM_FRAMES < 1)
   {
      cout << "The first parameter, FRAME_SIZE should be a number greater than 1.\n\n";
      return -1;
   }

   PageFactory* myPageFactory = new PageFactory(argv[3]);

   if (strcmp(argv[2], "LRU") == 0)
   {
      LRU myLRUAlgorithm(myPageFactory, NUM_FRAMES);
      myLRUAlgorithm.execute();
   }
   else if (strcmp(argv[2], "CLOCK") == 0)
   {
      CLOCK myCLOCK(myPageFactory, NUM_FRAMES);
      myCLOCK.execute();
   }
   else if (strcmp(argv[2], "FIFO") == 0)
   {
      FIFO myFIFO(myPageFactory, NUM_FRAMES);
      myFIFO.execute();
   }
   else if (strcmp(argv[2], "RANDOM") == 0)
   {
      RANDOM myRANDOM(myPageFactory, NUM_FRAMES);
      myRANDOM.execute();
   }
   else
   {
      cout << "I don't understand the " << argv[2] << " page replacement "
         << "algorithm.\nValid options are: LRU, CLOCK, FIFO, RANDOM (note:"
         << "parameter is\ncase sensitive." << endl;
      return -1;
   }
   return 0;
}
