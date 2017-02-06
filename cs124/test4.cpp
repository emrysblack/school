/***********************************************************************
* Program:
*    Test 4, Secret Decode
*    Brother Helfrich, CS124
* Author:
*    Brady Field
* Summary: 
*    Decodes a message input in ASCII values
*
*    Estimated:  1.0 hrs   
*    Actual:     0.0 hrs
*      It was very simple
************************************************************************/

#include <iostream>
using namespace std;

/**********************************************************************
* prompts for numbers
***********************************************************************/
void getNumbers( int code[], int num)
{
   cout << "Please enter the message one number at a time.\n";
   for (int i = 0; i < num; i++)
   {
      cout << "# ";
      cin >> code[i];
   }
}

/**********************************************************************
* changes the numbers to letter values and stores them
***********************************************************************/
void decode(char *message, int code[], int num)
{
   int i;
   for (i = 0; i < num; i++)
   {
      message[i] = (char)code[i];
   }
   message[i] = '\0';
}

/**********************************************************************
* displays the message
***********************************************************************/
void display(char *message)
{
   cout << message << endl;
}

/**********************************************************************
* prompts for length of message, calls functions to get the values,
* decode the values, and then display the decoded message
***********************************************************************/
int main()
{
   int num;   

   cout << "How many letters are there in your message? ";
   cin >> num;

   // use dynamic arrays so as no to waste memory
   int *code = new int[num];
   char *message = new char[num +1];

   getNumbers(code, num);
   decode(message, code, num);

   // free unneeded space
   delete [] code;
   code = NULL;
   
   display(message);

   // free remaining space
   delete [] message;
   message = NULL;
   return 0;
}
