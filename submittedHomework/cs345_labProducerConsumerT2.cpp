/****************************************************************************
* Program:
*    Lab ProducerConsumerT2
*    Brother Jones, CS 345
* Author:
*    Brady Field
*
* Conclusions:
*    It was a fun lab.
*
* Summary:
*    I wanted to get rid of my count and use the semaphore
*    value to comput the tail, but I couldn't get it to work the same
************************************************************************
*
* Changes made to my code for the re-submission:
*   - added comments and a proper usage statement
*   - implemented semaphores
*   - used dynamic allocation
*****************************************************************************/

#include<pthread.h>
#include<iostream>
#include<stdlib.h>
#include<semaphore.h>
#include<iomanip>
using namespace std;

typedef int bufferItem;
#define BUFFER_SIZE 5
bufferItem buffer[BUFFER_SIZE];
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
sem_t full;
sem_t empty;
int index = 0;
int numItems = 0; // for computing tail

void *producer (void *param)
{
   bufferItem itemProduced;
   while(true)
   {
      usleep(rand() % 150000); // wait
      itemProduced = (rand() % 999 + 1); // generate num
     
      sem_wait(&full); // only insert if room
      pthread_mutex_lock(&mutex); // sync
        
      cout << setw(5) << itemProduced // display item
           << setw(7) << "P" << (long) param<< endl;
      buffer[index] = itemProduced;
      index = (index + 1) % BUFFER_SIZE; // next position with wrap
      numItems++; // keep count
      sem_post(&empty); // order up for consumer
      pthread_mutex_unlock(&mutex); // exit critical section
   }
   pthread_exit(NULL);
}

void *consumer (void *param)
{
   bufferItem consumedItem;

   while(true)
   {
      usleep(rand() % 150000); // wait
     
      sem_wait(&empty); // only consume if buffer not empty
      pthread_mutex_lock(&mutex); // sync
      // display item
      cout << setw(22) << buffer[(index + BUFFER_SIZE - numItems) % BUFFER_SIZE]
           << setw(7) << "C" << (long) param << endl;
      numItems--; // count
      sem_post(&full); // more room to produce
      pthread_mutex_unlock(&mutex); // exit critical section
   }
   pthread_exit(NULL);
}


int main(int argc, char** argv)
{
   if(argc != 4)
   {
      cout << "\nInvalid input.\n\n";
      cout << "usage: " << argv[0] << "[seconds to run][num producer threads][num consumer threads]\n";
      cout << "e.g. " << argv[0] << "4 2 2\n";
      return 0;
   }

   // initialize semaphores and threads
   sem_init(&full, 0, BUFFER_SIZE);
   sem_init(&empty, 0 , 0);
   int secondsToSleep = atoi(argv[1]) * 1000000; // time in seconds
   int producerThreads = atoi(argv[2]);
   int consumerThreads = atoi(argv[3]);
   pthread_t * producerThreadsArray = new pthread_t[producerThreads];
   pthread_t * consumerThreadsArray = new pthread_t[consumerThreads];
   int ct;

   // launch threads
   for(long i = 0; i < producerThreads; i++)
   {
      ct = pthread_create(&producerThreadsArray[i], NULL, producer, (void *)(i + 1));

      if(ct) // error launching producers
      {
         cout << "THERE WAS AN ERROR. Return code from pthread_create is: "
              << ct << endl;
         exit(-1);
      }
   }

   for(long i = 0; i < consumerThreads; i++)
   {
      ct = pthread_create(&consumerThreadsArray[i], NULL, consumer, (void*) (i + 1));

      if(ct) // error launching consumers
      {
         cout << "THERE WAS AN ERROR. Return code from pthread_create is: "
              << ct << endl;
         exit(-1);
      }
   }
   cout << "Produced  by P#  Consumed  by C#\n========  =====  ========  =====\n";

   usleep(secondsToSleep); // let the program run for time

   // cleanup

   // cancel threads
   for (long i = 0; i < producerThreads; i++)
   {
      pthread_cancel(producerThreadsArray[i]);
   }
   for (long i = 0; i < consumerThreads; i++)
   {
      pthread_cancel(consumerThreadsArray[i]);
   }

   // clean memory
   delete [] producerThreadsArray;
   delete [] consumerThreadsArray;
 
   return 0;
}
