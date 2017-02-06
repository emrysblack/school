/**********************************************************************
* Program:
*    Homework 256, Final Project 
*    Brother Twitchell, CS235
* Author:
*    Brady Field
* Summary: 
*    Parses gedcom file and displays data
***********************************************************************/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <list>
using namespace std;

/**********************************************************************
 * Class for individuals records
 **********************************************************************/
class I
{
   private:
      string firstName;
      string lastName;
      string birthdate;
      string id;
   public:
      I(string fName, string lName, string date, string num)
      {firstName = fName; lastName = lName; birthdate = date; id = num;};
      string getFirstName(void){return firstName;};
      string getLastName(void){return lastName;};
      string getBirthdate(void){return birthdate;};
      string getId(void){return id;};
      void setFirstName(string name){firstName = name;};
      void setLastName(string name){lastName = name;};
      void setBirthdate(string date){birthdate = date;};
      void setId(string num){id = num;};
};

/**********************************************************************
 * uses insertion sort to put individuals in list
 **********************************************************************/
void insert(I* ind, list < I >& names)
{
   if (!names.empty())
   {
      list < I > ::iterator right = names.begin();
      string compare1 = ind->getLastName();
      string compare2 = right->getLastName();
      bool done = false;
      while(!done and right != names.end())
      {
         //compare last names
         if (ind->getLastName() != right->getLastName())
         {
            // case one: missing last name
            if (compare1 == "")
            {
               done = true;
            }
            else
            {
               if (compare1 < compare2)
               {
                  done = true;
               }
               else
               {
                  right++;
                  compare1 = ind->getLastName();
                  if (right != names.end())
                     compare2 = right->getLastName();
               }

            }
         }
         // compare first names
         else if (ind->getFirstName() != right->getFirstName())
         {
            compare1 = ind->getFirstName();
            compare2 = right->getFirstName();
                        // case one: missing last name
            if (compare1 == "")
            {
               done = true;
            }
            else
            {
               if (compare1 < compare2)
               {
                  done = true;
               }
               else
               {
                  right++;
                  compare1 = ind->getFirstName();
                  if (right != names.end())
                     compare2 = right->getFirstName();
               }

            }
         }
         // compare birthday
         else
         {
            done = true;
         }
      }
      names.insert(right,*ind);
   }
   else
      names.push_back(*ind);
}

/**********************************************************************
 * Parses information
 **********************************************************************/
void parse(list < string > &record, list < I > &names)
{
   I* ind;
   istringstream istr(record.front());
   string in, id, firstName, lastName, birthdate;
   istr.ignore(1,'@');
   istr >> in;
   // individual record
   if (in[1] == 'I')
   {
      id = in;
      record.pop_front();
      istr.str(record.front());
      istr.clear();
      istr.ignore(1);
      istr >> in;
      // get name
      if (in == "NAME")
      {
         // load next line
         record.pop_front();
         istr.str(record.front());
         istr.clear();
         istr.ignore(1);
         istr >> in;
         if (in == "GIVN")
         {
            istr.ignore(1);
            getline(istr,in);
            firstName = in;
            record.pop_front();
            istr.str(record.front());
            istr.clear();
            istr.ignore(1);
            istr >> in;
         }
         if (in == "SURN")
         {
            istr.ignore(1);
            getline(istr,in);
            if (firstName != "")
               lastName = " ";
            lastName += in;
            record.pop_front();
            istr.str(record.front());
            istr.clear();
            istr.ignore(1);
            istr >> in;
         }
      }
      while (in != "BIRT" and !record.empty())
      {
         record.pop_front();
         if (!record.empty())
         {
            istr.str(record.front());
            istr.clear();
            istr.ignore(1);
            istr >> in;
         }
      }
      if (in == "BIRT")
      {
         record.pop_front();
         istr.str(record.front());
         istr.clear();
         istr.ignore(1);
         istr >> in;
         if (in == "DATE")
         {
            istr.clear();
            istr.ignore(1);
            getline(istr,in);
            birthdate = ", b. " + in;
         }
      }
      ind = new I (firstName, lastName, birthdate, id);
      insert(ind, names);
   }
   else if (in[1] == 'F')
   {
      // family record
   }
}

/**********************************************************************
 * Opens file and displays
 **********************************************************************/
int main(int argc, char** argv)
{
   ifstream fin;
   if (argc < 2)
      fin.open("cameron.ged");
   else
      fin.open(argv[1]);
   if (fin.fail())
      cout << "ERROR: could not open file " << argv[1] << endl;
   else
   {
      list < I > names;
      list < string > record;
      string input;
      getline(fin,input);
      while (!fin.eof())
      {
         if (input[0] == '0' and input[2] == '@')
         {
            // store record in list
            record.push_back(input);
            getline(fin,input);
            while (input [0] != '0')
            {
               record.push_back(input);
               getline(fin,input);
            }
            //send off to be parsed
            parse(record, names);
            if (!record.empty())
               record.clear();
         }
         else
            getline(fin,input);
      }
      fin.close();
      list < I > ::iterator name = names.begin();
      ofstream out("sorted.dat");
      for (;name != names.end();name++)
         out << name->getFirstName() << name->getLastName() << name->getBirthdate() << endl;
      out.close();
   }
   return 0;
}