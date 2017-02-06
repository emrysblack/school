/***********************************************************************
* Program:
*    Lab Final Project
*    Brother Jones, CS 345
* Author:
*    A former BYU-Idaho student
* Summary:
*    This program demonstrates the use of threads to perform matrix
*  multiplication.  By using the time command from the terminal, I was
*  able to obtain casual measurements on the effects different numbers
*  of threads have on the running time of a program on single-processor
*  and multiprocessor machines.
************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <bits/pthreadtypes.h>
#include <time.h>
#include <semaphore.h>

#define INDEX(horizontal_value, vertical_value, width) ((horizontal_value) + ((vertical_value) * (width)))

int* MATRIX_A;
int MATRIX_A_WIDTH;
int MATRIX_A_HEIGHT;

int* MATRIX_B;
int MATRIX_B_WIDTH;
int MATRIX_B_HEIGHT;

int* MATRIX_C;
int MATRIX_C_WIDTH;
int MATRIX_C_HEIGHT;

int num_threads;

//Print the contents of a given integer array, formatted as though it were a
//width by height matrix.  Calls to this function are currently commented out,
//but I have included it so that you may doublecheck the accuracy of my matrix
//multiplication (if desired).
void dump_matrix(int* matrix, int width, int height) 
{
   int x;
   int num_elements = width * height;
   
   printf("Dumping %i x %i matrix: %x",width, height, matrix);
   
   for (x = 0; x < num_elements; x++) 
   {
      if (x % width == 0) printf("\n");
      printf ("  %i  ", matrix[x]);      
   }
   
   printf("\n");
}

//Returns a reference to an integer array of the requested width and height,
//which has been filled with random numbers.  Also, takes care of allocating
//memory for that integer array.
int* create_matrix(int width, int height) 
{
   int x;
   int num_elements = width * height;
   int* matrix = malloc(num_elements * sizeof(int));
   for (x = 0; x < num_elements; x++) 
   {
      matrix[x] = rand() % 100;
   }
   return matrix;
}

//Each thread created calls this function.  Each Xth of Y threads is
//responsible for calculating every Yth row.  In other words, in a
//10 x 10 matrix, thread number 1 of 3 will calculate rows #1, 4, 7, 10;
//thread number 2 of 3 will calculate rows #2, 5, 8; and thread number
// 3 of 3 will calculate rows #3, 6, 9.
//
//I chose to assign rows to a thread, instead of creating a pool of
//tasks, because each row will require (almost) exactly the same
//amount of work as any other row, so we can be confident that we
//are dividing the work evenly without spending extra processing
//time on complex scheduling routines.
void* worker(void* pointer) 
{
   int thread_num = * (int *) pointer;
   int row = thread_num;
   int col; 
   int x;
   int total;
   int matrix_a_pos;
   int matrix_b_pos;
      
   // printf("worker thread #%i created\n", thread_num);
   
   while (row < MATRIX_A_HEIGHT) 
   {
      for (col = 0; col < MATRIX_A_WIDTH; col++) 
      {
         int matrix_a_pos = INDEX(0, col, MATRIX_A_WIDTH);
         int matrix_b_pos = INDEX(row, 0, MATRIX_B_WIDTH);
         total = 0;
         for (x = 0; x < MATRIX_A_WIDTH; x++) 
         {
            total += MATRIX_A[matrix_a_pos] * MATRIX_B[matrix_b_pos];
            matrix_a_pos += 1;
            matrix_b_pos += MATRIX_B_WIDTH;
         }
         MATRIX_C[INDEX(row, col, MATRIX_C_WIDTH)] = total;
      }
      row += num_threads;
   }
   
   // printf("worker thread #%i exiting\n", thread_num);
   
   free (pointer);
}

int main(int num_args, char* args[]) 
{
   if (num_args != 6) 
   {
      printf("Usage: matrixMult <Matrix A Height> <Matrix A Width> <Matrix B Height> <Matrix B Width> <# threads>\n");
      exit(0);
   }
   
   //convert the argument from a string to a number   
   MATRIX_A_HEIGHT = atoi(args[1]);
   MATRIX_A_WIDTH = atoi(args[2]);
   MATRIX_B_HEIGHT = atoi(args[3]);
   MATRIX_B_WIDTH = atoi(args[4]);   
   num_threads = atoi(args[5]);
   
   //Doublecheck the size of the matricies
   if (MATRIX_A_WIDTH != MATRIX_B_HEIGHT) 
   {
      printf("By definition of matrix multiplication, Matrix A Width must equal Matrix B Height\n");
      exit(0);
   }
   
   //fill the first and second matrix with random integers.   
   MATRIX_A = create_matrix(MATRIX_A_WIDTH, MATRIX_A_HEIGHT);
   MATRIX_B = create_matrix(MATRIX_B_WIDTH, MATRIX_B_HEIGHT);
   
   //prepare matrix C to recieve the results of the multiplication
   MATRIX_C_HEIGHT = MATRIX_A_HEIGHT;
   MATRIX_C_WIDTH = MATRIX_B_WIDTH;   
   MATRIX_C = malloc(MATRIX_C_WIDTH * MATRIX_C_HEIGHT * sizeof(int));   
   
   //Create and start the worker threads
   int x;
   int *pointer;
   pthread_t threads[num_threads]; 
   for (x = 0; x < num_threads; x++) 
   {
      pointer = malloc(sizeof(int));
      *pointer = x;
      pthread_create( &threads[x], 
                      NULL,    //No special arguments for the thread type
                      worker,  //have the thread call the worker() function
                      pointer  //Pass a reference to the variable 
                               //holding that threads number
                      );   
   }
   
   //Stall the main program until all of the threads have finished executing.
   for (x = 0; x < num_threads; x++) 
   {
      pthread_join(threads[x], NULL);   
   }
   
   //You may optionally un-comment this section to check the correctness of the
   //matrix multiplication    
   //
   //dump_matrix(MATRIX_A, MATRIX_A_WIDTH, MATRIX_A_HEIGHT);
   //dump_matrix(MATRIX_B, MATRIX_B_WIDTH, MATRIX_B_HEIGHT);
   //dump_matrix(MATRIX_C, MATRIX_C_WIDTH, MATRIX_C_HEIGHT);

   //free the memory allocated by create_matrix   
   free(MATRIX_A);
   free(MATRIX_B);
   free(MATRIX_C);

   return 0;
}

