// bro ercanbrack stack assignment
#include <iostream>
using namespace std;

class Stack
{
    private:
      bool owner;
      static int stack[10];
      static bool locked;
      static int top;
    public:
      Stack(){ owner = false;};
      void push(int value);
      void pop();
      void lock();
      void unlock();
};

int main (void)
{
   Stack aStack;
   aStack.push (1);
   Stack bStack;
   bStack.push (2);
   Stack cStack;
   cStack.push (3);
   Stack dStack;
   dStack.pop ();
   cStack.pop ();
   dStack.push (4);
   aStack.pop ();
   bStack.unlock ();
   cStack.lock ();
   cStack.push (5);
   aStack.pop ();
   dStack.lock ();
   bStack.unlock ();
   dStack.push (6);
   cStack.unlock ();
   cStack.push (7);
   aStack.pop ();
   dStack.pop ();
   bStack.pop ();
   cStack.pop ();
}

// static declarations
int Stack::stack[10];
bool Stack::locked = false;
int Stack::top = 0;

// memeber functions
void Stack::push(int value)
{
   if (!locked || owner)
   {
      stack[top] = value;
      cout << value << " pushed to location " << top << endl;
      top++;
   }
   else
      cout << value << " push failed; stack locked\n";
}

void Stack::pop()
{
   if (top < 1)
      cout << "error: nothing on stack to pop\n";
   
   else if (!locked || owner)
   {
      cout << stack[top - 1] << " popped from location " << top - 1 << endl;
      top--;
   }

   else
      cout << "pop failed; stack locked\n";
}

void Stack::lock()
{
   if (!locked)
   {
      cout << "lock successful\n";
      locked = true;
      owner = true;
   }
   else
      cout << "lock failed; stack locked\n";
}

void Stack::unlock()
{
   if (!locked)
      cout << "unlock failed; stack not locked\n";
   else if (!owner)
      cout << "unlock failed; not lock owner\n";
   else
   {
      locked = false;
      owner = false;
      cout << "unlock successful\n";
   }
}
