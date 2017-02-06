/***********************************************************************
* Program:
*    Example 3.2: Bell-LaPadula 
* Author:
*    Br.  Helfrich
* Summary: 
*    This example is meant to demonstrate how to implement Bell-LaPadula
*    access control in a simple system.
************************************************************************/

#include <iostream>    // for CIN, COUT
#include <string>      // for STRING
#include <map>         // for VECTOR: a collection of Nodes
#include <cassert>     // because I am paranoid
using namespace std;

// levels of secrecy
enum Control { PUBLIC, CONFIDENTIAL, SECRET, TOP_SECRET};

/*****************************************
 * NODE
 * One data item to be protected
 *****************************************/
struct Node
{
   string  data;      // the data that is protected
   Control control;   // the level of access required to view the data
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
   
   // fetch the address corresponding to key, it could be confidential
   string get(const string & key, const Control & controlSubject) const;

   // change the address corresponding to key, there might be integrity issues
   void set(const string & key, const string & address);

private:

   // determine if we are legal
   bool securityCondition(const Control & controlAsset,
                          const Control & controlSubject) const;

   
   map <string, Node> addresses;
};

/********************************************
 * ADDRESSES : constructor
 * Just fill our map with address data
 ********************************************/
Addresses :: Addresses()
{
   Node node;

   // top secret data
   node.control = TOP_SECRET;
   node.data = "Bronson Canyon, 3200 Canyon Dr., Los Angeles, CA 90068";
   addresses[string("BatCave")] = node;   
   
   // secret data
   node.control = SECRET;
   node.data = "platform 9 3/4, Kings Cross Station, London";
   addresses[string("Hogwarts")] = node;   

   // confidential data
   node.control = CONFIDENTIAL;

   node.data = "4059 Mt Lee Dr. Hollywood, CA 90068";
   addresses[string("HollywoodSign")] = node;

   node.data = "626 Autumn Ct., Rexburg, ID";
   addresses[string("Br.Helfrich")] = node;   
      
   // public data
   node.control = PUBLIC;

   node.data = "1600 Pennsylvania Avenue, Washington DC";
   addresses[string("WhiteHouse")] = node;

   node.data = "11 Wall Street, New York, NY";
   addresses[string("NYSE")] = node;

   node.data = "2 Macquarie Street, Sydney";
   addresses[string("OperaHouse")] = node;

   node.data = "Buckingham Palace, London, England";
   addresses[string("King")] = node;
}

/****************************************************
 * ADDRESSES :: SECURITY CONDITION
 * Does the entity have access to the asset?
 ****************************************************/
bool Addresses :: securityCondition(const Control & controlAsset,
                                    const Control & controlSubject) const
{
   return controlSubject >= controlAsset;
}

/*********************************************
 * ADDRESSES :: GET
 * Fetch the address for a given location
 ********************************************/
string Addresses :: get(const string & key,
                        const Control & controlSubject) const
{
   // does the item exist?
   map <string, Node> :: const_iterator it = addresses.find(key);
   if (it == addresses.end())
      return string("Name not found");

   // protected by Bell-LaPadula
   if (securityCondition(it->second.control, controlSubject))
      return it->second.data;
   else
      return string("You don't have clearance for that!");
}

/***********************************************
 * ADDRESSES :: SET
 * change the address corresponding to key
 **********************************************/
void Addresses :: set(const string & key, const string & address)
{
   // protected by... noone!
   addresses[key].data = address;
}

/*********************************************
 * AUTHENTICATE
 ********************************************/
Control authenticate()
{
   string name;
   cout << "Name: ";
   cin  >> name;

   if (name == "Batman" || name == "God" || name == "ChuckNorris")
      return TOP_SECRET;

   if (name == "President" || name == "Professor")
      return SECRET;

   if (name == "Student" || name == "Parent")
      return CONFIDENTIAL;

   return PUBLIC;
}

/**********************************************************************
 * MAIN: Just a driver program to exercise our Bell-LaPadula access control
 ***********************************************************************/
int main()
{
   // fill up our secret data
   Addresses a;

   Control controlSubject = authenticate();

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
      cout << '\t' << a.get(key, controlSubject) << endl;

      // change the contents
      string data;
      cout << "  new data for " << key << ": ";
      getline(cin, data);
      if (data.size())
         a.set(key, data);
   }
   
   
   return 0;
}
