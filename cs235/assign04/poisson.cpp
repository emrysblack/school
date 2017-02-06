#include <math.h>
#include <cstdlib>
#include <time.h>

class Random
{
 public:
  Random();

  /* --- Get next Poisson random --- */
  int poissonRandom(double expected);

};


Random::Random()
{
   // srand((int)time(NULL));   // variable seed for real simulation
   srand(2500);                 // fixed seed for debug and grading
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

