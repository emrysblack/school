/***********************************************************************
* Program:
*    Assignment 07, Temperature Conversion
*    Brother Helfrich, CS124
* Author:
*    Brady Field
* Summary: 
*    
*    Takes an input temperature in Fahrenheit
*    and converts it to Celsius
*    
*    
*
*    Estimated:  1.0 hrs   
*    Actual:     1.7 hrs
*     I burnt my hand so it took forever to type and debug
************************************************************************/

#include <iostream>
#include <iomanip>

using namespace std;

/**********************************************************************
*
*
***********************************************************************/
double getTemp()
{
   cout.setf(ios::fixed);
   cout.precision(0);
   double tempF;
   double tempC;
   cout << "Please enter Fahrenheit degrees: ";
   cin >> tempF;
   tempC = (tempF-32)*5/9;
   
   return tempC;
}     
/**********************************************************************
* Add text here to describe what the function "main" does. Also don't forget
* to fill this out with meaningful text or YOU WILL LOOSE POINTS.
***********************************************************************/
int main()
{

   
   cout << "Celsius: "
        << getTemp() << endl;
   return 0;
}
