// breaking up is hard to do, mysteriousness
#include <iostream>
using namespace std;

void breakOne(int number, int numPieces, int pieces[])
{
   
   // count up and add the rest onto the last num
   int sum = 0;
   for (int i = 0; i < numPieces - 1; i++)
   {
      sum += i + 1;
      pieces[i] = i + 1;
   }
   pieces[numPieces - 1] = number - sum;
}

void breakTwo(int number, int numPieces, int pieces[])
{
	int average = number / numPieces;
	int sum = 0;
   // work from perfect increment combination and count down
   for (int i = 0; i < numPieces; i++)
   {
	   pieces[i] = numPieces - i;
	   sum += numPieces - i;
   }
   pieces[0] += number - sum; // add difference into first
}

void breakThree(int number, int numPieces, int pieces[])
{
   int average = number / numPieces;
   // work from average num and adjust
   for (int i = 0; i < numPieces; i++)
   {
      pieces[i] = average;
   }
   pieces[0] += number - average * numPieces; // add difference into first
   // adjust remaining values, j is max adjustment possible, counting down
   for (int i = 2, j = average - 1; i < numPieces; i+=2, j--)
   {
      pieces[i - 1] += j;
      pieces[i] -= j;
   }
   
}

void displayPieces(int numPieces, int pieces[])
{
   int sum = 0;
   for (int i = 0; i < numPieces; i++)
   {
      sum += pieces[i];
      cout << pieces[i] << " ";
   }
   cout << "= " << sum << endl;
}

int main ()
{
   int number;
   int numPieces;
   int * pieces;

   
   // get two numbers from the user
   cout << "Please enter numbers for breaking: ";
   cin >> number >> numPieces;

   pieces = new int[numPieces];

   // break up with three different algorithms
   cout << number << " broken up into " << numPieces
        << " different parts.\n";

   cout << "Algorithm 1: " << endl;
   breakOne(number, numPieces, pieces);
   displayPieces(numPieces, pieces);

   cout << "Algorithm 2: " << endl;
   breakTwo(number, numPieces, pieces);
   displayPieces(numPieces, pieces);

   cout << "Algorithm 3: " << endl;
   breakThree(number, numPieces, pieces);
   displayPieces(numPieces, pieces);
   
   delete [] pieces;
   
   return 0;
}
