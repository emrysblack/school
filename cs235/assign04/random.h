#ifndef _RANDOM_H
#define _RANDOM_H
class Random
{
 public:
  Random();

  /* --- Get next Poisson random --- */
  int poissonRandom(double expected);

};
#endif
