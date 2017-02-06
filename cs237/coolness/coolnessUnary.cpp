/*************************************************************************
 * Sample code (unary Predicate only --- no nested quantifiers)
 *************************************************************************/
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;

/**************************************************************
 * The Predicate class is an abstract base class with pure virtual
 * abstract functions (per the =0 suffix).
 ***************************************************************/
template<typename T>
class Predicate
{
public:
   /**************************************************************
    * Is this Predicate true for the given x?
    **************************************************************/
   virtual bool isTrue(T x)=0;

   /**************************************************************
    * Is this Predicate true for the given x?
    **************************************************************/
   virtual bool isFalse(T x)=0;

   /***************************************************************
    * Is this Predicate true for all values in the given domain?
    ***************************************************************/
   bool forAll(vector<T> domain);

   /***************************************************************
    * Is this Predicate true for some value in the given domain?
    ***************************************************************/
   bool forSome(vector<T> domain);
};

/***************************************************************
 * forAll is A#xP(x) (The Universal Quantification of P(x), the
 * proposition that is true if and only if P(x) is true for all
 * x in the universe of discourse.)
 *
 * This function loops through all values in a domain
 * (of a finite size) to see if the Predicate is always true.
 * If it encounters a value for which the Predicate is false,
 * then A#xP(x) is false. Otherwise A#xP(x) is true.
 ***************************************************************/
template<typename T>
bool Predicate<T>::forAll(vector<T> domain)
{
   for (int i = 0; i < domain.size(); i++)
   {
      if (isFalse(domain[i]))
      {
         return false;
      }
   }
   return true;
}

/***************************************************************
 * forSome = E#xP(x) (The Existential Quantification of P(x),
 * the proposition that is true if and only if there exists an
 * x in the universe of discourse such that P(x) is true.)
 *
 * This function loops through all values in a domain
 * (of a finite size) to see if the Predicate is ever true.
 * If it encounters any value for which the Predicate is true,
 * then E#xP(x) is true. Otherwise E#xP(x) is false.
 ***************************************************************/
template<typename T>
bool Predicate<T>::forSome(vector<T> domain)
{
   for (int i = 0; i < domain.size(); i++)
   {
      if (isTrue(domain[i]))
      {
         return true;
      }
   }
   return false;
}

/***************************************************************
 * IsEven is a Predicate whose isTrue function returns true if
 * its integer argument is even (divisible by 2 -- meaning it
 * has a remainder of 0 when divided by 2 (using the mod operator
 * (%))).
 * Its isFalse function just returns the opposite by calling
 * isTrue and negating its value.
 ***************************************************************/
template <typename T>
class IsEven : public Predicate<int>
{
public:
   bool isTrue(int x)
   {
      return ((x % 2) == 0);
   }

   bool isFalse(int x)
   {
      return !isTrue(x);
   }
};

/***************************************************************
 * IsOdd is a Predicate whose isTrue function returns true if
 * its integer argument is odd (NOT divisible by 2 -- meaning it
 * has a remainder of 1 when divided by 2 (using the mod operator
 * (%))).
 * Its isFalse function just returns the opposite by calling
 * isTrue and negating its value.
 ***************************************************************/
template <typename T>
class IsOdd : public Predicate<int>
{
public:
   bool isTrue(int x)
   {
      return ((x % 2) == 1);
   }

   bool isFalse(int x)
   {
      return !isTrue(x);
   }
};

/***************************************************************
 * main tests for both true and false return values for the
 * two functions forAll and forSome for the simple Predicates
 * IsEven and IsOdd.
 ***************************************************************/
int main()
{
   IsEven<int> even;
   IsOdd<int> odd;

   vector<int> smallEvens;
   smallEvens.push_back(0);
   smallEvens.push_back(2);
   smallEvens.push_back(4);
   smallEvens.push_back(6);
   smallEvens.push_back(8);

   vector<int> smallOdds;
   smallOdds.push_back(1);
   smallOdds.push_back(3);
   smallOdds.push_back(5);
   smallOdds.push_back(7);
   smallOdds.push_back(9);

   cout << boolalpha; // so 1 prints as true and 0 as false
   cout << "even.forAll(smallEvens)\n"
        << "     expected to return true;\n"
        << " actual return value is "
        <<  even.forAll(smallEvens) << ".\n\n";
   cout << "odd.forAll(smallEvens)\n"
        << "     expected to return false;\n"
        << " actual return value is "
        <<  odd.forAll(smallEvens) << ".\n\n";
   cout << "even.forAll(smallOdds)\n"
        << "     expected to return false;\n"
        << " actual return value is "
        <<  even.forAll(smallOdds) << ".\n\n";
   cout << "odd.forAll(smallOdds)\n"
        << "     expected to return true;\n"
        << " actual return value is "
        <<  odd.forAll(smallOdds) << ".\n\n";

   cout << "--------------------------------\n\n";

   cout << "even.forSome(smallEvens)\n"
        << "     expected to return true;\n"
        << " actual return value is "
        <<  even.forSome(smallEvens) << ".\n\n";
   cout << "odd.forSome(smallEvens)\n"
        << "     expected to return false;\n"
        << " actual return value is "
        <<  odd.forSome(smallEvens)  << ".\n\n";
   cout << "even.forSome(smallOdds)\n"
        << "     expected to return false;\n"
        << " actual return value is "
        <<  even.forSome(smallOdds) << ".\n\n";
   cout << "odd.forSome(smallOdds)\n"
        << "     expected to return true;\n"
        << " actual return value is "
        <<  odd.forSome(smallOdds)  << ".\n\n";

   return 0;
}
