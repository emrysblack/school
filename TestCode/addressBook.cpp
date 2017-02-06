// ercanbrack 165 assignment address book
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

// Contact class
class Contact
{
   public:
      Contact(string pName = "", string pAddress = "", string pCity = "",
              string pState = "", string pZip = "", string pPhone = "");
      void setName(string pName){ name = pName;};
      void setAddress(string pAddress){address = pAddress;};
      void setCity(string pCity){city = pCity;};
      void setState(string pState){state = pState;};
      void setZip(string pZip){zip = pZip;};
      void setPhone(string pPhone){phone = pPhone;};
      string getName(){ return name;};
      string getAddress(){return address;};
      string getCity(){return city;};
      string getState(){return state;};
      string getZip(){return zip;};
      string getPhone(){return phone;};
      void prompt();
      void display();
   private:
      string name;
      string address;
      string city;
      string state;
      string zip;
      string phone;
};

/*********************************************************************
 * opens file and reads in a list of contacts
 *********************************************************************/
void readContacts(Contact contacts[])
{
   ifstream fin("/home/ercanbracks/cs165-examples/assign06/contactlist.txt");
   if (fin.fail())
   {
      cout << "ERROR: could not open file\n";
      return;
   }
   string name;
   string address;
   string city;
   string state;
   string zip;
   string phone;
   for (int i = 0; i < 5; i++)
   {
      getline (fin ,name);
      getline (fin, address);
      getline (fin, city);
      getline (fin, state);
      getline (fin, zip);
      getline (fin, phone);
      contacts[i].setName(name);
      contacts[i].setAddress(address);
      contacts[i].setCity(city);
      contacts[i].setState(state);
      contacts[i].setZip(zip);
      contacts[i].setPhone(phone);
   }
   fin.close();
}

/*********************************************************************
 * prompts for a number and calls display will keep re-prompting until  
 * user enters a q for quit
 *********************************************************************/
int main()
{
   Contact instruct;
   Contact student;
   Contact contacts[5];
   instruct.setName("Brother Ercanbrack");
   instruct.setAddress("AUS 217");
   instruct.setCity("Rexburg");
   instruct.setState("ID");
   instruct.setZip("83460");
   instruct.setPhone("496-7606");
   cout << endl;
   student.prompt();
   readContacts(contacts);
   instruct.display();
   student.display();
   for (int i = 0; i < 5; i++)
   {
      contacts[i].display();
   }
   return 0;
}

/*********************************************************************
 * constructor
 *********************************************************************/
Contact::Contact(string pName, string pAddress, string pCity,
                 string pState, string pZip, string pPhone)
{
   name = pName;
   address = pAddress;
   city = pCity;
   state = pState;
   zip = pZip;
   phone = pPhone;
}

/*********************************************************************
 * prompts for a contact
 *********************************************************************/
void Contact::prompt()
{
   cout << "Name: ";
   getline (cin ,name);
   cout << "Address: ";
   getline (cin, address);
   cout << "City: ";
   getline (cin, city);
   cout << "State: ";
   getline (cin, state);
   cout << "Zip: ";
   getline (cin, zip);
   cout << "Phone: ";
   getline (cin, phone);
}

/*********************************************************************
 * displays contact in format
 *********************************************************************/
void Contact::display()
{
   cout << endl << setw(5) << " " << name << endl;
   cout << setw(5) << " " << address << endl;
   cout << setw(5) << " " << city << ", " << state << "  " << zip << endl;
   cout << setw(5) << " " << phone << endl;
}
