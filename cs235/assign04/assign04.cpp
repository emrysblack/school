/***********************************************************************
* Program:
*    Homework 04, Airport Simulation 
*    Brother Twitchell, CS235
* Author:
*    Brady Field
* Summary: 
*    Will take in a few user inputs to simulate an airport using random
*    numbers.
************************************************************************/

#include <iostream>
#include <math.h>
#include <cstdlib>
#include <iomanip>
#include <time.h>
using namespace std;

/**********************************************************************
 * random numbers generated with fixed seed for grading
 **********************************************************************/
class Random
{
   public:
      Random();

      /* --- Get next Poisson random --- */
      int poissonRandom(double expected);

};

// template
template <typename QueueElement>

/**********************************************************************
 * queue class modified to work with templates
 **********************************************************************/
class Queue
{
   private:
     int front;                  // --- index of front of queue
     int back;                   // --- index of back of queue
     int maxSize;                // --- max storage capacity of array
     QueueElement *queueItems;            // --- array containing queue items

   public:
     Queue(int = 128);           // --- constructor
     Queue(const Queue<QueueElement> &aQueue); // --- copy constructor
     ~Queue(void);               // --- destructor
     void insert(QueueElement item);      // --- insert item into back of queue
     QueueElement remove(void);           // --- remove item from front of queue
     bool empty(void);           // --- returns 1 if queue is empty, 0 otherwise
     bool full(void);            // --- returns 1 if queue is full, 0 otherwise
     Queue& operator = (const Queue<QueueElement> &rtSide); // overload assign
};

/**********************************************************************
 * not used in this version
 * but I will when I make the new one
 **********************************************************************/
class Airport
{
public:
private:
};

/**********************************************************************
 * plane class
 **********************************************************************/
class Plane
{
public:
   float getWaitTime();
private:
   float waitTime;
};

/**********************************************************************
 * Asks for user input, runs plane simulation and outputs results
 ***********************************************************************/
int main()
{
   int curTime;
   int endTime;
   int totalPlanes = 0;
   int planesIn = 0;
   int planesOut = 0;
   int refused = 0;
   int landed = 0;
   int departed = 0;
   int idleTime = 0;
   int landReady = 0;
   int departReady = 0;
   float arriveRate;
   float departRate;
   float waitIn = 0;
   float waitOut = 0;
   Queue<int> landing(5);
   Queue<int> departing(5);
   Random arrivals;
   Random departures;
   
   // get user input
   cout << "Units of time the simulation will run: ";
   cin >> endTime;
   cout << "Expected number of arrivals per time unit: ";
   cin >> arriveRate;
   cout << "Expected number of take offs per time unit: ";
   cin >> departRate;
   cout << endl;
   
   // run simulation
   for (curTime = 0; curTime < endTime; curTime++)
   {
      // get planes flying in
      planesIn = arrivals.poissonRandom(arriveRate);
      for (int i = 0; i < planesIn; i++)
      {
         if (landing.full())
            refused++;
         else
            landing.insert(curTime);
      }
      totalPlanes += planesIn;
      
      // get planes flying out
      planesOut = departures.poissonRandom(departRate);
      for (int i = 0; i < planesOut; i++)
      {
         if (departing.full())
            refused++;
         else
            departing.insert(curTime);
      }
      totalPlanes += planesOut;
      if (!landing.empty())
      {
         // land plane and get time waited
         waitIn += curTime - landing.remove();
         landed++;
      }
      else if (!departing.empty())
      {
         // depart and get time waited
         waitOut += curTime - departing.remove();
         departed++;
      }
      else
         idleTime++;
   }
   while (!landing.empty())
   {
      landing.remove();
      landReady++;
   }
   while (!departing.empty())
   {
      departing.remove();
      departReady++;
   }
   waitIn /= landed; // average total waiting time for planes landed
   waitOut /= departed; // average total waiting time for planes departed
   idleTime *= 100;
   float percentIdle = idleTime/endTime;
   // display results
   cout << "Total number of planes processed: " << totalPlanes << endl;
   cout << "Number of planes landed: " << landed << endl;
   cout << "Number of planes taken off: " << departed << endl;
   cout << "Number left ready to land: " << landReady << endl;
   cout << "Number left ready to take off: " << departReady << endl;
   cout << "Number of planes refused use: " << refused << endl;
   cout << "Percentage of time runway idle: ";
   cout.precision(2);
   cout.setf(ios::fixed,ios::floatfield);
   cout << percentIdle << "%\n";
   cout << "Average wait time to land: " << waitIn << endl;
   cout << "Average wait time to take off: " << waitOut << endl;
   return 0;
}

/**********************************************************************
 * generate random number without parameters - fixed seed
 **********************************************************************/
Random::Random()
{
   // srand((int)time(NULL));   // variable seed for real simulation
   srand(2500);                 // fixed seed for debug and grading
}

/**********************************************************************
 * generate random number with expected passed in - fixed seed
 **********************************************************************/
int Random::poissonRandom(double expected)
{
   int n = 0;
   double limit;
   double x;
  
   limit = exp(-expected);
   x = rand() / ((double)RAND_MAX + 1);
   while (x > limit)
   {
      n++;
      x *= rand() / ((double)RAND_MAX + 1);
   }
   return n;
}

/**********************************************************************
 * default constructor
 **********************************************************************/
template <typename QueueElement>
Queue<QueueElement>::Queue(int size)    
{
   maxSize = size > 0 ? size : 128; // don't allow a negative size
   back = 0;
   front = 0;
   queueItems = new int[maxSize];
}

/**********************************************************************
 * destructor
 **********************************************************************/
template <typename QueueElement>
Queue<QueueElement>::~Queue(void)
{
   delete [] queueItems;
}

/***********************************************************************
 * Queue Copy Constructor
 ***********************************************************************/
template <typename QueueElement>
Queue<QueueElement>::Queue(const Queue<QueueElement> &aQueue)
{
   maxSize = aQueue.maxSize;
   front = aQueue.front;
   back = aQueue.back;
   queueItems = new int[maxSize];
   for (int i = 0; i < maxSize; i++)
   {
      queueItems[i] = aQueue.queueItems[i];
   }
}

/***********************************************************************
 * Overloaded assignment operator.
 ***********************************************************************/
template <typename QueueElement>

 Queue<QueueElement>& Queue<QueueElement>::operator =
 (const Queue<QueueElement> &rtSide)
{
   if (this != &rtSide)
   {
   
      if (maxSize != rtSide.maxSize)
      {
         delete [] queueItems;
         queueItems = new int[rtSide.maxSize];
      }
      for (int i = 0; i < rtSide.maxSize; i++)
      {
         queueItems[i] = rtSide.queueItems[i];
      }
      maxSize = rtSide.maxSize;   //max size of queue
      back = rtSide.back;
      front = rtSide.front;
   }
   return *this;
}

/**********************************************************************
 * returns true if queue is empty
 **********************************************************************/
template <typename QueueElement>
bool Queue<QueueElement>::empty(void)
{
   return front == back;
}

/**********************************************************************
 * returns true if queue is full
 **********************************************************************/
template <typename QueueElement>
bool Queue<QueueElement>::full(void)
{
   return (back - front) >= maxSize;
}

/**********************************************************************
 * inserts item into back of queue, then increments number of items
 * in queue
 **********************************************************************/
template <typename QueueElement>
void Queue<QueueElement>::insert(QueueElement item)
{
   // --- check for overflow
   if (full())
   {
      cout << "queue overflow" << endl;
      exit(1); // a terrible thing for an object to do
   }
   queueItems[back % maxSize] = item;
   ++back;
}

/**********************************************************************
 * removes item from front of queue, then decrements number of items
 * in queue
 **********************************************************************/
template <typename QueueElement>
QueueElement Queue<QueueElement>::remove(void)
{
   QueueElement temp;
   
   if (empty())
   {
      cout << "queue underflow" << endl;
      exit(1); // a terrible thing for an object to do
   }
   temp = queueItems[front % maxSize];
   ++front;
   if (front >= maxSize)
   {
      front -= maxSize;
      back -= maxSize;
   }
   return temp;
}
