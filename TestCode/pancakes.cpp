// test for pancake flipping
#include <iostream>
#include <algorithm>    // std::next_permutation, std::sort
using namespace std;

class Pancake
{
public:
   Pancake() : size(0), burnt(false) {}
   Pancake(int s, bool b = false)
   {
      size = s;
      burnt = b;
   }
   int getSize() const { return size; }
   bool isBurnt() const { return burnt; }
   void setSize(int s) { size = s; }
   void setBurnt(bool b) { burnt = b; }
private:
   int size;
   bool burnt;
};

bool operator <(const Pancake & lhs, const Pancake & rhs)
{
   return lhs.getSize() < rhs.getSize();
}
bool operator >(const Pancake & lhs, const Pancake & rhs)
{
   return lhs.getSize() > rhs.getSize();
}
bool operator ==(const Pancake & lhs, const Pancake & rhs)
{
   return lhs.getSize() == rhs.getSize();
}
bool operator !=(const Pancake & lhs, const Pancake & rhs)
{
   return lhs.getSize() != rhs.getSize();
}

// returns true for sorted stack. If burnt is true, will work burnt pancake
// problem.
bool isSorted(const Pancake pancakes[], int size, bool burnt = false)
{
   for(int i = 0; i < size - 1; i++)
   {
      if (pancakes[i] > pancakes[i+1])
      {
         return false;
      }
      if (burnt) // check for burnt
      {
         if(pancakes[i].isBurnt() || pancakes[i + 1].isBurnt())
         {
            return false;
         }
      }
   }
   return true;
}

void flip(Pancake pancakes[], int pos)
{
   // flip pancakes and burnt sides above position
   Pancake temp;
   for (int i = 0; i <= pos / 2; i++)
   {
      temp = pancakes[pos - i];
      pancakes[pos - i] = pancakes[i];
      pancakes[pos - i].setBurnt(!pancakes[pos - i].isBurnt());
      pancakes[i] = temp;
      pancakes[i].setBurnt(!pancakes[i].isBurnt());
   }
}

void display(Pancake pancakes[], int size, bool burnt = false)
{
   for (int i = 0; i < size; i++)
   {
      cout << pancakes[i].getSize();
      if (burnt)
      {
         cout << (pancakes[i].isBurnt() ? " Burnt" : "");
      }
      cout << endl;
   }
}

// sorts and returns the number of flips
int sort(Pancake pancakes [], int size, bool burnt = false) 
{
   int flips = 0;
   int target = size - 1;
   int biggest = 0;
   while(!isSorted(pancakes, size, burnt))
   {
      for (int i = 0; i <= target; i++)
      {
         if (pancakes[biggest] < pancakes[i])
         {
            biggest = i;
         }
      }
      if(biggest == target) // seek to next unsorted pancake
      {
         target--;
         biggest = 0;
         continue;
      }
      if (biggest > 0)
      {
         flip(pancakes, biggest);
         flips++;
         // display(pancakes, size);
         // cout << endl;
      }
      if (isSorted(pancakes, size, burnt))
      {
         break;
      }
      flip(pancakes, target);
      flips++;
      target--;
      // display(pancakes, size);
      // cout << endl;
   }
   return flips;
}

int main()
{
   int n;
   Pancake * pancakes;
   int * order;
   // prompt for n
   cout << "How many pancakes would you like? ";
   cin >> n;

   pancakes = new Pancake[n];
   order = new int[n];
   
   // build pancakes
   for (int i = 0; i < n; i++)
   {
      order[i] = i + 1; 
      pancakes[i].setSize(i + 1);
      //   pancakes[i].setBurnt(i % 2);
   }
   // pancakes[0].setSize(3);
   // pancakes[1].setSize(1);
   // pancakes[2].setSize(5);
   // pancakes[3].setSize(4);
   // pancakes[4].setSize(2);
   //display(pancakes, n);
   //cout << endl;
   cout << "Expect worst case to be\n2n - 3\n2(" << n << ") - 3 = "
        << 2 * n - 3 << endl;
   int max = 0;
   int current = 0;
   do
   {
      for (int i = 0; i < n; i++)
      {
         cout << order[i] << " ";
         pancakes[i].setSize(order[i]);
         //   pancakes[i].setBurnt(i % 2);
      }
      cerr << " = ";
      //display(pancakes, n);
      current = sort(pancakes, n);
      cout << current << endl;
      if (current > max)
      {
         max = current;
      }
      
   } while (next_permutation(order,order+n) );
   cout << max << " flips worst case\n";
   //cout << sort(pancakes, n) << " flip(s)" << endl; 

   delete [] pancakes;
   delete [] order;
   
   return 0;
}
