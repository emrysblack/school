/***********************************************************************
* Program:
*    Lab ProducerConsumer
*    Brother Jones, CS 345
* Author:
*    Ryan Hildreth
*
* Conclusions:
*    The semaphores worked as expected, allowing the correct number of
*    items to be added to the buffer and delaying attempts to add or 
*    remove items if the action is impossible.
*
* Summary:
*    This program creates a number of producer and consumer threads
*    to add and remove items from a global buffer. Semaphores are
*    used to ensure that no more than the specified number of items
*    are within the thread at any time.
************************************************************************/
#include <iostream>
#include <unistd.h>
#include <iomanip>
#include "semaphore.h"
#include "stdlib.h"
#include "pthread.h"
using namespace std;

typedef int bufferItem;
#define BUFFER_SIZE 5

bufferItem data[BUFFER_SIZE];

/*************************************************************
* The Buffer class handles all interactions with the global
* buffer data array
*************************************************************/
class Buffer
{
   private:
   
      int read;
      int write;
      sem_t full;
      sem_t empty;

   public: 
   
      /*************************************************************
      * Default constructor initializes semaphores and values
      *************************************************************/
      Buffer()
      {
         read = 0;
         write = 0;
         if (sem_init(&full, 0, BUFFER_SIZE))
         {
            cout << "ERROR: Cannot initialize semaphore.\n";
            exit(1);
         }
         if (sem_init(&empty, 0, 0))
         {
            cout << "ERROR: Cannot initialize semaphore.\n";
            exit(1);
         }
      }
      
      /*************************************************************
      * Destructor ensures semaphores are destroyed on exit
      *************************************************************/
      ~Buffer()
      {
         sem_destroy(&full);
         sem_destroy(&empty);
      }
      
      /*************************************************************
      * Get a value from the global buffer
      *************************************************************/
      int get(int destination)
      {
         /* Wait if empty, then get oldest item from buffer */
         sem_wait(&empty);
         int old_read = read;
         read = (read + 1) % BUFFER_SIZE;
         
         /* Display value retrieved */
         cout << setw(21) << data[old_read] 
              << setw(6) << "C" << destination << endl;  
         sem_post(&full);
         return data[old_read];
      }
      
      /*************************************************************
      * Add a value to the global buffer
      *************************************************************/
      void add(int value, int source)
      {
         /* Wait if full, then add new item to buffer */
         sem_wait(&full);
         int old_write = write;
         write = (write + 1) % BUFFER_SIZE;
         data[old_write] = value;
         
         /* Display value added */
         cout << setw(5) << value 
              << setw(6) << "P" << source << endl;
         sem_post(&empty);
      }
} 
buffer;

/*************************************************************
* Function for producer threads
*************************************************************/
void *producer (void *param)
{
   bufferItem itemProduced;
   while (1)
   {
      /* sleep for a random period of time */
      usleep(rand() % 150000);
      
      /* generate a random number */
      itemProduced = (rand() % 1000 );
      
      /* Send value to global buffer */
      buffer.add(itemProduced, *((int *) param));
   }
}

/*************************************************************
* Function for consumer threads
*************************************************************/
void *consumer(void *param)
{
   bufferItem consumedItem;
   while (1)
   {
      /* sleep for a random period of time */
      usleep(rand() % 150000);
      
      /* Get value from global buffer */
      consumedItem = buffer.get(*((int *) param));
   }
}

/*************************************************************
* The main function creates and starts the required threads,
* waits for a specified time, then ends all threads.
*************************************************************/
int main(int argc, char* argv[])
{
   if (argc != 4)
   {
      cout << "ERROR: Expected 3 arguments, found " << (argc - 1) << ".\n";
      cout << "USAGE: " << argv[0]
           << " <Wait Time> <#Producers> <#Consumers>\n";
      return 1;
   }

   int sleep_length = atoi(argv[1]);
   int numProducers = atoi(argv[2]);
   int numConsumers = atoi(argv[3]);
   
   if (!sleep_length || !numProducers || !numConsumers)
   {
      cout << "ERROR: Invalid arguments.\n";
      exit(1);
   }

   /* Thread declarations */
   pthread_t producerThreads[numProducers];
   pthread_t consumerThreads[numConsumers];
   
   /* Thread IDs */ 
   int* threadID[numProducers + numConsumers];
   
   int nextThread = 0;
   
   /* Display table header */
   cout << "Produced by P# Consumed by C#\n" <<
           "======== ===== ======== =====\n";
   
   /* Create producer threads */
   for (int i = 0; i < numProducers; i++)
   {
      threadID[i] = new int;
      *threadID[i] = i + 1;
      pthread_create( &producerThreads[nextThread++], 
         NULL, producer, (void*)threadID[i]);
   }
   
   nextThread = 0;
   
   /* Create consumer threads */
   for (int i = 0; i < numConsumers; i++)
   {
      threadID[i + numProducers] = new int;
      *threadID[i + numProducers] = i + 1;
      pthread_create( &consumerThreads[nextThread++ ], 
         NULL, consumer, (void*)threadID[i + numProducers]);
   }

   /* Start consumer threads */
   for (int i = 0; i < numConsumers; i++)
   {
      pthread_detach(consumerThreads[i]);
   }
   
   /* Start producer threads */
   for (int i = 0; i < numProducers; i++)
   {
      pthread_detach(producerThreads[i]);
   }
   
   /* Wait for specified time */
   usleep(sleep_length * 1000000);
   
   /* Cancel running threads */
   for (int i = 0; i < numProducers; i++)
   {
      pthread_cancel(producerThreads[i]);
   }
   
   for (int i = 0; i < numConsumers; i++)
   {
      pthread_cancel(consumerThreads[i]);
   }
   
   
   /* Free dynamically allocated memory */
   for (int i = 0; i < numProducers + numConsumers; i++)
   {
      free(threadID[i]);
   }

   return 0;
}