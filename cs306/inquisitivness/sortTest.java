import java.util.Random;

public class sortTest
{
   // simple utility array copy so we can reuse our cases
   private static void copyList(int src[], int dest[], int size)
   {
      for (int i = 0; i < size; i++)
      {
         dest[i] = src[i];
      }
   }
   private static void bubbleSort(int unsorted[], int size)
   {
      boolean sorted = false;
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

   private static void insertionSort(int unsorted[], int size)
   {
      int i;
      int j;
      int temp;
      for (i = 1; i < size; i++)
      {
         temp = unsorted[i];
         for (j = i; j > 0 && temp < unsorted[j - 1]; j--)
         {
            unsorted[j] = unsorted[j - 1]; // shift
         }
         unsorted[j] = temp;
      }
   }
   private static void mergeSort(int arr[], int l, int r)
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
         int [] L = new int[n1];
         int [] R = new int[n2];
 
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
      }
   }

   // Bro Neff's quicksort
   private static void quickSort(int data[], int left, int right)
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

   public static void main(String[] args)
   {
      // enforce correct usage
      // for no argument default
      int size = (args.length > 0? Integer.parseInt(args[0]) : 60000);
      if (size <= 0)
      {
         System.out.println("Usage: a.out num\n e.g. a.out 1000\n");
         return;
      }

      Random rand = new Random();
      // set up various cases
      
      int [] randomList = new int[size];

      for (int i = 0; i < size; i++)
      {
         randomList[i] = rand.nextInt(size) + 1;
      }

      // backward (worst case in many algorithms)
      int [] backList = new int[size];
      for (int i = 0; i < size; i++)
      {
         backList[i] = size - i;
      }

      // already sorted
      int [] sortedList = new int[size];
      for (int i = 0; i < size; i++)
      {
         sortedList[i] = i;
      }
   
      // mostly sorted list
      int [] almostList = new int[size];
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

      int [] unsorted = new int[size];

      double start;
      double end;
      double timeRun;
      
      // n^2 sorts

      // bubble sort
      copyList(randomList, unsorted, size);
      start = System.nanoTime();
      bubbleSort(unsorted, size);
      end = System.nanoTime();
      timeRun = (end - start) / 1000000000.0;
      System.out.println("\nBubble Sort\n\nRandom list of " + size
                         + " items: " + String.format("%f", timeRun)
                         + " seconds");
      
      copyList(backList, unsorted, size);
      start = System.nanoTime();
      bubbleSort(unsorted, size);
      end = System.nanoTime();
      timeRun = (end - start) / 1000000000.0;
      System.out.println("Backword list of " + size
                         + " items: " + String.format("%f", timeRun)
                         + " seconds");

      copyList(sortedList, unsorted, size);
      start = System.nanoTime();
      bubbleSort(unsorted, size);
      end = System.nanoTime();
      timeRun = (end - start) / 1000000000.0;
      System.out.println("Sorted list of " + size
                         + " items: " + String.format("%f", timeRun)
                         + " seconds");

      copyList(almostList, unsorted, size);
      start = System.nanoTime();
      bubbleSort(unsorted, size);
      end = System.nanoTime();
      timeRun = (end - start) / 1000000000.0;
      System.out.println("Almost sorted list of " + size
                         + " items: " + String.format("%f", timeRun)
                         + " seconds");

      // insertion sort
   
      copyList(randomList, unsorted, size);
      start = System.nanoTime();
      insertionSort(unsorted, size);
      end = System.nanoTime();
      timeRun = (end - start) / 1000000000.0;
      System.out.println("\nInsertion Sort\n\nRandom list of " + size
                         + " items: " + String.format("%f", timeRun)
                         + " seconds");
      
      copyList(backList, unsorted, size);
      start = System.nanoTime();
      insertionSort(unsorted, size);
      end = System.nanoTime();
      timeRun = (end - start) / 1000000000.0;
      System.out.println("Backword list of " + size
                         + " items: " + String.format("%f", timeRun)
                         + " seconds");

      copyList(sortedList, unsorted, size);
      start = System.nanoTime();
      insertionSort(unsorted, size);
      end = System.nanoTime();
      timeRun = (end - start) / 1000000000.0;
      System.out.println("Sorted list of " + size
                         + " items: " + String.format("%f", timeRun)
                         + " seconds");

      copyList(almostList, unsorted, size);
      start = System.nanoTime();
      insertionSort(unsorted, size);
      end = System.nanoTime();
      timeRun = (end - start) / 1000000000.0;
      System.out.println("Almost sorted list of " + size
                         + " items: " + String.format("%f", timeRun)
                         + " seconds");
   
      // nlogn sorts

      // merge sort
      copyList(randomList, unsorted, size);
      start = System.nanoTime();
      mergeSort(unsorted, 0, size - 1);
      end = System.nanoTime();
      timeRun = (end - start) / 1000000000.0;
      System.out.println("\nMerge Sort\n\nRandom list of " + size
                         + " items: " + String.format("%f", timeRun)
                         + " seconds");

      copyList(backList, unsorted, size);
      start = System.nanoTime();
      mergeSort(unsorted, 0, size - 1);
      end = System.nanoTime();
      timeRun = (end - start) / 1000000000.0;
      System.out.println("Backword list of " + size
                         + " items: " + String.format("%f", timeRun)
                         + " seconds");

      copyList(sortedList, unsorted, size);
      start = System.nanoTime();
      mergeSort(unsorted, 0, size - 1);
      end = System.nanoTime();
      timeRun = (end - start) / 1000000000.0;
      System.out.println("Sorted list of " + size
                         + " items: " + String.format("%f", timeRun)
                         + " seconds");

      copyList(almostList, unsorted, size);
      start = System.nanoTime();
      mergeSort(unsorted, 0, size - 1);
      end = System.nanoTime();
      timeRun = (end - start) / 1000000000.0;
      System.out.println("Almost sorted list of " + size
                         + " items: " + String.format("%f", timeRun)
                         + " seconds");

      // quick sort
      copyList(randomList, unsorted, size);
      start = System.nanoTime();
      quickSort(unsorted, 0, size - 1);
      end = System.nanoTime();
      timeRun = (end - start) / 1000000000.0;
      System.out.println("\nQuick Sort\n\nRandom list of " + size
                         + " items: " + String.format("%f", timeRun)
                         + " seconds");

      copyList(backList, unsorted, size);
      start = System.nanoTime();
      quickSort(unsorted, 0, size - 1);
      end = System.nanoTime();
      timeRun = (end - start) / 1000000000.0;
      System.out.println("Backword list of " + size
                         + " items: " + String.format("%f", timeRun)
                         + " seconds");

      copyList(sortedList, unsorted, size);
      start = System.nanoTime();
      quickSort(unsorted, 0, size - 1);
      end = System.nanoTime();
      timeRun = (end - start) / 1000000000.0;
      System.out.println("Sorted list of " + size
                         + " items: " + String.format("%f", timeRun)
                         + " seconds");

      copyList(almostList, unsorted, size);
      start = System.nanoTime();
      quickSort(unsorted, 0, size - 1);
      end = System.nanoTime();
      timeRun = (end - start) / 1000000000.0;
      System.out.println("Almost sorted list of " + size
                         + " items: " + String.format("%f", timeRun)
                         + " seconds");
   }
}