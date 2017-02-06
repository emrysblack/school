// test for lack of return, what the heck?
// Turns out the return statement uses the EAX register,
// so the end of function returns whatever is in there which
// happens to be the last evaluated statement
#include <iostream>
#include <iomanip>
using namespace std;

float getDollar()
{
   float dollar;
   cout << "Enter dollars: ";
   cin >> dollar;
}

float getEuro(float dollar)
{
   float euro = dollar / 1.41;
}

int main()
{
   float dollar = getDollar();
   float euro = getEuro(dollar);
   cout << "Euro: " << fixed << setprecision(2) << euro << endl;
   return 0;
}
