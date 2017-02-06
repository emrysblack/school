/***************************************************************************
 * A simple c++ hello world to work over CGI
 *
 ***************************************************************************/
#include <iostream>
#include <string>
#include <cstdlib>
#include <iomanip>
#include <math.h>
using namespace std;

void display(float apr, int term, float amt, float pmt);
void getData(float &apr, int &term, float &amt);
float computePmt(float apr, int term, float amt);

/***************************************************************************
 * sets up vairables for mortgage and calls functions to get data
 * from client, compute payment, and output the web page
 ***************************************************************************/
int main(int argc, char **argv)
{
   float apr = 0;
   int term = 0;
   float amt = 0;
   float pmt = 0;

   getData(apr, term, amt);
   pmt = computePmt(apr, term, amt);
   display(apr, term, amt, pmt);
   return 0;
}

/***************************************************************************
 * takes the numbers recieved from query and calculated payment and then
 * outputs them in an html table
 ***************************************************************************/
void display(float apr, int term, float amt, float pmt)
{
   cout.setf(ios::fixed);
   cout.setf(ios::showpoint);
   cout.precision(2);
   cout << "content-type: text/html\n\n"
        << "<html>"
        << "<head>"
   // external stylesheet
        << "<link rel=\"stylesheet\" type=\"text/css\""
        << "href=\"/~emrys/html/css/style.css\"/>"
   
        << "<title>C++ - Assignment 10 - Mortgage Payment</title>"
        << "</head>"
        << "<body>"
        << "<h1 style = 'text-align:center'>C++ Mortgage Calculator</h1>"
        << "<table border=\"0\""
        << "style = \"margin:auto; font-family:serif; background-color:grey\">"
        << "<tr><td>APR: "
        <<  apr << "%"
        << "</td></tr><tr><td>Term: "
        << term
        << " years</td><td></td></tr><tr>"
        << "<td>Loan Amount: $"
        << amt
        << "</td></tr>"
        << "<tr><td>Monthly Payment: $"
        << pmt
        << "</td></tr>"
        << "</table>"
        << "</body>"
        << "</html>";
   return;
}

/***************************************************************************
 * takes the numbers recieved from query and calculated payment and then
 * outputs them in an html table
 ***************************************************************************/
void getData(float &apr, int &term, float &amt)
{  
   string query = getenv("QUERY_STRING");
   //   string query = "$APR=10&Term=23&Amt=45";
   string temp;
   // parse the query string

   //go to first variable
   int i;
   for(i = 0; query[i] != '='; i++);
   
   for(i++; query[i] != '&'; i++)
      temp += query[i];
   // get apr
   apr = atof(temp.c_str());
   temp = "";
   //go to second vairable
   for(i; query[i] != '='; i++);

   for(i++; query[i] != '&'; i++)
      temp += query[i];
   // get term
   term = atoi(temp.c_str());
   temp = "";
   //go to last vairable
   for(i; query[i] != '='; i++);
   
   for(i++; query[i]; i++)
      temp += query[i];
   // get amt
   amt = atof(temp.c_str());
   return;
}

/***************************************************************************
 * takes the numbers recieved from query and calculated payment and then
 * outputs them in an html table
 ***************************************************************************/
float computePmt(float i, int n, float p)
{
   i /= 100;
   i /= 12;
   n *= 12;
   float n2 = pow((1 + i), n);
   return p * ((i * n2)/(n2 - 1));
}
