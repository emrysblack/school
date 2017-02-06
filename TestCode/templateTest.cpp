// Test for const and class overloading
#include <iostream>
using namespace std;

template <class T>
class Test
{
private:
   T a;
   T b;
public:
   Test(T p1 = 0, T p2 = 0){ a = p1; b = p2;}
   Test(const Test &rhs){ a = rhs.a; b = rhs.a;}
   T getA() const {return a;}
   T getB() const {return b;}
   Test& setA(T p){a = p;}
   void setB(T p){b = p;}
   void display(ostream & out) const {out << a << " " << b;}
};

template <class T>
ostream & operator <<(ostream & out, const Test<T> & rhs)
{
   rhs.display(out);
   return out;
}

template <class T>
const Test<T> operator +(const Test<T> & lhs, const Test<T> & rhs)
{
   Test<T> temp(lhs);
   temp.setA(lhs.getA() + rhs.getA());
   temp.setB(lhs.getB() + rhs.getB());
   return temp;
}

int main()
{
   Test<int> test(1, 1);
   Test<int> test1(10, 10);
   Test<int> test2 = test + test1;
   // Test<string> test(" Hi", " Brady ");
   // Test<string> test1(" Hello ", " Back ");
   // Test<string> test2 = test + test1;
   cout << "Test: " << test << endl;
   cout << "Test1: " << test1 << endl;
   cout << "Test + Test1: " << test + test1 << endl;
   cout << "Test2: " << test2 << endl;
   return 0;
}
