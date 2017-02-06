/***********************************************************************
 * Program:
 *    Exploration 2, Clearness
 *    Brother Neff, CS 238
 * Author:
 *    You
 * Summary:
 *    Amortization Calculating Program
 *    Exploring a practical recurrence relation.
 ***********************************************************************/

#include "system.h"

/*******************************************************************
 * runWithData is a global function declared here
 * and implemented in the clearness.cpp file.
 *
 * It serves as the interface between the CLI and the Amortize class.
 *******************************************************************/
void runWithData(int termInMonths, double rate, double principal,
                 double monthlyPayment, double extraMonthlyPayment,
                 bool showAmortizationSchedule, int start, int end,
                 bool havePrincipal, bool haveRate,
                 bool haveTermInMonths, bool haveMonthlyPayment);

/*******************************************************************
 * getDataAndRunWithIt is a global function that is called by main
 * and then calls runWithData with the data it gets from the System
 * properties (set by main).
 *******************************************************************/
void getDataAndRunWithIt()
{
   int termInMonths;
   double rate;
   double principal;
   double monthlyPayment;
   double extraMonthlyPayment;
   bool showAmortizationSchedule;
   int start;
   int end;
   bool haveTermInMonths = System.getIntegerProperty("n", termInMonths);
   bool havePrincipal = System.getDoubleProperty("p", principal);
   bool haveRate = System.getDoubleProperty("r", rate);
   bool haveMonthlyPayment = System.getDoubleProperty("m", monthlyPayment);
   System.getDoubleProperty("x", extraMonthlyPayment);
   System.getIntegerProperty("s", start);
   System.getIntegerProperty("e", end);
   showAmortizationSchedule = Boolean.getBoolean("v");

   runWithData(termInMonths, rate, principal,
               monthlyPayment, extraMonthlyPayment,
               showAmortizationSchedule, start, end,
               havePrincipal, haveRate,
               haveTermInMonths, haveMonthlyPayment);
}

/*************************************************************************
 * learned tells what was learned.
 *************************************************************************/
void learned();

/*************************************************************************
 * usage tells how to use this program.
 *************************************************************************/
void usage(const char* programName);

/****************************************************************
 * Main reads command-line argument(s) as follows:
 *
 *  Name of a file containing parameter settings, or
 *  (3 of the following 4 parameters are required)
 *
 *      p= principal (amount loaned)
 *      n= term in months (number of payments)
 *      r= annual interest rate (in percent, e.g. 3.75)
 *      m= monthly payment amount
 *
 *      v= (optional) 1 = view amortization schedule
 *      x= (optional) extra monthly payment
 *      s= (optional) month extra payment starts
 *      e= (optional) month extra payment ends (default = n)
 ****************************************************************/
int main(int argc, const char* argv[])
{
   if (argc <= 1)
   {
      learned();
      usage(argv[0]);
      return 0;
   }
   else
   {
      setSystemProperties(argc, argv);
   }

   getDataAndRunWithIt();
   return 0;
}
