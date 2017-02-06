/***********************************************************************
* Program:
*    Lesson 04, Memory Injection
*    Brother Smithb, CS470
* Author:
*    Brady Field
* Summary: 
*    This program is designed to illustrate weaknesses in the stack, 
*    heap, and other things
************************************************************************/

#include <iostream>
using namespace std;


void partOne();    // Find the address of the stack, heap, and code segments
void partTwo();    // Manipulate the stack to find a weakness
void partThree();  // Demonstrate a variety of vulnerabilities

/* vulnerable functions*/
void stackVulnerability(int data[], int size);
void heapVulnerability(int data[], int size);
void arrayVulnerability(int i);
void arcVulnerability(int data[], int size);

/* exploit functions */
void stackExploit();
void heapExploit();
void arrayExploit();
void arcExploit();
void stackMessage();
void safeMessage();
void arcMessage();

/******************************************************
 * MAIN
 * This function will only take you to one of the three parts
 * of Assignment 10
 *****************************************************/
int main()
{
   // prompt
   cout << "Please select an option:\n";
   cout << "  1.  Find the address\n";
   cout << "  2.  Manipulate the stack\n";
   cout << "  3.  Demonstrate vulnerabilities\n";
   cout << "> ";
   int selection;
   cin >> selection;

   // highly complex menu system
   switch (selection)
   {
      case 1:
         partOne();
         break;
      case 2:
         partTwo();
         break;
      case 3:
         partThree();
         break;
      default:
         cout << "Unknown option\n";
         return 1;
   }

   return 0;
}

/**************************************************************
 **************************************************************
 **************************** PART 1 **************************
 **************************************************************
 **************************************************************/

/**********************************************
 * Part 1
 *
 * Find the address of the stack, heap, and code.
 * Note that it will be in a different location with
 * every execution
 **********************************************/
void partOne()
{   
   // stack stores local variables
   int age = 0;
   age = 28;
   cout << "Stack: " << &age << endl;
   
   // Heap stores dynamic variables
   int * num;
   num = new int [10];
   num[0] = 28;
   num[1] = 29;
   cout << "Heap: " << num << endl;
   delete [] num;
   
   // code section contains source code and global variables like cout
   cout << "Code: " << cout << endl;
   return;
}


/**************************************************************
 **************************************************************
 **************************** PART 2 **************************
 **************************************************************
 **************************************************************/

void fail(char grade);
void pass(char grade);


/**********************************************************************
 * All your code needs to exist in this function below the comment
 *********************************************************************/
void readStack()
{
   int number;
   char text[16];
   
   ////////////////////////////////////////////////
   // put your magic code between here...
   int * num = &number;
   int i;
   for(i = 0; (void *)(*(num + i)) != (void *)fail; i++);
   *(num + i) = (long int)&pass; // change found fail to pass
   // number offset changes depending on variables added or taken away
   char * j = (char *)(num + 21);
   j--; // needs to back up by one address, not 4 so use pointer--
   // make sure we are in the right place
   if (*j == 'B')
      *j = 'A';
   else
      cout << "Houston we have a problem\n";
   number = *(num + 28);
   i = 0;
   for (char * p = (char *)(num + 21); *p; p++, i++)
   {
      text[i] = *p;
      text[i + 1] = '\0';
   }
   // ... and here
   ////////////////////////////////////////////////

   // output the goods
   cout << "\tnumber: "
        << number
        << endl;
   cout << "\ttext:   "
        << text
        << endl;
   return;
}

/*******************************************************************
 * Part 2
 *
 * This function contains the data that you are trying to manipulate.
 * Please don't modify partTwo() in any way
 ********************************************************************/
void partTwo()
{
   int   number;   // first local variable that you need to read
   char  text[16]; // second

   char  letterGrade;
   void (*pointerFunction)(char);

   // compilers are annoying.
   // If we don't get the address of these two variables, our
   // compiler will optimize them away and they will not appear
   // on the stack.  To get around this, I use the address-of
   // operator which forces the compiler to put them in the stack.
   &letterGrade;
   &pointerFunction;

   // get the values
   cout << "number: ";
   cin  >> number;
   cout << "text:   ";
   cin  >> text;


   // Call the function and display the results.
   pointerFunction = fail;
   letterGrade = 'B';
   readStack();            // vulnerability is here 
   (*pointerFunction)(letterGrade);

   return;
}


/**********************************************************************
 * The failure case. Don't touch this function
 *********************************************************************/
void fail(char grade)
{
   cout << "\tI am sorry, but you got a 'C'\n";
}

/**********************************************************************
 * I think you would really rather call this function.  This
 * is read-only also
 *********************************************************************/
void pass(char grade)
{
   cout << "\tGood job, you got a(n) '" << grade << "'\n";
}


/**************************************************************
 **************************************************************
 **************************** PART 3 **************************
 **************************************************************
 **************************************************************/


/*************************************
 * Part 3
 *
 * partThree() will call four functions to
 * demonstrate Stack, Heap, ArrayIndex, and Arc
 * vulnerabilities.  You should
 *   * Write the functions with code defects
 *     that represent the various vulnerabilities
 *   * Create input that will cause the vulnerabilities
 *     to be exploited
 *   * Create a simple menu system similar to main()
 *     so the user can witness the vulnerability
 *     of his choice
 *************************************/
void partThree()
{ 
   cout << "  1. Stack smashing\n"
        << "  2. Heap spraying\n"
        << "  3. Array index\n"
        << "  4. Arc vulnerability\n"
        << "> ";

   int select;
   cin >> select;

   switch (select)
   {
      case 1:
         stackExploit();
         break;
      case 2:
         heapExploit();
         break;
      case 3:
         arrayExploit();
         break;
      case 4:
         arcExploit();
         break;
      default:
         cout << "Unknown option " << select << endl;
   }
   return;
}

void stackVulnerability(int data[], int size)
{
   int myData[5];
   for (int i = 0; i < size; i++)
   {
      myData[i] = data[i];
   }
}

void heapVulnerability(int data[], int size)
{
   int * myData = new int[5];
   int * myOtherData = new int[5];
   // initialize
   for (int i = 0; i < 5; i++)
   {
      myData[i] = 1;
      myOtherData[i] = 2;
   }
   // copy data
   for (int i = 0; i < size; i++)
   {
      myData[i] = data[i];
   }
   // display
   cout << "myData: ";
   for (int i = 0; i < 5; i++)
   {
      cout << myData[i] << " ";
   }
   // oops what happened to our second set of numbers? hehehe
   cout << "\nmyOtherData: ";
   for (int i = 0; i < 5; i++)
   {
      cout << myOtherData[i] << " ";
   }
   cout << endl;
   cout << "Data is now corrupt, get ready to crash...incoming...\n";
   // second buffer must be released first according to textbook
   delete [] myOtherData;
   delete [] myData;
}

void arrayVulnerability(int i)
{
   string messages [] = {"one", "two", "three", "four", "five"};
   string secret = "Shh, it's a secret!";
   cout << "Requested item: "<< messages[i] << endl;
}

void arcVulnerability(int data[], int size)
{
   void (*p)(void) = &safeMessage;
   
   int myData[5];
   for (int i = 0; i < size; i++)
   {
      myData[i] = data[i];
   }
  
   (*p)();
}

void stackExploit()
{
   cout << "Start stack exploit\n";
   int data [] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, (long int) &stackMessage};
   int size = sizeof(data)/sizeof(data[0]);
   stackVulnerability(data, size);
   cout << "stackExploitaddr: " << (void *)stackExploit << endl;
   
   cout << "Finish stack exploit - failed\n";
}

void heapExploit()
{
   int data [] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
   int size = sizeof(data)/sizeof(data[0]);
   heapVulnerability(data, size);
}

void arrayExploit()
{
   cout << "Lets look at a message that's supposed to be a secret...\n";
   arrayVulnerability(6);
}

void arcExploit()
{
   int data [] = {0, 1, 2, 3, 4, 5, 6, 7, (long int) &arcMessage};
   int size = sizeof(data)/sizeof(data[0]);
   arcVulnerability(data, size);
}

void stackMessage()
{
   cout << "I claim the return of this function in the name of Spain!\n";
   cout << "This program will self-destruct in 3...2...1...\n";
}

void safeMessage()
{
   cout << "You are safe!\n";
}
void arcMessage()
{
   cout << "How did I get over here???\n";
}
