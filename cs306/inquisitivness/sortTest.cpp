// comparison of a few sorts
#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

// simple utility array copy so we can reuse our cases
void copyList(int src[], int dest[], const int size)
{
   for (int i = 0; i < size; i++)
   {
      dest[i] = src[i];
   }
}

void bubbleSort(int unsorted[], const int size)
{
   bool sorted = false;
   int temp;
   while (!sorted)
   {
      sorted = true;
      for (int i = 0; i < size - 1; i++)
      {
         if (unsorted[i] > unsorted[i + 1])
         {
            // swap
            temp = unsorted[i];
            unsorted[i] = unsorted[i + 1];
            unsorted[i + 1] = temp;
            sorted = false;
         }
      }
   }
}

void insertionSort(int unsorted[], const int size)
{
   for (int i = 1, j = 1; i < size; i++)
   {
      int temp = unsorted[i];
      for (j = i; j > 0 && temp < unsorted[j - 1]; j--)
      {
         unsorted[j] = unsorted[j - 1]; // shift
      }
      unsorted[j] = temp;
   }
}

/**********************************************************************
 * sorts with merge sort - adapted from geeksforgeeks.org merge sort
 * example. My CS235 sort was broken and was slower than bubble...
 **********************************************************************/
void mergeSort(int arr[], const int l, const int r)
{
   if (l < r)
    {
        // Same as (l+r)/2, but avoids overflow for
        // large l and h
        int m = l+(r-l)/2;
 
        // Sort first and second halves
        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);
 
        //     merge(arr, l, m, r);

        int i, j, k;
        int n1 = m - l + 1;
        int n2 =  r - m;
 
        /* create temp arrays */
        int * L = new int[n1];
        int * R = new int[n2];
 
        /* Copy data to temp arrays L[] and R[] */
        for (i = 0; i < n1; i++)
           L[i] = arr[l + i];
        for (j = 0; j < n2; j++)
           R[j] = arr[m + 1+ j];
 
        /* Merge the temp arrays back into arr[l..r]*/
        i = 0; // Initial index of first subarray
        j = 0; // Initial index of second subarray
        k = l; // Initial index of merged subarray
        while (i < n1 && j < n2)
        {
           if (L[i] <= R[j])
           {
              arr[k] = L[i];
              i++;
           }
           else
           {
              arr[k] = R[j];
              j++;
           }
           k++;
        }
 
        /* Copy the remaining elements of L[], if there
           are any */
        while (i < n1)
        {
           arr[k] = L[i];
           i++;
           k++;
        }
 
        /* Copy the remaining elements of R[], if there
           are any */
        while (j < n2)
        {
           arr[k] = R[j];
           j++;
           k++;
        }
        delete [] L;
        delete [] R;
    }
}

// Bro Neff's quicksort
void quickSort(int data[], int left, int right)
{
   int i;
   int j;
   int pivot;
   int temp;

   if (left <= right)
   {
      pivot = data[(left + right) / 2];

      i = left;
      j = right;
      do
      {
         while (data[i] < pivot)
         {
            i++;
         }
         while (pivot < data[j])
         {
            j--;
         }
         if (i <= j)
         {
            temp = data[i];
            data[i] = data[j];
            data[j] = temp;
            i++;
            j--;
         }
      } while (i < j);
      quickSort(data, left, j);
      quickSort(data, i, right);
   }
}

// functions for heap sort
void siftDown(int data[], int parent, int end) // fixes a heap
{
   int leftChild = parent * 2 + 1;
   int rightChild = leftChild + 1;
   int kid = leftChild;
   int temp;
   while (leftChild < end)
   {
      // find largest child
      if (rightChild < end)
         if (data[rightChild] > data[leftChild])
            kid = rightChild;

      // we are done if we found the proper position
      if (data[parent] >= data[kid])
         return;

      // swap values
      temp = data[parent];
      data[parent] = data[kid];
      data[kid] = temp;

      // move down
      parent = kid;
      leftChild = parent * 2 + 1;
      rightChild = leftChild + 1;
      kid = leftChild;
   }
}

void heapify(int data[], int size) // creates a heap
{
   int parent = (size - 1 - (size % 2 == 0)) / 2;
   while (parent >= 0)
   {
      siftDown(data, parent, size);
      parent--;
   }
}

void heapSort(int data[], int size) // sorts using a heap
{
   heapify(data, size);

   int temp;
   while (size > 1)
   {
      // swap first and last element
      temp = data[0];
      data[0] = data[size - 1];
      data[size - 1] = temp;
      siftDown(data, 0, --size);
   }
}

int main(int argc, char ** argv)
{
   // enforce correct usage
   stringstream ss;
   ss << (argc > 1? ((string)argv[1]) : "60000"); // for no argument default
   int size = 0;
   ss >> size;

   if (ss.fail() || size <= 0)
   {
      cout << "Usage: a.out num\n e.g. a.out 1000\n";
      return 1;
   }

   srand(time(NULL));
   clock_t start, end;
   double timeRun;
   // set up various cases
   
   // random or average case
   int * randomList = new int[size];
   for (int i = 0; i < size; i++)
   {
      randomList[i] = (int) ((float) rand() / RAND_MAX * size + 1);
   }

   // backward (worst case in many algorithms)
   int * backList = new int[size];
   for (int i = 0; i < size; i++)
   {
      backList[i] = size - i;
   }

   // already sorted
   int * sortedList = new int[size];
   for (int i = 0; i < size; i++)
   {
      sortedList[i] = i;
   }
   
   // mostly sorted list
   int * almostList = new int[size];
   for (int i = 0; i < size; i++)
   {
      if (i % 5 == 0)
      {
         almostList[i] = sortedList[size - 1 - i];
      }
      else
      {
         almostList[i] = sortedList[i];
      }
   }

   int * unsorted = new int[size];

   // n^2 sorts

   // bubble
   copyList(randomList, unsorted, size);
   start = clock();
   bubbleSort(unsorted, size);
   end = clock();
   timeRun = double(end - start) / CLOCKS_PER_SEC;
   cout << "\nBubble Sort\n\nRandom list of " << size
        << " items: " << timeRun << " seconds\n";
   copyList(backList, unsorted, size);
   start = clock();
   bubbleSort(unsorted, size);
   end = clock();
   timeRun = double(end - start) / CLOCKS_PER_SEC;
   cout << "Backword list of " << size
        << " items: " << timeRun << " seconds\n";

   copyList(sortedList, unsorted, size);
   start = clock();
   bubbleSort(unsorted, size);
   end = clock();
   timeRun = double(end - start) / CLOCKS_PER_SEC;
   cout << "Sorted list of " << size
        << " items: " << timeRun << " seconds\n";

   copyList(almostList, unsorted, size);
   start = clock();
   bubbleSort(unsorted, size);
   end = clock();
   timeRun = double(end - start) / CLOCKS_PER_SEC;
   cout << "Almost sorted list of " << size
        << " items: " << timeRun << " seconds\n";



   // insertion
   
   copyList(randomList, unsorted, size);
   start = clock();
   insertionSort(unsorted, size);
   end = clock();
   timeRun = double(end - start) / CLOCKS_PER_SEC;
   cout << "\nInsertion Sort\n\nRandom list of " << size
        << " items: " << timeRun << " seconds\n";
   copyList(backList, unsorted, size);
   start = clock();
   insertionSort(unsorted, size);
   end = clock();
   timeRun = double(end - start) / CLOCKS_PER_SEC;
   cout << "Backword list of " << size
        << " items: " << timeRun << " seconds\n";

   copyList(sortedList, unsorted, size);
   start = clock();
   insertionSort(unsorted, size);
   end = clock();
   timeRun = double(end - start) / CLOCKS_PER_SEC;
   cout << "Sorted list of " << size
        << " items: " << timeRun << " seconds\n";

   copyList(almostList, unsorted, size);
   start = clock();
   insertionSort(unsorted, size);
   end = clock();
   timeRun = double(end - start) / CLOCKS_PER_SEC;
   cout << "Almost sorted list of " << size
        << " items: " << timeRun << " seconds\n";

   
   // nlogn sorts

   // merge sort
   copyList(randomList, unsorted, size);
   start = clock();
   mergeSort(unsorted, 0, size - 1);
   end = clock();
   timeRun = double(end - start) / CLOCKS_PER_SEC;
   cout << "\nMerge Sort\n\nRandom list of " << size
        << " items: " << timeRun << " seconds\n";
   copyList(backList, unsorted, size);
   start = clock();
   mergeSort(unsorted, 0, size - 1);
   end = clock();
   timeRun = double(end - start) / CLOCKS_PER_SEC;
   cout << "Backword list of " << size
        << " items: " << timeRun << " seconds\n";

   copyList(sortedList, unsorted, size);
   start = clock();
   mergeSort(unsorted, 0, size - 1);
   end = clock();
   timeRun = double(end - start) / CLOCKS_PER_SEC;
   cout << "Sorted list of " << size
        << " items: " << timeRun << " seconds\n";

   copyList(almostList, unsorted, size);
   start = clock();
   mergeSort(unsorted, 0, size - 1);
   end = clock();
   timeRun = double(end - start) / CLOCKS_PER_SEC;
   cout << "Almost sorted list of " << size
        << " items: " << timeRun << " seconds\n";

   // quicksort
   copyList(randomList, unsorted, size);
   start = clock();
   quickSort(unsorted, 0, size - 1);
   end = clock();
   timeRun = double(end - start) / CLOCKS_PER_SEC;
   cout << "\nQuick Sort\n\nRandom list of " << size
        << " items: " << timeRun << " seconds\n";
   copyList(backList, unsorted, size);
   start = clock();
   quickSort(unsorted, 0, size - 1);
   end = clock();
   timeRun = double(end - start) / CLOCKS_PER_SEC;
   cout << "Backword list of " << size
        << " items: " << timeRun << " seconds\n";

   copyList(sortedList, unsorted, size);
   start = clock();
   quickSort(unsorted, 0, size - 1);
   end = clock();
   timeRun = double(end - start) / CLOCKS_PER_SEC;
   cout << "Sorted list of " << size
        << " items: " << timeRun << " seconds\n";

   copyList(almostList, unsorted, size);
   start = clock();
   quickSort(unsorted, 0, size - 1);
   end = clock();
   timeRun = double(end - start) / CLOCKS_PER_SEC;
   cout << "Almost sorted list of " << size
        << " items: " << timeRun << " seconds\n";

   // heap sort
   copyList(randomList, unsorted, size);
   start = clock();
   heapSort(unsorted, size);
   end = clock();
   timeRun = double(end - start) / CLOCKS_PER_SEC;
   cout << "\nHeap Sort\n\nRandom list of " << size
        << " items: " << timeRun << " seconds\n";
   copyList(backList, unsorted, size);
   start = clock();
   heapSort(unsorted, size);
   end = clock();
   timeRun = double(end - start) / CLOCKS_PER_SEC;
   cout << "Backword list of " << size
        << " items: " << timeRun << " seconds\n";

   copyList(sortedList, unsorted, size);
   start = clock();
   heapSort(unsorted, size);
   end = clock();
   timeRun = double(end - start) / CLOCKS_PER_SEC;
   cout << "Sorted list of " << size
        << " items: " << timeRun << " seconds\n";

   copyList(almostList, unsorted, size);
   start = clock();
   heapSort(unsorted, size);
   end = clock();
   timeRun = double(end - start) / CLOCKS_PER_SEC;
   cout << "Almost sorted list of " << size
        << " items: " << timeRun << " seconds\n";
   
   // free cases
   delete [] randomList;
   delete [] backList;
   delete [] sortedList;
   delete [] almostList;
   delete [] unsorted;
   
   return 0;
}
