// ercanbrack 165 assignment 1 data types and casting
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

// person struct
struct Person
{
   string fName;
   string lName;
   string id;
   int record;
};

bool search(Person * list, int numRecords);
void sort(Person * list, int numRecords);
/*********************************************************************
 * prompts for a number and calls display will keep re-prompting until  
 * user enters a q for quit
 *********************************************************************/
int main()
{
   int num;
   string input;
   string file = "/home/cs165/ercanbracks/studentList.txt";
   Person * list;

   // open file
   ifstream fin(file.c_str());
   if (fin.fail())
   {
      cout << "ERROR: could not open file " << file << endl;
      return 1;
   }
   
   fin >> num;
   list = new Person[num];
   for(int i = 0; fin >> list[i].lName >> list[i].fName >> list[i].id; i++)
   {
      list[i].id = "(" + list[i].id + ")";
      list[i].record = i + 1;
   }
   
   fin.close();

   // sort list
   sort(list, num);
   
   // display header
   cout << "---------------------------------------------------------------\n"
        << "Binary Search Program - Search using last name (case sensitive)\n"
        << "---------------------------------------------------------------\n";

   // run search
   while (search(list, num));

   //cleanup and exit
   delete [] list;
   return 0;
}

/*********************************************************************
 * prompts for a number and calls display will keep re-prompting until  
 * user enters a q for quit
 *********************************************************************/
bool search(Person * list, int numRecords)
{
   string name;
   cout << "\nSearch for: ";
   cin >> name;

   if (name == "quit")
        return false;
   for (int i = 0; i < numRecords; i++)
   {
      if (name == list[i].lName)
      {
         cout << endl << setw(30) << left << list[i].lName + ", "
            + list[i].fName + " " + list[i].id
              << "Record Number: " << i + 1
              << endl;
         return true;
      }     
   }
   cout << endl << name << " is not found!\n";
   return true;
   
}

/*********************************************************************
 * prompts for a number and calls display will keep re-prompting until  
 * user enters a q for quit
 *********************************************************************/
void sort(Person * list, int numRecords)
{
   Person temp;
   for (int i = 0; i < numRecords - 1; i++)
   {
      if (list[i].lName > list[i + 1].lName)
      {
         temp = list[i];
         list[i] = list[i + 1];
         list[i + 1] = temp;
         i = -1;
      }
      else if (list[i].lName == list[i + 1].lName)
         if (list[i].fName > list[i + 1].fName)
         {
            temp = list[i];
            list[i] = list[i + 1];
            list[i + 1] = temp;
            i = -1;
         }
   }
   return;
}
