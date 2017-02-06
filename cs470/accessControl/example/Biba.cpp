/***********************************************************************
* Program:
*    Example 3.2: Biba
* Author:
*    Br.  Helfrich
* Summary: 
*    This example is meant to demonstrate how to implement Biba
*    access control in a simple system.
************************************************************************/

#include <iostream>    // for CIN, COUT
#include <string>      // for STRING
#include <map>         // for VECTOR: a collection of Nodes
#include <cassert>     // because I am paranoid
using namespace std;

// Integrity level
enum IntegrityLevel { UNTRUSTED, PRELIMINARY, SECONDARY, PRIMARY };

/*****************************************
 * NODE
 * One data item to be protected
 *****************************************/
struct Node
{
   string         data;      // the data that is protected
   IntegrityLevel il;        // integrity level to be mainted for "data"
};

/*********************************************
 * ADDRESSES
 * A collection of addresses
 ********************************************/
class Addresses
{
public:
   // initialize the data
   Addresses();

   // display address list, this is not confidential information
   friend ostream & operator << (ostream & out, const Addresses & rhs)
   {
      map <string, Node> :: const_iterator it;
      for (it = rhs.addresses.begin(); it != rhs.addresses.end(); ++it)
         out << '\t' << it->first << endl;
      return out;
   }
   
   // fetch the address corresponding to key,
   //  there might be confidentialiy issues
   string get(const string & key) const;

   // change the address corresponding to key, there might be integrity issues
   void set(const string & key,
            const string & address,
            const IntegrityLevel & ilSubject);

private:

   // determine if we are legal
   bool securityCondition(const IntegrityLevel & ilObject,
                          const IntegrityLevel & ilSubject) const;

   
   map <string, Node> addresses;
};

/********************************************
 * ADDRESSES : constructor
 * Just fill our map with address data
 ********************************************/
Addresses :: Addresses()
{
   Node node;

   // PRIMARY
   node.il = PRIMARY;

   node.data = "1600 Pennsylvania Avenue, Washington DC";
   addresses[string("WhiteHouse")] = node;

   node.data = "Buckingham Palace, London, England";
   addresses[string("King")] = node;

   // SECONDARY
   node.il = SECONDARY;

   node.data = "11 Wall Street, New York, NY";
   addresses[string("NYSE")] = node;

   node.data = "2 Macquarie Street, Sydney";
   addresses[string("OperaHouse")] = node;


   // PRELIMINARY
   node.il = PRELIMINARY;

   node.data = "4059 Mt Lee Dr. Hollywood, CA 90068";
   addresses[string("HollywoodSign")] = node;

   node.data = "626 Autumn Ct., Rexburg, ID";
   addresses[string("Br.Helfrich")] = node;   
      
   // UNTRUSTED
   node.il = UNTRUSTED;
   
   node.data = "Bronson Canyon, 3200 Canyon Dr., Los Angeles, CA 90068";
   addresses[string("BatCave")] = node;   
   
   node.data = "platform 9 3/4, Kings Cross Station, London";
   addresses[string("Hogwarts")] = node;   

}

/****************************************************
 * ADDRESSES :: SECURITY CONDITION
 * Does the entity have access to the asset?
 ****************************************************/
bool Addresses :: securityCondition(const IntegrityLevel & ilObject,
                                    const IntegrityLevel & ilSubject) const
{
   return ilObject >= ilSubject;
}

/*********************************************
 * ADDRESSES :: GET
 * Fetch the address for a given location
 ********************************************/
string Addresses :: get(const string & key) const
{
   // does the item exist?
   map <string, Node> :: const_iterator it = addresses.find(key);
   if (it == addresses.end())
      return string("Name not found");

   // protected by... noone!
   return it->second.data;
}

/***********************************************
 * ADDRESSES :: SET
 * change the address corresponding to key
 **********************************************/
void Addresses :: set(const string & key,
                      const string & address,
                      const IntegrityLevel & ilSubject)
{
   // protected by Biba
   if (securityCondition(addresses[key].il, ilSubject))
      addresses[key].data = address;
   else
      cout << "You do not have permission to make this change.\n";
}

/*********************************************
 * AUTHENTICATE
 ********************************************/
IntegrityLevel authenticate()
{
   string name;
   cout << "Name: ";
   cin  >> name;

   if (name == "God" || name == "ChuckNorris")
      return PRIMARY;

   if (name == "President" || name == "Professor")
      return SECONDARY;

   if (name == "Batman" || name == "Parent" || name == "Student")
      return PRELIMINARY;
   
   return UNTRUSTED;
}

/**********************************************************************
 * MAIN: Just a driver program to exercise our Bell-LaPadula access control
 ***********************************************************************/
int main()
{
   // fill up our secret data
   Addresses a;

   IntegrityLevel ilSubject = authenticate();

   cout << "What address do you want?\n"
        << a;
   for (;;)
   {
      // select an item...
      string key;
      cout << "> ";
      cin  >> key;
      cin.ignore();

      // display the contents
      cout << '\t' << a.get(key) << endl;

      // change the contents
      string data;
      cout << "  new data for " << key << ": ";
      getline(cin, data);
      if (data.size())
         a.set(key, data, ilSubject);
   }
   
   
   return 0;
}
