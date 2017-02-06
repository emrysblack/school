// test for finding max position recursively

#include <iostream>
using namespace std;

int rCount, bCount = 0;

int maxPos(int nums[], int l, int r)
{
   if (l == r)
   {
      return l;
   }
   int mid = (l+r)/2;
   int left = maxPos(nums,l,mid);
   int right = maxPos(nums,mid+1,r);
   rCount++;
   return (nums[left] > nums[right] ? left : right);    
}

int maxBrute(int nums [], int length)
{
   int max = 0;
   for (int i = 1; i < length; i++)
   {    
      if (nums[max] < nums[i])
      {
         max = i;    
      }
      bCount++;
   }
   return max;
}

int main()
{
   //  int nums[] = {1,0,0,1,1};
   int nums[] = {62,17,73,22,61,14,49,35,63,2};
   int length = sizeof(nums)/sizeof(int);
   int pos = maxPos(nums,0, length - 1);
   cout << "Max value " << nums[pos] << " at position " << pos << endl;
   pos = maxBrute(nums, length);
   cout << "Max value " << nums[pos] << " at position " << pos << endl;
   cout << "Recursion checks: " << rCount
        << "\nvs.\n" <<"Brute force checks: " << bCount
        << endl;
   return 0;
}
