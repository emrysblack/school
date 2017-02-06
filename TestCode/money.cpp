// test for money
#include <iostream>
#include <iomanip>
using namespace std;

class Money
{
   public:
   Money() // default
   {
      cents = 0;
   }
   Money(int c) // cents
   {
      cents = 0;
      setCents(c);
   }
   Money(int d, int c) // dollars and cents
   {
      cents = 0;
      setDollars(d);
      setCents(c);
   }
   int getDollars() const { return cents / 100; }
   int getCents() const { return cents % 100; }
   void setDollars(int d)
   {
      cents = (d >= 0 ? d: -d) * 100 + cents % 100;
   }
   void setCents(int c)
   {
      cents = cents / 100 * 100 + (c >= 0 ? c: -c);
   }
   private:
   int cents; // is better than separate, translates into proper dollars
};

ostream & operator << (ostream & out, const Money & money)
{
   out << "$" << money.getDollars() << "."
       << setw(2) << setfill('0')
       << money.getCents() << setfill(' ');
   return out;
}

istream & operator >> (istream & in, Money & money)
{
   int d, c;
   cout << "Dollars: ";
   in >> d;
   cout << "Cents: ";
   in >> c;
   money.setDollars(d);
   money.setCents(c);
   return in;
}

int main()
{
   Money money; // default
   // Money money1(501); // cents
   // Money money2(1,7); // dollars and cents
   cin >> money;
   cout << money << endl;
   cout << "That is "
       << money.getDollars()
       << (money.getDollars() != 1 ? " dollars" : " dollar")
       << " and "
       << money.getCents()
       << (money.getCents() != 1 ? " cents!\n" : " cent!\n");
   // cout << money1 << endl;
   // cout << money2 << endl;
   return 0;
}
