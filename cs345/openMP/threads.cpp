/***********************************************************************
* Program:
*    Lab OpenMPmatrixMult 
*    Brother Jones, CS 345
* Author:
*    Brady Field
* Summary:
*    Does Matrix Multiplication using multiple threads with OpenMP
* Conclusions:
*    Wow. I really liked modifying this lab to use OpenMP instead of
*    using PThreads. It was nice to be able to reduce it into more
*    natural looking code. On top of that I got to get rid of those
*    nasty global variables! Yay! The only suggestion I have is maybe
*    a small rubric to point to what to look for in the finished product
*    (such as no global variables), since I had to think for a bit and
*    experiment to get this to happen since I wasn't sure it could/should
************************************************************************/
#include <iostream>
#include <iomanip>
#include <cstdlib>
using namespace std;

#define M 5 // number of rows in matrix A
#define K 6 // number of rows in matrix B -- number of columns in matrix A
#define N 8 // number of columns in matrix B

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
void mult(ThreadData pos, int A [M][K], int B [K][N], int C [M][N])
{
   int sum = 0;
   for (int i = 0; i < K; i++)
   {
      sum += A[pos.i][i] * B[i][pos.j];
   }
   C[pos.i][pos.j] = sum;
}

/***********************************************************************
* Displays the resulting matrix
* containing the calculations from the previous multiplication
************************************************************************/
void display(int C [M][N])
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
int main(int argc, char ** argv)
{
   // [rows][columns]
   int A [M][K] = { {1,4,3,7,9,1}, {2,5,4,8,6,3}, {3,6,5,8,2,3},
                    {3,8,8,1,4,1}, {1,5,4,5,7,9} };

   int B [K][N] = { {1,5,6,5,7,9,8,2}, {1,2,3,5,5,6,7,8}, {3,5,9,7,3,1,4,1},
                    {8,3,1,2,6,5,2,4}, {3,8,8,1,4,1,3,3}, {8,7,6,5,4,3,2,1} };
   int C [M][N]; // this is where the answer will be placed
   ThreadData pos[M][N];
   int threadct = 1;         /* number of threads to use */
   /* parse command-line arg for number of threads */
   if (argc > 1)
      threadct = atoi(argv[1]);
     
#ifdef _OPENMP
   cout << "OMP defined, threadct = " << threadct << endl;
#else
   cout << "OMP not defined" << endl;
#endif
   int i, j;
   #pragma omp parallel for num_threads(threadct) \
      shared(A, B, C) private (i, j)
   // launch calculations
   for (i = 0; i < M; i++)
   {
      for (j = 0; j < N; j++ )
      {
         pos[i][j].i = i;
         pos[i][j].j = j;
         mult(pos[i][j], A, B, C);
         usleep(5000);
      }
   }
   
   // display results
   display(C);
   return 0;
}
