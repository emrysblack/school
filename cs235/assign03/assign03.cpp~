/***********************************************************************
* Program:
*    Homework 03, Assembly (e.g., Homework 01, Hello World!)
*    Brother Twitchell, CS 235   (e.g., Brother Twitchell, CS 235)
* Author:
*    Brady Field
* Summary: 
*    Reads an expression in infix notation from file, changes it to
*    postfix notation and displays corresponding Assembly language
*    code required to evaluate said expressions
***********************************************************************/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>

using namespace std;

// template declaration
template <typename StackElement>

/**********************************************************************
 * Stack class modified to be generic with templates
 **********************************************************************/ 
   class Stack
{
   private:
      int myTop;                  // index of top of stack
      int maxSize;                // maximum size of stack  
      StackElement *stackItems;            // pointer for dynamic array
   public:
      Stack(int size = 100);      // default constructor (stack size 100)
      Stack(const Stack<StackElement> &aStack); // copy constructor 
      StackElement top(void);              // returns top item in the stack
      void push(StackElement item);        // store item on the stack
      void pop(void);             // remove/delete top item off stack
      bool empty(void);           // is stack empty
      bool full(void);            // is stack full
      ~Stack();                   // destructor
      Stack& operator = (const Stack<StackElement> &rtSide);
};
bool readFile(char* fileName, string expression[]);
void convert(string expression[]);
void displayAssembly(string expression[]);

/**********************************************************************
 * reads in file, converts in to postfix notation and then displays
 * the assembly code
 **********************************************************************/
int main (int argc, char* argv[])
{
   if (argc != 2)
      cout << "ERROR: must be specified with one input file\n";
   else
   {
      string expression [10];
      if (readFile(argv[1], expression)) // read in expressions
      {   
         convert(expression);
         displayAssembly(expression);
      }
   }

   return 0;
}

/**********************************************************************
 * opens input file and reads in lines to array for storage
 **********************************************************************/
bool readFile(char* fileName, string expression[])
{
   ifstream input;
   input.open(fileName);
   if (input.fail())
   {
      cout << "ERROR: could not open " << fileName << endl;
      return false;
   }
   else
   {
      int i;
      for (i = 0; !input.eof(); i++)
         getline(input, expression[i]); 
      input.close();
      expression[i - 1] = "NULL"; // use NULL to mark end of input
      return true;
   }
}

/**********************************************************************
 * goes through the expressions and converts them into postfix
 * notation 
 **********************************************************************/
void convert(string expression[])
{
   string postfix; // stores postfix expression
   string p; // work on current expression
   Stack<char> stack; // stack to store operators

   for (int i = 0; expression[i] < "NULL"; i++) // counter for strings
   {
      p = expression[i];

      for (int j = 0; j < p.length(); j++) // counter for chars in strings
      {
         switch (p.at(j))
         {
            case '(': // always stack
               stack.push(p.at(j));
               break;
            case '*':
            case '/':
               if (!stack.empty())
               {
                  bool done = false;
                  while (!done) // process first
                  {
                     if (stack.top() == '*' or stack.top() == '/')
                     {
                        postfix += stack.top();
                        stack.pop();
                     }
                     else
                        done = true;
                  }
               }
               stack.push(p.at(j)); // stack last
               break;
            case '+':
            case '-':
               if (!stack.empty())
               {
                  bool done = false;
                  while (!done) // process first
                  {
                     if (stack.top() == '*' or stack.top() == '/' or
                         stack.top() == '+' or stack.top() == '-')
                     {
                        postfix += stack.top();
                        stack.pop();
                     }
                     else
                        done = true;
                  }
               }
               stack.push(p.at(j)); // stack last
               break;
            case ')':
               while (stack.top() != '(')
               {
                  postfix += stack.top();
                  stack.pop();
               }
               stack.pop();
               break;
            case ' ':
               break;
            default:
               postfix += p.at(j);
               break;
         }
      }
      p.assign(postfix);
      while (!stack.empty()) // pop remaining items off stack
      {
         p += stack.top();
         stack.pop();
      }
      expression[i].assign(p);
      postfix = ""; // clear temp string
   }
}

/**********************************************************************
 * takes the postfix notation and displays the evaluation
 * in assembly code
 **********************************************************************/
void displayAssembly(string expression[])
{
   string p; // work on current expression
   char l;
   char r;
   char n = '0'; // keep track of variable count
   Stack<char> stack; // stack to store operators

   for (int i = 0; expression[i] < "NULL"; i++) // counter for strings
   {
      p = expression[i];
      n = '0'; // reset variable count for each word
      
      for (int j = 0; j < p.length(); j++) // counter for chars in strings
      {
         switch (p.at(j))
         {
            case '*':
               r = stack.top(); // get left and right for equation
               stack.pop();
               l = stack.top();
               stack.pop();
               cout << "LD  "; // load left side
               if (isdigit(l))
                  cout << "TEMP"; // check for variable
               cout << l << endl;
               cout << "ML  "; // operate with right side
               if (isdigit(r))
                  cout << "TEMP"; // check for variable
               cout << r << endl;
               n++; // increase variable count for storage
               cout << "ST  TEMP" << n << endl;
               stack.push(n); // store result
               break;
            case '/':
               r = stack.top(); // get left and right for equation
               stack.pop();
               l = stack.top();
               stack.pop();
               cout << "LD  "; // load left side
               if (isdigit(l))
                  cout << "TEMP"; // check for variable
               cout << l << endl;
               cout << "DV  "; // operate with right side
               if (isdigit(r))
                  cout << "TEMP"; // check for variable
               cout << r << endl;
               n++; // increase variable count for storage
               cout << "ST  TEMP" << n << endl;
               stack.push(n); // store result
               break;
            case '+':
               r = stack.top(); // get left and right for equation
               stack.pop();
               l = stack.top();
               stack.pop();
               cout << "LD  "; // load left side
               if (isdigit(l))
                  cout << "TEMP"; // check for variable
               cout << l << endl;
               cout << "AD  "; // operate with right side
               if (isdigit(r))
                  cout << "TEMP"; // check for variable
               cout << r << endl;
               n++; // increase variable count for storage
               cout << "ST  TEMP" << n << endl;
               stack.push(n); // store result
               break;
            case '-':
               r = stack.top(); // get left and right for equation
               stack.pop();
               l = stack.top();
               stack.pop();
               cout << "LD  "; // load left side
               if (isdigit(l))
                  cout << "TEMP"; // check for variable
               cout << l << endl;
               cout << "SB  "; // operate with right side
               if (isdigit(r))
                  cout << "TEMP"; // check for variable
               cout << r << endl;
               n++; // increase variable count for storage
               cout << "ST  TEMP" << n << endl;
               stack.push(n); // store result
               break;
            default:
               stack.push(p.at(j));
               break;
         }
      }
      while (!stack.empty()) // pop remaining items off stack
      {
         stack.pop();
      }
      cout << endl;
   }
}

// Class Definitions
/**********************************************************************
 * Default constructor. Sets up an array for 100 items
 **********************************************************************/
template <typename StackElement>
   Stack<StackElement>::Stack(int size)
{
   myTop = 0;
   maxSize = size;
   stackItems = new StackElement [size];
}
 
/***********************************************************************
 * Copy constructor. Will do a deep copy of the elements
 **********************************************************************/
template <typename StackElement>
   Stack<StackElement>::Stack(const Stack<StackElement> &aStack)
{
   maxSize = aStack.maxSize;
   myTop = aStack.myTop;
   stackItems = new int [aStack.maxSize];

   for (int i = 0; i < maxSize; i++) // fill array
      stackItems[i] = aStack.stackItems[i];
}
 
/**********************************************************************
 * Destructor to return allocated memory
 **********************************************************************/
template <typename StackElement>
   Stack<StackElement>::~Stack()
{
   myTop = 0;
   maxSize = 0;
   delete [] stackItems;
}

/**********************************************************************
 * Returns current item on top of stack
 **********************************************************************/
template <typename StackElement>
   StackElement Stack<StackElement>::top(void)
{
   return stackItems[myTop - 1]; // get last item put on
}
 
/**********************************************************************
 * Puts a new item on top of the stack
 **********************************************************************/
template <typename StackElement>
   void Stack<StackElement>::push(StackElement item)
{
   if (!full())
   {
      stackItems[myTop] = item;
      myTop++;
   }
   else
   {
      cout << "ERROR: Stack Overflow\n";
      exit(1);
   }
}
 
/**********************************************************************
 * Removes to item from stack
 **********************************************************************/
template <typename StackElement>
   void Stack<StackElement>::pop(void)
{
   if (!empty())
      myTop--;
   else
   {
      cout << "ERROR: Stack Underflow\n";
      exit(1);
   }
}
 
/**********************************************************************
 * Returns true if stack is empty
 **********************************************************************/
template <typename StackElement>
   bool Stack<StackElement>::empty(void)
{
   return (myTop == 0);
}
 
/**********************************************************************
 * Returns true if stack is full
 **********************************************************************/
template <typename StackElement>
   bool Stack<StackElement>::full(void)
{
   return (myTop >= maxSize);
}
 
/**********************************************************************
 * Assignment operator for stack class
 **********************************************************************/
template <typename StackElement>
   Stack<StackElement>& Stack<StackElement>::operator = 
   (const Stack<StackElement> &rtSide)
{
   if (maxSize != rtSide.maxSize) // if array isn't right size, reallocate
   {
      maxSize = rtSide.maxSize;
      delete [] stackItems;
      stackItems = new int [rtSide.maxSize];
   }

   myTop = rtSide.myTop;
   for (int i = 0; i < maxSize; i++) // fill array
      stackItems[i] = rtSide.stackItems[i];

   return *this;
}
