#include <iostream>
#include <math.h>
#include <cstdlib>
#include <time.h>

using namespace std;

class Random
{
 public:
  Random();

  /* --- Get next Poisson random --- */
  int poissonRandom(double expected);

};



Random::Random()
{
  srand((int)time(NULL));
}

int Random::poissonRandom(double expected)
{
  int n=0;
  double limit;
  double x;
  
  limit = exp(-expected);
  x = rand()/((double)RAND_MAX+1);
  while (x>limit)
    {
      n++;
      x *= rand()/((double)RAND_MAX+1);
    }
  return n;
}

main(int argc, char* argv[])
{

   int planesArrived;
   int simLength = 20;
   double expectedArrivalsPerTimeUnit = .46;
   if (argc > 1)
   {
      expectedArrivalsPerTimeUnit = atof(argv[1]);
   }
   Random myRand;
   for(int i = 0; i < simLength; i++)
   {
      planesArrived = myRand.poissonRandom(expectedArrivalsPerTimeUnit);
      cout << "Planes arrived = " << planesArrived << endl;
   }
}
