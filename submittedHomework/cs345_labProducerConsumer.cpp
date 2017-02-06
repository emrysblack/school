/***********************************************************************
* Program:
*    Lab ProducerConsumer  
*    Brother Jones, CS 345
* Author:
*    Brady Field
*
* Conclusions:
*    fun lab. I haven't figured out the semaphores yet, but I'm close
*
* Summary:
*    simulates the producer/consumer problem and solves it using
*    multi-threading
************************************************************************/
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
int index = 0;
int numItems = 0;

void *producer (void *param)
{
   bufferItem itemProduced;
   while(true)
   {
      usleep(rand() % 150000);
      itemProduced = (rand() % 999 + 1);
      if (numItems < 5)
      {
         pthread_mutex_lock(&mutex);
         //TODO: insert item into the buffer.
         cout << setw(5) << itemProduced
              << setw(7) << "P" << (long) param<< endl;
         buffer[index] = itemProduced;
         index = (index + 1) % BUFFER_SIZE;
         numItems++;
         pthread_mutex_unlock(&mutex);
      }
   }
   pthread_exit(NULL);
}

void *consumer (void *param)
{
   bufferItem consumedItem;
//   usleep(rand() % 150000);
   while(true)
   {
      usleep(rand() % 150000);
      if (numItems > 0)
      {
         pthread_mutex_lock(&mutex);
         cout << setw(22) << buffer[(index + BUFFER_SIZE - numItems) % BUFFER_SIZE]
              << setw(7) << "C" << (long) param << endl;
         numItems--;
         pthread_mutex_unlock(&mutex);
      }
//TODO: consume the item from the buffer.
   }
   pthread_exit(NULL);
}


int main(int argc, char** argv)
{
   if(argc != 4)
   {
      cout << "\nInvalid input.\n\n";
      return 0;
   }

   //full = BUFFER_SIZE;
   int secondsToSleep = atoi(argv[1]) * 1000000;
   int producerThreads = atoi(argv[2]);
   int consumerThreads = atoi(argv[3]);
   pthread_t producerThreadsArray[producerThreads];
   pthread_t consumerThreadsArray[consumerThreads];
   int ct;
   
   for(long i = 0; i < producerThreads; i++)
   {
      ct = pthread_create(&producerThreadsArray[i], NULL, producer, (void *)(i + 1));

      if(ct)
      {
         cout << "THERE WAS AN ERROR. Return code from pthread_create is: "
              << ct << endl;
         exit(-1);
      }
   }

   for(long i = 0; i < consumerThreads; i++)
   {
      ct = pthread_create(&consumerThreadsArray[i], NULL, consumer, (void*) (i + 1));

      if(ct)
      {
         cout << "THERE WAS AN ERROR. Return code from pthread_create is: "
              << ct << endl;
         exit(-1);
      }
   }
   cout << "Produced  by P#  Consumed  by C#\n========  =====  ========  =====\n";
   usleep(secondsToSleep);
   for (long i = 0; i < producerThreads; i++)
   {
      pthread_cancel(producerThreadsArray[i]);
   }
   for (long i = 0; i < consumerThreads; i++)
   {
      pthread_cancel(consumerThreadsArray[i]);
   }
 
   return 0;
}
