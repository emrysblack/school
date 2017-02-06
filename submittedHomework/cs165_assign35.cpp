/***********************************************************************
* Program:
*    Assignment 35, pure virtual functions
*    Brother Boyer, CS165
* Author:
*    Brady Field
* Summary: 
*    This program will demonstrate abstract classes and pure virtual functions.
*    An abstract class (ValidNumber) will have two children: GPA and
*    Price.  Each will have unique display and validate functions.
*
*    Estimated:  1.0 hrs   
*    Actual:     1.0 hrs
*      having to put definitions in virtual functions that will never be called
************************************************************************/

#include <iostream>
using namespace std;

/***************************
 * pure virtual function
 ***************************/
class ValidNumber
{
public:
   void prompt(const char *sMessage);
   void get();
   virtual void display();
   virtual bool validate();
protected:
   float value;
};

/**************************
 * PRICE: one type of number
 **************************/
class Price : public ValidNumber
{
   void display();
   bool validate();
};

/**************************
 * GPA: another type of number
 **************************/
class GPA : public ValidNumber
{
   void display();
   bool validate();
};

/*********************************
 * Valid Number: PROMT
 *********************************/
void ValidNumber::prompt(const char *sMessage)
{
   cout << sMessage;
   get();
}

/*********************************
 * Valid Number: GET
 *********************************/
void ValidNumber::get()
{
   cout << ": ";
   cin >> value;
   validate();
}

/*********************************
 * Valid Number: display virtual
 * Should never get here!
 *********************************/
void ValidNumber::display()
{
   cout << "Error\n";
}

/*********************************
 * Valid Number: validate virtual
 * Should never get here!
 *********************************/
bool ValidNumber::validate()
{
   return true;
}

/*********************************
 * PRICE: display
 *********************************/
void Price::display()
{
   cout.setf(ios::fixed);
   cout.setf(ios::showpoint);
   cout.precision(2);
   cout << "$" << value << endl;
}

/*********************************
 * PRICE: validate
 *********************************/
bool Price::validate()
{
   if (value < 0)
   {
      cout << "Value out of range, try again";
      get();
   }
   return true;
}

/*********************************
 * GPA: display
 *********************************/
void GPA::display()
{
   cout.setf(ios::fixed);
   cout.setf(ios::showpoint);
   cout.precision(1);
   cout << value << endl;
}

/*********************************
 * GPA: validate
 *********************************/
bool GPA::validate()
{
   if ((value < 0.0) || (value > 4.0))
   {
      cout << "Value out of range, try again";
      get();
   }
   return true;
}

/***************************************
 * TEST. Test the abstract base class
 *    INPUT:  num:       A valid number to be tested
 *            sMessage:  The prompt message 
 ***************************************/
void test(ValidNumber &num, const char *sMessage)
{
   num.prompt(sMessage);
   num.display();
}
   
/**********************************************************************
 * MAIN.  This function, coupled with TEST, will constitute the driver
 *        program for our ValidNumber family of classes.  
 ***********************************************************************/
int main()
{
   GPA   gpa;
   Price price;

   test(gpa,   "Enter a GPA where 0.0 <= gpa <= 4.0");
   test(price, "Enter a non-negative price");
   
   return 0;
}

