// Test for const and class overloading
#include <iostream>
using namespace std;

class Test
{
private:
   int a;
   int b;
public:
   Test(int p1 = 0, int p2 = 0){ a = p1; b = p2;}
   int getA() const {return a;}
   int getB() const {return b;}
   Test& setA(int p){a = p;}
   void setB(int p){b = p;}
   void display(ostream & out) const {out << a << " " << b;}
};

ostream & operator <<(ostream & out, const Test & rhs)
{
   rhs.display(out);
   return out;
}

const Test operator +(const Test & lhs, const Test & rhs)
{
   Test temp;
   temp.setA(lhs.getA() + rhs.getA());
   temp.setB(lhs.getB() + rhs.getB());
   return temp;
}

int main()
{
   Test test(1, 1);
   Test test1(10, 10);
   Test test2 = test + test1;
   cout << "Test: " << test << endl;
   cout << "Test1: " << test1 << endl;
   cout << "Test + Test1: " << test + test1 << endl;
   cout << "Test2: " << test2 << endl;
   return 0;
}
