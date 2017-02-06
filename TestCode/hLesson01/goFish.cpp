/***********************************************************************
* Program:
*    Assignment 01, Go Fish
*    Brother Helfrich, CS 235
* Author:
*    <your names here>
* Summary: 
*    This is all the functions necessary to play Go Fish!
*
*    Estimated:  0.0 hrs   
*    Actual:     0.0 hrs
*      Please describe briefly what was the most difficult part.
************************************************************************/

#include <iostream>
#include <fstream>
#include <cassert>
#include "set.h"
#include "goFish.h"
#include "card.h"
using namespace std;

/**********************************************************************
 * GO FISH
 * The function which starts it all
 ***********************************************************************/
void goFish()
{
   Set<Card> deck;
   Set<Card> hand;
   Card card;
   int matches = 0;

   // read deck from file
   ifstream fin("/home/cs235/lesson01/hand.txt");
   if (fin.fail())
   {
      cout << "ERROR: could not read file\n";
      return;
   }
   
   while(!fin.fail())
   {
      fin >> card;
      deck.insert(card);
   }
   // cout << deck << endl;
   // draw 5 cards and start game
   for (int i = 0; i < 5; i++)
   {
      hand.insert(deck.top());
      deck.erase(deck.find(deck.top()));
   }
   fin.close();
   // cout << hand << endl;
   SetIterator<Card> myCard;
   cout << "We will play 5 rounds of Go Fish.  Guess the card in the hand\n";
   for (int i = 0; i < 5; i++)
   {
      cout << "round " << i + 1 << ": ";
      cin >> card;
      myCard = hand.find(card);
      if (myCard.getItem() == NULL)
         cout << "\tGo Fish!\n";
      else
      {
         cout << "\tYou got a match!\n";
         // discard
         hand.erase(myCard);
         matches++;

         //draw next card
         hand.insert(deck.top());
      }
   }
   cout << "You have " << matches << " matches!\n"
        << "The remaining cards: " << hand << endl;
   return;
}
