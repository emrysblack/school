// Test for matricies
#include <iostream>
using namespace std;

// Main
int main()
{
   int matrix1[5][5];
   int matrix2[5][5];

   //fill
    for (int i = 0; i < 5; i++)
   {
      for (int j = 0; j < 5; j++)
      {
         matrix1[i][j] = j;
         matrix2[i][j] = i;
      }
   }

   // display
    cout << "Matrix 1\n";
   for (int i = 0; i < 5; i++)
   {
      for (int j = 0; j < 5; j++)
      {
         cout << matrix1[i][j] << " ";
      }
      cout << endl;
   }
   cout << endl;
   cout << "Matrix 2\n";
   for (int i = 0; i < 5; i++)
   {
      for (int j = 0; j < 5; j++)
      {
         cout << matrix2[i][j] << " ";
      }
      cout << endl;
   }
   
   return 0;
}
