/********************************************************
 * Class: Random
 * 
 * Purpose: Generate randmon numbers
 *
 * Constructor: Random (), seeds the random number generator
 *
 * Member Functions: NextInt(int low, int high) - Generate a random
 *                   number between the low and the high values.
 *******************************************************/
class Random
{
 public:
  Random();

  /* --- Get next integer in range low-high --- */
  int nextInt(int low, int high); 

};

/*********************************************************
 *
 *    FUNCTION: Random
 *
 *  PARAMETERS: None
 *
 *     PURPOSE: Random constructor.  Sets the random number
 *              seed to the current time.  The srand function
 *              is provided by stdlib.h and time by time.h
 *              Passing NULL to the time function returns
 *              the current time (in clock ticks) and this
 *              is then passed to srand.
 *
 *       USAGE: Creates a random object to generate random numbers
 *              
 *              Random r1;  
 *
 *********************************************************/
Random::Random()
{
  srand((int)time(NULL));
}

/*********************************************************
 *
 *    FUNCTION: NextInt
 *
 *  PARAMETERS: low - smallest number in range
 *              high - largest number in range
 *
 *     PURPOSE: This function does the following:
 *                1. Generate a real number between 0 and 1 
 *                   by calling rand() and dividing by
 *                   the constant RAND_MAX + 1
 *                2. Scale this number to the appropriae range
 *                   size (high - low)
 *                3. Truncate the value to an integer
 *                4. Translate the number to the appropriate
 *                   starting point.
 *
 *        USAGE: Assumes random object has been created.
 *               This call will create 1 random number betwen
 *               1 and 50.
 *
 *               num = r1.NextInt(1,50);
 *
 *********************************************************/
int Random::nextInt(int low, int high)
{
  int k;
  double d;
  
  d = (double)rand()/((double)RAND_MAX+1);
  k = (int)(d*(high-low+1));
  return(low+k);
}

/*********************************************************
 * Function: genRand - generate an array of random numbers
 *
 * Parameters: the size of the array
 *
 * Returns: A pointer to the newly created array
 ********************************************************/
int* genRandom (int arraySize, int LOW = 1, int HIGH = 500)
{
    int* intArray = new int[arraySize];
    Random random;

    for (int i = 0; i < arraySize; ++i)
    {
        intArray[i] = random.nextInt(LOW, HIGH);
    }

    return intArray;
}

