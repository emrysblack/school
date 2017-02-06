/***********************************************************************
 * Component:
 *    UNICODE
 * Author:
 *    Br. Helfrich (add your name if you make any changes)
 * Summary:
 *    Everything necessary to work with unicode
 *    text. This includes a character data type,
 *    a string data type, and all the necessary
 *    methods.
 ************************************************************************/

#ifndef _HOMOGRAPH_H_
#define _HOMOGRAPH_H_

#include <vector>        // a String is a vector of Characters
#include <string>        // as parameters
#include <iostream>      // for ISTREAM and OSTREAM
#include <cassert>       // because I am paranoid
using std::vector;
using std::string;
using std::ostream;
using std::istream;

/***********************************
 * CHARACTER
 * One unicode character: a short
 **********************************/
typedef unsigned short Character;

/***********************************
 * HOMOGRAPH
 * Collection of similar chars
 **********************************/
class Homograph
{
   public:
   Homograph(){}
   void setFamily(string symbol) { family = symbol; }
   void insert(string symbol) { symbols.push_back(symbol); }
   string getFamily() { return family; }
   bool isHomograph(string symbol) 
   { 
      for (int i = 0; i < symbols.size(); i++)
      {
         if (symbol == symbols[i])
            return true;
      }
      
      return false;
   }
   private:
   string family;
   vector <string> symbols;
};


/*************************************
 * STRING
 * A unicode string
 ************************************/
class String
{
public:
   String()                 : simple(true) {                                  }
   String(const String & s) : simple(true) { *this = s;                       }
   String(const string & s) : simple(true) { *this = s;                       }

   String & operator =  (const String & s) { text = s.text;     return *this; }
   String & operator =  (const string & s);
   String & operator += (Character c)      { text.push_back(c); return *this; }
   String & operator += (const String & s);
   Character & operator [] (int index)       { return text[index];            }
   Character   operator () (int index) const { return text.at(index);         }
   bool operator == (const String & rhs) const;
   bool operator != (const String & rhs) const { return !(*this == rhs);      }
   
   int size() const                        { return text.size();              }

   void setSimple()                        { simple = true;                   }
   void setComplex()                       { simple = false;                  }
   bool isSimple() const                   { return simple;                   }
   
   friend ostream & operator << (ostream & out, const String & rhs);
   friend istream & operator >> (istream &  in,       String & rhs);
   friend istream & getline     (istream &  in,       String & rhs); 
   string getString() const;
   
private:
   vector <Character> text;
   bool simple;  // display a character as simply as possible?
};


string codeFromString(const string & src);
/*******************************************
 * CHARACTER FROM STRING
 * Derrive the character from a string.  We will
 * advance the pointer by value
 *******************************************/
Character characterFromString(const string &, int &);

/*******************************************
 * CHARACTER FROM NUMBERS
 * Convert a c-str such as 0045 into a Character.
 * This is useful for reading a UC_SimList
 *******************************************/
Character characterFromNumbers(const char *);

/**********************************************
 * STRING FROM CHARACTER
 * For a given character (which may be unicode),
 * return a string with the proper HTML encoding.
 **********************************************/
string stringFromCharacter(Character, bool simple = true);

/******************************************************************
 * RANDOM
 * This function generates a random number.
 *    INPUT:   min, max : The number of values (min <= num <= max)
 *    OUTPUT   <return> : Return the integer
 ****************************************************************/
int random(int min, int max);


#endif // _HOMOGRAPH_H_
