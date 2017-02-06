/***********************************************************************
* Program:
*    Homework 05, Stocks 
*    Brother Twitchell, CS235
* Author:
*    Brady Field
* Summary: 
*    Will open a file containing lines of stock market transactions
************************************************************************/

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <deque>
using namespace std;

/**********************************************************************
 * Class Stock to store stock buy transactions from file
 **********************************************************************/
class Stock
{
   public:
      int getNumShares();
      float getPrice();
      void setNumShares(int number);
      void setPrice(float number);
   private:
      int numShares;
      float price;
};

void readFile(char* fileName, deque<Stock>& buys, float& totalProfit);
void process(deque<Stock>& buys, string type, 
             int number, float price, float& totalProfit);

/**********************************************************************
 * Sets up a deque of Stocks and calls functions to read in stocks
 ***********************************************************************/
int main(int argc, char** argv)
{
   char fileName[256];
   float totalProfit = 0;
   deque<Stock> buys;
   if (argc < 2)
   {
      cout << "Enter file name: ";
      cin >> fileName;
      readFile(fileName, buys, totalProfit);
   }
   else
   {
      readFile(argv[1], buys, totalProfit);
      cout << "\nTotal Profit: $" << totalProfit << endl;
      cout << "\nUnsold Shares" << endl;
      for (deque<Stock>::iterator i = buys.begin(); i < buys.end(); i++)
      {
         cout << "   " << i->getNumShares();
         cout << " shares bought for $" << i->getPrice() << endl;
      }
   }
   return 0;
}

/**********************************************************************
 * returns number of shares in a transaction
 **********************************************************************/
int Stock::getNumShares()
{
   return numShares;
}

/**********************************************************************
 * returns price per share in a transaction
 **********************************************************************/
float Stock::getPrice()
{
   return price;
}

/**********************************************************************
 * sets number of shares in a transaction
 **********************************************************************/
void Stock::setNumShares(int number)
{
   numShares = number;
}

/**********************************************************************
 * sets price per share in a transaction
 **********************************************************************/
void Stock::setPrice(float number)
{
   price = number;
}

/**********************************************************************
 * reads input file and sends line off to be processed
 **********************************************************************/
void readFile(char* fileName, deque<Stock>& buys, float& totalProfit)
{
   string transaction = "Test";
   string type;
   int number;
   float price;
   ifstream input;
   input.open(fileName);
   if (input.fail())
      cout << "ERROR: Could not open file: " << fileName << endl;
   else
   {
      while (!input.eof())
      {
         input >> type;
         input >> number;
         input >> price;
         if (type != "BLANK") // check for empty input
            process(buys, type, number, price, totalProfit);
         type = "BLANK";
      }
      input.close();
   }
}

/**********************************************************************
 * processes the buy and sell transactions
 **********************************************************************/
void process(deque<Stock>& buys, string type, int number, 
             float price, float& totalProfit)
{
   Stock temp; // stores stock for deque
   temp.setNumShares(number);
   temp.setPrice(price);
   
   if (type == "BUY") // put buys in deque
   {
      buys.push_back(temp);
   
      // display result
      cout << "Bought " << number << " shares at $";
      cout.precision(2);
      cout.setf(ios::fixed,ios::floatfield);
      cout << price << endl;
   }
   
   else if (type == "SELL") // process sells immediately
   {      
      // calculate profit
      float profit = number * price;
      float value;
      for (deque<Stock>::iterator top = buys.begin(); temp.getNumShares() > 0;
           top++)
      {
         if (top->getNumShares() >= temp.getNumShares()) // enough to sell
         {
            top->setNumShares(top->getNumShares() - temp.getNumShares());
            profit -= temp.getNumShares() * top->getPrice();
            temp.setNumShares(0);
            if (top->getNumShares() == 0)
               buys.pop_front();
         }
         else // not enough to sell in current stock list
         {
            temp.setNumShares(temp.getNumShares() - top->getNumShares());
            buys.pop_front();
            profit -= top->getNumShares() * top->getPrice();
         }
      }
      totalProfit += profit;
      
      // display result
      cout << "Sold " << number << " shares at $";
      cout.precision(2);
      cout.setf(ios::fixed,ios::floatfield);
      cout << price << " for a profit of $";
      if (profit < 0)
         cout << "(" << profit * -1 << ")\n";
      else
         cout << profit << endl;
   }
}
