// test for class nesting
#include <iostream>
using namespace std;

template<class T>
class A
{
public:
   A() { data = new C; }
   ~A() { if (data) { delete data; data = NULL; } }
   T getData() { return data->getData(); }
   class B
   {
   public:
      B() { data = 2;}
      T getData() { return data; }
   private:
      T data;
   };
private:
   class C
   {
   public:
      C() { data = 1; }
      T getData() { return data; }
   private:
      T data;
   };
   C * data;
};


int main()
{
   A<int> a;
   A<int>::B b;
   cout << a.getData() << " " << b.getData() << endl;
   return 0;
}
