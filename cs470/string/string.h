// my version of a secure String container
// behaves exactly as expected from a string
// plus is secure

#include <iostream>
#include <cassert>
#ifndef STRING_H
#define STRING_H

// functions are inline when used to
// maximize efficiency without
// compromising security
// no redundant checks are made
// beyond security 
class String
{
   // private are not accessible
   // but use checks anyway
private:
   char *text;
   int num;
   int cap;
   void resize() throw (const char *);
   
// all public functions either const that don't change data or 
// use secure methods/functions   
public:
   String() { text = NULL; num = 0; cap = 0; }
   String(const char * p);
   String(const String & rhs);
   String & operator = (const String & rhs);
   String & operator =(const char * rhs);
   String & operator =(const char rhs);
   char & operator [](const int index)
   {
      // only allow valid use of index 
      // to protect against array index
      // attacks as defined in
      // section 2.2.3 under 
      // Array Index
      assert (index > -1 && index < num);
      return text[index];
   }
   String slice(const int index,  const int index1)
   {
      // only allow valid use of index 
      // to protect against array index
      // attacks as defined in
      // section 2.2.3 under 
      // Array Index
      assert (index > -1 && index < num);
      assert (index1 > -1 && index1 < num);
      String slice;
      for (int i = index; i <= index1; i++)
      {
         slice.insert(text[i]);
      }
      return slice;
   }
   ~String() { clear(); }
   void clear() {if (text) delete text; text = NULL; num = 0; cap = 0;}
   int size() const {return num;}
   int length() const {return size();}
   int maxSize() const {return cap - 1;}
   int capacity() const {return cap;}
   const char * c_str() const {return text;}
   std::istream & getline(std::istream & in);
   inline String & insert(const char & c);
   int strcmp(const String & rhs) const;
   int strcmp(const char * rhs) const;
   String & append(const char * rhs);
   String & operator +=(const String & rhs);
   String & operator +=(const char * rhs);
};

// non-default constructor
String::String(const char * p)
{
   text = NULL;
   // get size of input string
   int count;
   for (count = 0; p[count]; ++count);

   // allocate
   if (count > 0)
      text = new char [count + 1];

   // copy contents
   for (int i = 0; i < count; ++i)
   {
      text[i] = p[i];
   }
   if (count > 0)
      text[count] = '\0';
   num = count;
   cap = count;
   return;
}

// copy constructor
String::String(const String & rhs)
{
   text = NULL;
   num = 0;
   cap = 0;
   *this = rhs;
}

String & String::operator =(const char * rhs)
{
   // empty string case
   if (!rhs)
   {
      // make sure to erase anything previous
      // if setting to empty
      clear();
      return *this;
   }
   
   // count number of characters
   // to check bounds
   // so they can't get us
   int count = 0;
   for (; rhs[count]; ++count);
   
   // reallocate if need be
   if (cap < count + 1)
   {    
      if (cap > 0)
      {
         delete text;
      }
      cap = count + 1;
      text = new char [cap];
   }

   // copy items plus null character
   num = count;
   text[num] = '\0';
   for (int i = 0; rhs[i]; ++i)
   {
      text[i] = rhs[i];
   }

   return *this;
}

String & String::operator =(const String & rhs)
{
   // use the safe version with checks
   return *this = rhs.text;
}

String & String::operator =(const char rhs)
{
   // reallocate if need be
   if (cap < 2)
   {    
      if (cap > 0)
      {
         delete text;
      }
      cap = 2;
      text = new char [2];
   }

   // copy items plus null character
   num = 1;
   text[0] = rhs;
   text[1] = '\0';
  
   return *this;
}

// private, user cannot touch
void String::resize() throw (const char *)
{
   String temp(*this); // hold old items
   if (cap > 0)
     delete [] text;
   // smallest we can have is 2 - one char and null
   (cap <= 0)?cap = 2 : cap *= 2; // reallocate
   
   try
   {
      text = new char [cap];
   }
   catch(std::bad_alloc)
   {
      throw "ERROR: unable to allocate a new buffer for string";
   }
   // copy old items back in
   if (temp.text)
      *this = temp;
}
/****************************************************************************
 * secured insert function
 * all user input must go through
 * this function.
 * Hardened against smashing and spraying attacks
 * 
 *  [section 2.2.3 Stack smashing and spraying]
 * "For a Stack Smashing vulnerability to exist in the code, 
 *  the following must be present:
 *  1. There must be a buffer (such as an array) on the stack.
 *  2. The buffer must be reachable from an external input.
 *  3. The mechanism to fill the buffer from the external input must 
 *     not correctly check for the buffer size.
 *
 *  Stack Spraying is related to Stack Smashing in that a stack buffer
 *  is overrun by malicious attacker. The difference is that, instead 
 *  of providing a new and valid stack address, the attacker instead just 
 *  overwrites data in memory. The result is a program crash when the calling
 *  function returns. Thus Stack Smashing is an Elevation of Privilege
 *  attack and Stack Spraying is a Denial attack."
 *  
 *  [section 2.2.3 heap smashing and spraying]
 * "For a Heap Smashing vulnerability to exist in the code, the following
 *  must be present:
 *  1. There must be two adjacent heap buffers.
 *  2. The first buffer must be reachable through external input.
 *  3. The mechanism to fill the buffer from the external input must not 
 *     correctly check for the buffer size.
 *  4. The second buffer must be released before the first.
 *
 *  Heap Smashing is the process of overwriting a buffer on the heap whose
 *  boundaries are not appropriately checked. On the surface, this appears
 *  to be quite similar to Stack Smashing. However the attack vector is quite
 *  a bit more complex: the attacker is not able to directly inject code to
 *  be executed but rather a block of data in memory can be altered. This may
 *  eventually result in arbitrary code insertion. More commonly, the
 *  attacker would alter program flow or its data."
 ***************************************************************************/
String & String::insert(const char & c)
{
   // always check bounds and adjust before the insert 
   // so that we can handle as much data as they can throw
   // at us without being able to lay a finger on the heap
   // num plus one is beacuse we always insert 2 chars(null)
   if (num + 1 >= cap - 1) 
   {
      resize();
   }
   text[num] = c;
   num++;
   text[num] = '\0'; // always enforce good form
}

// uses secure function for all modifications
std::istream & String::getline(std::istream & in)
{
   char input = '\0';
   while (in.get(input) && input != '\n')
   {
      // pass everything through secure insert
      // one char at a time
      insert(input);
   }
   return in;
}

// const everywhere so nothing can be modified
int String::strcmp(const String & rhs) const
{
    const char * left = text;
    const char * right = rhs.text;
   
    // go to first different character or the end
    for (; (*left && *right) && (*left == *right); ++left, ++ right);

    return *left - *right;
}

// const everywhere so nothing can be modified
int String::strcmp(const char * rhs) const
{
   const char * left = text;
   const char * right = rhs;
   
   // go to first different character or the end
   for (; (*left && *right) && (*left == *right); ++left, ++right);

   return *left - *right;
}

// uses secure insert function for all modification
String & String::append(const char * rhs)
{
   for (int i = 0; rhs[i]; ++i)
   {
      // use insert function that is secured, it also takes care of null
      insert(rhs[i]);
   }
   return *this;
}

// operators
bool operator > (const String & lhs, const String & rhs)
{
   return lhs.strcmp(rhs) > 0;
}

bool operator >= (const String & lhs, const String & rhs)
{
   return lhs.strcmp(rhs) > -1;
}

bool operator < (const String & lhs, const String & rhs)
{
   return lhs.strcmp(rhs) < 0;
}

bool operator <= (const String & lhs, const String & rhs)
{
   return lhs.strcmp(rhs) < 1;
}

bool operator == (const String & lhs, const String & rhs)
{
   return !lhs.strcmp(rhs);
}

bool operator != (const String & lhs, const String & rhs)
{
   return lhs.strcmp(rhs);
}

// compare strings and arrays
bool operator > (const String & lhs, const char * rhs)
{
   return lhs.strcmp(rhs) > 0;
}

bool operator >= (const String & lhs, const char * rhs)
{
   return lhs.strcmp(rhs) > -1;
}

bool operator < (const String & lhs, const char * rhs)
{
   return lhs.strcmp(rhs) < 0;
}

bool operator <= (const String & lhs, const char * rhs)
{
   return lhs.strcmp(rhs) < 1;
}

bool operator == (const String & lhs, const char * rhs)
{
   return !lhs.strcmp(rhs);
}

bool operator != (const String & lhs, const char * rhs)
{
   return lhs.strcmp(rhs);
}

std::ostream & operator <<(std::ostream & out, const String & rhs)
{
   (rhs.length()) ? out << rhs.c_str() : out << '\0';
   return out;
}

// append uses secure function so use that in all
String & String::operator +=(const String & rhs)
{
   return append(rhs.c_str());
}

String & String::operator +=(const char * rhs)
{
   return append(rhs);
}

String operator +(const String & lhs, const String & rhs)
{
   String temp(lhs);
   return temp.append(rhs.c_str());
}

String operator +(const String & lhs, const char * rhs)
{
   String temp(lhs);
   return temp.append(rhs);
}

std::istream & operator >>(std::istream & in, String & rhs)
{
   // eat up white space
   in >> std::ws;

   // use a peek to not extract possible white space from buffer
   char input = in.peek();
   while (!isspace(input))
   {
      // grab char and insert
      in.get(input);
      // go through secure function
      rhs.insert(input);

      // check next input
      input = in.peek();
   }
   return in;
}
#endif
