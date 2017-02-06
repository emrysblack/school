/***********************************************************************
* Program:
*    Lab Threads - doIOjobs
*    Brother Jones, CS 345
* Author:
*    Brother Jones with pieces of code from BYU-Idaho Students 
* Summary:
*    This program simulates completing a bunch of IO jobs that need to
*    be done.  Instead of doing actual IO, sleeps are done instead.
*    This program is given one argument that tells how many threads to 
*    use in getting the IO jobs done.
************************************************************************/

#include <pthread.h>
#include <iostream>
#include <iomanip>
#include <cstdlib>
using namespace std;

// The maximum number of IO jobs to be done.
const int MAX_JOBS = 1000;
// Initialize an array that provides the simulated IO time (sleep time)
// for the various IO jobs.
const int SIMULATED_IO[MAX_JOBS] = 
      { 2975927, 1219003,    3781, 1530320,  482044,    8627,  768811, 2384440,
         100905, 1216700, 1867600,   80830,  414900, 2634000,     258, 1536298,
         818800, 1993134,  535600, 1277433,   26992, 1400855,   19306, 2221900,
         974122,     780,    3579,  588500,    7220,   22578,       0,    3333,
        1974927, 1219003,    3781, 1530320,  482044,    8627,  768811, 2384440,
         100905, 1216700, 1867600,   80830,  414900, 2634000,     258, 1536298,
         818800, 1993134,  535600, 1277433,   26992, 1400855,   19306, 2221900,
         974122,     780,    3579,  588500,    7220,   22578,       0 };

/***********************************************************************
* struct ThreadJobs
*  This data structure holds the start index and increment that are passed
*  to a thread to tell the thread which IO jobs to work on.
************************************************************************/
struct ThreadJobs
{
   int startAt;
   int increment;
};


// Each thread is started in the doIOjobs function to "do some IO jobs"
// (actually 'sleep' jobs) for a specified number of microseconds. Each
// thread is passed a structure that tells which 'job' to start on and an
// increment value that tells where to pick up the next 'job.'
// A pointer to the structure is passed to the doIOjobs function.
void* doIOjobs(void *whichJobsToDo);

/***********************************************************************
*    This program simulates completing a bunch of IO jobs that need to
*    be done.  Instead of doing actual IO, sleeps are done instead.
*    The IO jobs are done by a user specified number of threads.
************************************************************************/
int main(int numArgs, char* args[])
{
   //Check for one argument that is the number of threads to run
   if (numArgs != 2)
   {
      cerr << "Usage: " << args[0] << " <# threads>" << endl;
      exit(1);
   }

   //Convert the argument from a string to a number
   int numThreads = atoi(args[1]);
   //Check that the number of threads asked for does not exceed the maximum
   //allowed for this program
   if (numThreads > MAX_JOBS || numThreads < 1)
   {
      cerr << args[0] << ": Number of threads allowed is 1 to " 
           << MAX_JOBS << endl;
      cerr << "            or, the maximum threads allowed on the system for one process.\n";
      exit(2);
   }

   // Create an array to hold all the thread IDs
   pthread_t* threads = new pthread_t[MAX_JOBS];
   int tidIndex = 0;  //index into the array

   //The number of threads asked for is the increment given to each thread.
   // If there are to be 10 threads, the first thread executes jobs 0, 10, 20
   // 30, ..., the second thread executes jobs 1, 11, 21, 31, ... and so on.
   // Each thread will be responsible to check that it doesn't try to execute
   // non-existent jobs.

   //Create threads telling them which IO jobs to do.  Each thread is
   // passed a pointer to a ThreadsJobs structure.
   for (int i = 0; i < numThreads; i++)
   {
      ThreadJobs* pThreadJobs = new ThreadJobs;
      pThreadJobs->startAt = i;
      pThreadJobs->increment = numThreads;
      pthread_create(&threads[tidIndex], NULL, doIOjobs, (void*)pThreadJobs);
      tidIndex++;
   }
   
   // Wait for all the threads to finish
   for (int i = 0; i < tidIndex; i++)
   {
      pthread_join(threads[i],NULL);
   }
   
   //cleanup
   delete [] threads;
}


/***********************************************************************
* Function Name: doIOjobs
*
* Summary: This function completes IO jobs (sleep jobs) that are 
*          specified in a global array called SIMULATE_IO[].
*
* Input: This function is passed a pointer to a structure that tells
*        which 'job' to start on in the global array and an increment
*        value that tells where to pick up the next 'job.'
*
* Output: Completes the IO (sleep) jobs and prints a line of output to
*         the console.
************************************************************************/
void* doIOjobs(void *whichJobsToDo)
{
   // Put startAt and increment values into local variables
   int startJob = ((ThreadJobs*) whichJobsToDo)->startAt;
   int incrBy = ((ThreadJobs*) whichJobsToDo)->increment;

   // Do the jobs
   for (int job = startJob; job < MAX_JOBS; job += incrBy)
   {
      usleep(SIMULATED_IO[job]);
      cout << "Finished job " << job << " with " << SIMULATED_IO[job] / 1e6
           << " seconds of IO" << endl;
   }
   
   delete (ThreadJobs*) whichJobsToDo;

   pthread_exit(NULL);
}

