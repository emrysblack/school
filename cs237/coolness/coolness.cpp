/*************************************************************************
* Binary Predicates and Nested Quantifiers Implementation
*************************************************************************/
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;

/*************************************************************************
* Binary predicate class declaration.
*
* Add to this if desired, but do NOT change the functions already in it.
*
* This is an abstract base class with pure virtual functions
* (per the =0 suffix).
*************************************************************************/
template<typename T1, typename T2>
class Predicate
{
public:
   /***********************************************************
    * Is this Predicate true for the given x and y?
    ***********************************************************/
   virtual bool isTrue(T1 x, T2 y)=0;

   /***********************************************************
    * Is this Predicate false for the given x and y?
    ***********************************************************/
   virtual bool isFalse(T1 x, T2 y)=0;

   /***********************************************************
    * Is this Predicate true for all x for all y
    * in the supplied domains?
    ***********************************************************/
   bool forAllForAll(vector<T1> domain1, vector<T2> domain2);

   /***********************************************************
    * Is this Predicate true for all x for some y
    * in the supplied domains?
    ***********************************************************/
   bool forAllForSome(vector<T1> domain1, vector<T2> domain2);

   /***********************************************************
    * Is this Predicate true for some x for all y
    * in the supplied domains?
    ***********************************************************/
   bool forSomeForAll(vector<T1> domain1, vector<T2> domain2);

   /***********************************************************
    * Is this Predicate true for some x for some y
    * in the supplied domains?
    ***********************************************************/
   bool forSomeForSome(vector<T1> domain1, vector<T2> domain2);
};

class Object
{
public:
   string name;
   int weight;
};

class Person : public Object
{
public:
   Person(string pName = "Waldo", int pWeight = 20)
   {
      name = pName;
      weight = pWeight;
   }
};

class Duck : public Object
{
public:
   Duck()
   {
      name = "Duck";
      weight = 10;
   }
};

class Church : public Object
{
public:
   Church()
   {
      name = "Church";
      weight = 100;
   }
};

class Apple : public Object
{
public:
   Apple()
   {
      name = "Apple";
      weight = 15;
   }
};

class VerySmallRock : public Object
{
public:
   VerySmallRock()
   {
      name = "VerySmallRock";
      weight = 20;
   }
};

bool madeOfWood(Object x);

/***************************************************************
 * IsAWitch is a Predicate whose isTrue function returns true if
 * its person argument is less or equal to the duck argument and
 * the person argument passes the made-of-wood test
 *
 * Its isFalse function just returns the opposite by calling
 * isTrue and negating its value.
 ***************************************************************/
class WeighsLessThanOrTheSameAs : public Predicate<Person, Object>
{
public:
   bool isTrue(Person x, Object y)
   {
      // If she weighs the same as a duck or less than a duck...
      return (x.weight <= y.weight);
   }

   bool isFalse(Person x, Object y)
   {
      return !isTrue(x, y);
   }
};

class GreaterThan : public Predicate<int, int>
{
public:
   bool isTrue(int x, int y)
   {
      return x > y;
   }
   bool isFalse(int x, int y)
   {
      return !isTrue(x, y);
   }
};

class LessThan : public Predicate<int, int>
{
public:
   bool isTrue(int x, int y)
   {
      return x < y;
   }
   bool isFalse(int x, int y)
   {
      return !isTrue(x, y);
   }
};

class IsAdditiveInverse : public Predicate<int, int>
{
   public:
   bool isTrue(int x, int y)
   {
      return x + y == 0;
   }
   bool isFalse(int x, int y)
   {
      return !isTrue(x, y);
   }
};

class IsOppositeNegative : public Predicate<int, int>
{
   public:
   bool isTrue(int x, int y)
   {
      return x + y == 0 && (x < 0 || y < 0);
   }
   bool isFalse(int x, int y)
   {
      return !isTrue(x, y);
   }
};

/***************************************************************
 * Reports on what was learned.
 ***************************************************************/
void learned()
{
   cout << "I learned a lot.\n";
}

/***************************************************************
 * Shows how to use the program.
 ***************************************************************/
void usage()
{
   cout << "\nHere's how you can too.\n";
}

/***************************************************************
 * Runs one test, identified by its string argument.
 ***************************************************************/
void runOne(string test)
{
   WeighsLessThanOrTheSameAs witches;
   vector<Person> knownWitches;
   vector<Object> ducks;
   vector<Object> objects;
   Person p ("shelly", 10);
   Duck d;
   Apple a;
   Church c;
   VerySmallRock v;
   knownWitches.push_back(p);
   ducks.push_back(d);
   objects.push_back(p);
   objects.push_back(d);
   objects.push_back(a);
   objects.push_back(c);
   objects.push_back(v);

   GreaterThan greater;
   LessThan less;
   IsAdditiveInverse additive;
   IsOppositeNegative negative;
   vector<int> oneDigit;
   vector<int> twoDigit;
   vector<int> nonPositive;
   vector<int> positive;
   for (int i = 0; i < 10; i++)
   {
      oneDigit.push_back(i);
      positive.push_back(i + 1);
      twoDigit.push_back(i + 10);
      nonPositive.push_back(i * -1);
   }
   
   cout << "\nRunning test " << test << endl;

   if (test =="taa")
   {
      cout << "All two digit positive numbers are greater than\n"
           << "single digit non-negative numbers"
           << "expected to return True\n"
           << "Actual return value is "
           << greater.forAllForAll(twoDigit, oneDigit)
           << ".\n";
   }
      
   else if (test == "faa")
   {
      cout << "All non-positive numbers are less than\n"
           << "non-negative numbers\n"
           << "expected to return False\n"
           << "Actual return value is "
           << less.forAllForAll(nonPositive, oneDigit)
           << ".\n";
   }
      
   else if (test == "tas")
   {
      cout << "All single digit numbers have\n"
           << "an additive inverse\n"
           << "expected to return True\n"
           << "Actual return value is "
           << additive.forAllForSome(oneDigit, nonPositive)
           << ".\n";
   }
      
   else if (test == "fas")
   {
      cout << "All single digit numbers have\n"
           << "an opposite negative number\n"
           << "expected to return False\n"
           << "Actual return value is "
           << negative.forAllForSome(oneDigit, nonPositive)
           << ".\n";      
   }
      
   else if (test == "tsa")
   {
      cout << "For some non-negative number, all\n"
           << "all positive numbers are greater\n"
           << "expected to return True\n"
           << "Actual return value is "
           << less.forSomeForAll(oneDigit, positive)
           << ".\n";  
   }
      
   else if (test == "fsa")
   {
      cout << "For some single digit non-negative number, all\n"
           << "all single digit non-negative numbers are less than it\n"
           << "expected to return False\n"
           << "Actual return value is "
           << less.forSomeForAll(oneDigit, oneDigit)
           << ".\n";  
   }
      
   else if (test == "tss")
   {
   }
      
   else if (test == "fss")
   {
   }
   
   else if (test == "weighsLessThanOrTheSameAs")
   {
   }
   
   else if (test == "isMadeOfWood")
   {
   }

   else if (test == "isAWitch")
   {
   }
   
   else
   {
      learned();
      usage();
   }
}

/***************************************************************
 * Runs all tests.
 ***************************************************************/
void runAll()
{
   cout << "Running all tests.\n";
   string tests[] = {"taa", "faa",
                     "tas", "fas",
                     "tsa", "fsa",
                     "tss", "fss",
                     "weighsLessThanOrTheSameAs",
                     "isMadeOfWood",
                     "isAWitch"};
   for(int i = 0; i < 11; i++)
   {
      runOne(tests[i]);
   }
}

/***********************************************************
 * Is this Predicate true for all x for all y
 * in the supplied domains?
 ***********************************************************/
template<typename T1, typename T2>
bool Predicate<T1, T2>::forAllForAll(vector<T1>domain1, vector<T2>domain2)
{
   for (int i = 0; i < domain1.size(); i++)
   {
      for (int j = 0; j < domain2.size(); j++)
      {
         if (isFalse(domain1[i], domain2[j]))
         {
            return false;
         }
      }
   }
   return true;
}

/***********************************************************
 * Is this Predicate true for all x for some y
 * in the supplied domains?
 ***********************************************************/
template<typename T1, typename T2>
bool Predicate<T1, T2>::forAllForSome(vector<T1>domain1, vector<T2>domain2)
{
   bool hasSome;
   for (int i = 0; i < domain1.size(); i++)
   {
      hasSome = false;
      for (int j = 0; j < domain2.size(); j++)
      {
         if (isTrue(domain1[i], domain2[j]))
         {
            hasSome = true;
         }
      }
      if (!hasSome)
      {
         return false;
      }
   }
   return true;
}

/***********************************************************
 * Is this Predicate true for some x for all y
 * in the supplied domains?
 ***********************************************************/
template<typename T1, typename T2>
bool Predicate<T1, T2>::forSomeForAll(vector<T1>domain1, vector<T2>domain2)
{
   bool hasAll;
   for (int i = 0; i < domain1.size(); i++)
   {
      hasAll = true;
      for (int j = 0; j < domain2.size(); j++)
      {
         if (isFalse(domain1[i], domain2[j]))
         {
            hasAll =  false;
         }
      }
      if (hasAll)
         return true;
   }
   return false;
}

/***********************************************************
 * Is this Predicate true for some x for some y
 * in the supplied domains?
 ***********************************************************/
template<typename T1, typename T2>
bool Predicate<T1, T2>::forSomeForSome(vector<T1>domain1, vector<T2>domain2)
{
   for (int i = 0; i < domain1.size(); i++)
   {
      for (int j = 0; j < domain2.size(); j++)
      {
         if (isTrue(domain1[i], domain2[j]))
         {
            return true;
         }
      }
   }
   return false;
}

bool madeOfWood(Object x)
{
   bool wood = false;
   for (int i = 0; i < x.name.length() - 1; i++)
   {
      // everyone knows that someone with double letters in their name
      // is made of wood. Just like the word wood itself
      if (x.name[i] == x.name[i + 1])
         wood = true;
   }
   return wood;
}
