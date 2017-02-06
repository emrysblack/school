/***********************************************************************
* Program:
*    Lab Threads  
*    Brother Jones, CS 345
* Author:
*    Brady Field
* Summary:
*    Does Matrix Multiplication using multiple threads
************************************************************************/
#include <iostream>
#include <iomanip>
#include <pthread.h>
using namespace std;

#define M 5 // number of rows in matrix A
#define K 6 // number of rows in matrix B -- number of columns in matrix A
#define N 8 // number of columns in matrix B

// [rows][columns]
int A [M][K] = { {1,4,3,7,9,1}, {2,5,4,8,6,3}, {3,6,5,8,2,3},
                 {3,8,8,1,4,1}, {1,5,4,5,7,9} };

int B [K][N] = { {1,5,6,5,7,9,8,2}, {1,2,3,5,5,6,7,8}, {3,5,9,7,3,1,4,1},
                 {8,3,1,2,6,5,2,4}, {3,8,8,1,4,1,3,3}, {8,7,6,5,4,3,2,1} };
int C [M][N]; // this is where the answer will be placed

/* structure for passing data to threads */
struct ThreadData
{
   int i; // row
   int j; // column
};

/***********************************************************************
* Takes a position and does matrix multiplication using
* the position as a starting point
************************************************************************/
void *mult(void * p)
{
   ThreadData * pos = (ThreadData *)p;
   int sum = 0;
   for (int i = 0; i < K; i++)
   {
      sum += A[pos->i][i] * B[i][pos->j];
   }
   C[pos->i][pos->j] = sum;

   pthread_exit(0);
}

/***********************************************************************
* Displays the resulting matrix
* containing the calculations from the previous multiplication
************************************************************************/
void display()
{
   cout << "The product of matrices A and B is:\n";
   for (int i = 0; i < M; i++)
   {
      for (int j = 0; j < N; j++ )
      {
         cout << setw(8) << C[i][j];
      }
      cout << endl;
   } 
}

/***********************************************************************
* Sets up threads to handle calculations, launches the threads,
* and joins them before displaying the end result
************************************************************************/
int main()
{
   // setup threads and arguments
   pthread_t thread [M][N];
   ThreadData pos[M][N];
   
   // launch calculations
   for (int i = 0; i < M; i++)
   {
      for (int j = 0; j < N; j++ )
      {
         pos[i][j].i = i;
         pos[i][j].j = j;
         pthread_create( &thread[i][j], NULL, mult, (void*) &pos[i][j]);
      }
   }
   
   // join threads
   for (int i = 0; i < M; i++)
   {
      for (int j = 0; j < N; j++ )
      {     
         pthread_join(thread[i][j], NULL);    
      }
   }

   // display results
   display();
   return 0;
}
