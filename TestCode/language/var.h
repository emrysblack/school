#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <stack>
#include <map>
#include <cmath>
using namespace std;
#ifndef VAR
#define VAR

static const char GROUP_SEPARATE_BEGIN = 29; // 29 group separator, { for testing
static const char GROUP_SEPARATE_END = 30; // 30 record separator, } for testing
static const char ITEM_SEPARATE = 31; // 31 unit separator, ; for testing

class Var
{
   public:
   Var() {}
   ~Var() {}
   string getName() { return name; }
   string getValue() { return value; }
   string getType() { return type; }
   int getScopeLevel() { return scopeLevel; }

   void setName(string text) { name = text; }
   void setValue(string text) { value = text; }
   void setType(string text) { type = text; }
   void setScopeLevel(int level) { scopeLevel = level; }

   protected:
   string name;
   string value;
   string type;
   int scopeLevel;
};

// lowercase names are local, uppercase names are global
map <string, Var> _globals;
vector < vector < map <string, Var> > > _vars;

Var getVar(string name)
{
  if (islower(name[0])) // locals
  {
    for (int i = 0; i < _vars.back().size(); i++)
    {
      if(_vars.back()[i].count(name))
      {
        return _vars.back()[i][name];
      }
    }
  }
  else // globals
  {
    if (_globals.count(name))
    {
      return _globals[name];
    }
  }
  throw string("Unknown variable " + name);
}

struct Function
{
  string name;
  vector< vector<string> > instructions;
  vector< string> params;
  string returnVal;
};
vector < vector < map <string, Function> > > _functions;

Function getFunction(string name)
{
    for (int i = 0; i < _functions.back().size(); i++)
    {
      if(_functions.back()[i].count(name))
      {
        return _functions.back()[i][name];
      }
    }
  throw string("Unknown function " + name.substr(0,name.size() - 1));
}

/* var util functions */

string eat(stack <string> & args)
{
  if (args.empty())
  {
    throw string("Expected argument");
  }
  string arg = args.top();
  args.pop();
  return arg;
}

stack <string> getArgs(stack <string> & args, int num = -1)
{
   string marker;
   marker.push_back(NO_ARG);

   stack <string> strings;
   if (args.size() && num)
   {
      int num_args = 1;

      if (args.top() == marker)
      {
         args.pop();
         num_args--;
      }
      // eat args and re-order
      while (num_args)
      {
         if (args.top() == ",")
         {
            args.pop();
            num_args++;
         }
         else
         {
            strings.push(eat(args));
            num_args--;
         }
      }
   }
   if (num > 0 && num != strings.size())
   {
      ostringstream error;
      error << "Expected " << num << (num == 1 ? " argument" :" arguments");
      throw error.str();
   }
   return strings;
}

bool isBool(string value)
{
  return value == "True" || value == "False";
}

bool isString(string value)
{
  if (value[0] == '\"')
  {
    return value[value.length() - 1] == '\"';
  }
  else if (value[0] == '\'')
  {
    return value[value.length() - 1] == '\'';
  }
  return false;
}

bool isList(string value)
{
   return value[0] == '[' && value[value.length() - 1] == ']';
}

bool isInt(string number)
{
    istringstream ss(number);
    int i;
    ss >> noskipws >> i; // noskipws considers leading whitespace invalid
    // Check the entire string was consumed and if either failbit or badbit is set
    return ss.eof() && !ss.fail();
}

bool isFloat(string number)
{
    istringstream ss(number);
    float f;
    ss >> noskipws >> f; // noskipws considers leading whitespace invalid
    // Check the entire string was consumed and if either failbit or badbit is set
    return ss.eof() && !ss.fail();
}

long long toInt(string value)
{
  long long i = 0;
  if (isInt(value))
  {
    istringstream ss(value);
    ss >> noskipws >> i;
  }
  else if (isString(value))
  {
    i = value != "\"\"" && value !="\'\'";
  }
  else if (isBool(value))
  {
    i = value == "True";
  }
  return i;
}

long double toFloat(string value)
{
  long double f = 0.0;
  if (isFloat(value))
  {
    istringstream ss(value);
    ss >> noskipws >> f;
  }
  else if (isString(value))
  {
    f = value != "\"\"" && value !="\'\'";
  }
  else if (isBool(value))
  {
    f = value == "True";
  }
  return f;
}

string toString(string value)
{
   return value.substr(1,value.size()-2);
}

string toString(int value)
{
   ostringstream ss;
   ss << value;
   return ss.str();
}

string toString(long value)
{
   ostringstream ss;
   ss << value;
   return ss.str();
}

string toString(long long value)
{
   ostringstream ss;
   ss << value;
   return ss.str();
}

string toString(float value)
{
   ostringstream ss;
   ss << value;
   return ss.str();
}

string toString(double value)
{
   ostringstream ss;
   ss << value;
   return ss.str();
}

string toString(long double value)
{
   ostringstream ss;
   ss << value;
   return ss.str();
}

bool isTrue(string value)
{
  if (isBool(value))
  {
    return value == "True";
  }
  if (isString(value))
  {
    return value != "\"\"" && value !="\'\'";
  }
  if (isInt(value))
  {
    return toInt(value) > 0;
  }
  if (isFloat(value))
  {
    return toFloat(value) > 0.0;
  }
}

bool isEqual(string left, string right)
{
  // do any necesary casting and compare
  if (isString(left) || isString(right)) // concat
  {
    return toString(left) == toString(right);
  }
  if (isFloat(left) || isFloat(right)) // float
  {
    return toFloat(left) == toFloat(right);
  }
  if (isInt(left) && isInt(right)) // int
  {
    return toInt(left) == toInt(right);
  }
  if (isBool(left) && isBool(right)) // bool
  {
    return toInt(left) == toInt(right); // bool to int
  }
}

bool isLess(string left, string right)
{
  // do any necesary casting
  // compare
  if (isFloat(left) || isFloat(right)) // float
  {
    return toFloat(left) < toFloat(right);
  }
  if (isInt(left) && isInt(right)) // int
  {
    return toInt(left) < toInt(right);
  }
  if (isBool(left) && isBool(right)) // bool
  {
    return toInt(left) < toInt(right); // bool to int
  }
}

// TO-DO split into separete utility file
bool isLiteral(string value)
{
  return isBool(value) || isString(value) || isInt(value) || isFloat(value) || isList(value);
}

bool isVar(string value)
{
  return isalpha(value[0]) && value[value.size() - 1] != '(' && !isLiteral(value);
}

bool isFunction(string value)
{
  return !isVar(value) && !isLiteral(value);
}

string _neg(stack <string> & args)
{
  string value = eat(args);
  if (isVar(value))
  {
    value = getVar(value).getValue();
  }
  if (!isInt(value) && !isFloat(value))
  {
    throw string("Expected number");
  }
  if (value[0] == '-')
  {
    return value.substr(1);
  }
  return "-" + value;
}

string _add(stack <string> & args)
{
  // eat args
  string right = eat(args);
  string left = eat(args);

  if (isVar(left))
  {
    left = getVar(left).getValue();
  }
  if (isVar(right))
  {
    right = getVar(right).getValue();
  }
  if (isList(left) || isList(right))
  {
     if (isList(left))
     {
      left = toString(left);
     }
     if (isList(right))
     {
      right = toString(right);
     }
     string sep = "";
     if (!left.empty() && !right.empty())
     {
        sep += ITEM_SEPARATE;
     }
     return "[" + left + sep + right + "]";
  }
  if (isString(left) || isString(right)) // concat
  {
    if (isString(left))
    {
      left = toString(left);
    }
    if (isString(right))
    {
      right = toString(right);
    }
    return "\"" + left + right + "\"";
  }
  if (isFloat(left) || isFloat(right)) // float
  {
    return toString(toFloat(left) + toFloat(right));
  }
  if (isInt(left) && isInt(right)) // int
  {
    return toString(toInt(left) + toInt(right));
  }
  if (isBool(left) && isBool(right)) // bool
  {
    return toString(toInt(left) + toInt(right)); // bool to int
  }
}

string _sub(stack <string> & args)
{
  // eat args
  string right = eat(args);
  string left = eat(args);

  if (isVar(left))
  {
    left = getVar(left).getValue();
  }
  if (isVar(right))
  {
    right = getVar(right).getValue();
  }
  if (isString(left) || isString(right)) // concat
  {
    throw string("Expected number");
  }
  if (isFloat(left) || isFloat(right)) // float
  {
    return toString(toFloat(left) - toFloat(right));
  }
  if (isInt(left) && isInt(right)) // int
  {
    return toString(toInt(left) - toInt(right));
  }
  if (isBool(left) && isBool(right)) // bool
  {
    return toString(toInt(left) - toInt(right)); // bool to int
  }
}

string _mul(stack <string> & args)
{
  // eat args
  string right = eat(args);
  string left = eat(args);

  if (isVar(left))
  {
    left = getVar(left).getValue();
  }
  if (isVar(right))
  {
    right = getVar(right).getValue();
  }
  if (isString(left) || isString(right)) // concat
  {
    throw string("Expected number");
  }
  if (isFloat(left) || isFloat(right)) // float
  {
    return toString(toFloat(left) * toFloat(right));
  }
  if (isInt(left) && isInt(right)) // int
  {
    return toString(toInt(left) * toInt(right));
  }
  if (isBool(left) && isBool(right)) // bool
  {
    return toString(toInt(left) * toInt(right)); // bool to int
  }
}

string _div(stack <string> & args)
{
  // eat args
  string right = eat(args);
  string left = eat(args);

  if (isVar(left))
  {
    left = getVar(left).getValue();
  }
  if (isVar(right))
  {
    right = getVar(right).getValue();
  }
  if (isString(left) || isString(right)) // concat
  {
    throw string("Expected number");
  }
  if (!toFloat(right))
  {
    throw string("Cannot divide by 0");
  }
  if (isFloat(left) || isFloat(right)) // float
  {
    return toString(toFloat(left) / toFloat(right));
  }
  if (isInt(left) && isInt(right)) // int
  {
    return toString(toInt(left) / toInt(right));
  }
  if (isBool(left) && isBool(right)) // bool
  {
    return toString(toInt(left) / toInt(right)); // bool to int
  }
}

string _mod(stack <string> & args)
{
  // eat args
  string right = eat(args);
  string left = eat(args);

  if (isVar(left))
  {
    left = getVar(left).getValue();
  }
  if (isVar(right))
  {
    right = getVar(right).getValue();
  }
  if (isString(left) || isString(right)) // concat
  {
    throw string("Expected number");
  }
  if (!toFloat(right))
  {
    throw string("Cannot mod by 0");
  }
  if (isFloat(left) || isFloat(right)) // float
  {
    return toString(fmod(toFloat(left),toFloat(right)));
  }
  if (isInt(left) && isInt(right)) // int
  {
    return toString(toInt(left) % toInt(right));
  }
  if (isBool(left) && isBool(right)) // bool
  {
    return toString(toInt(left) % toInt(right)); // bool to int
  }
}

string _pow(stack <string> & args)
{
  // eat args
  string right = eat(args);
  string left = eat(args);

  if (isVar(left))
  {
    left = getVar(left).getValue();
  }
  if (isVar(right))
  {
    right = getVar(right).getValue();
  }
  if (isString(left) || isString(right)) // concat
  {
    throw string("Expected number");
  }
  if (isFloat(left) || isFloat(right)) // float
  {
    return toString(pow(toFloat(left),toFloat(right)));
  }
  if (isInt(left) && isInt(right)) // int
  {
    return toString(pow(toInt(left),toInt(right)));
  }
  if (isBool(left) && isBool(right)) // bool
  {
    return toString(pow(toInt(left),toInt(right))); // bool to int
  }
}

string _and(stack <string> & args)
{
  // eat args
  string right = eat(args);
  string left = eat(args);

  if (isVar(left))
  {
    left = getVar(left).getValue();
  }
  if (isVar(right))
  {
    right = getVar(right).getValue();
  }
  if (!isLiteral(left) || !isLiteral(right))
  {
    throw string("Unknown literal type");
  }
  return (isTrue(left) && isTrue(right) ? "True":"False");
}

string _or(stack <string> & args)
{
  // eat args
  string right = eat(args);
  string left = eat(args);

  if (isVar(left))
  {
    left = getVar(left).getValue();
  }
  if (isVar(right))
  {
    right = getVar(right).getValue();
  }
  if (!isLiteral(left) || !isLiteral(right))
  {
    throw string("Unknown literal type");
  }
  return (isTrue(left) || isTrue(right) ? "True":"False");
}

string _equal(stack <string> & args)
{
  // eat args
  string right = eat(args);
  string left = eat(args);

  if (isVar(left))
  {
    left = getVar(left).getValue();
  }
  if (isVar(right))
  {
    right = getVar(right).getValue();
  }
  if (!isLiteral(left) || !isLiteral(right))
  {
    throw string("Unknown literal type");
  }
  return (isEqual(left,right) ? "True":"False");
}

string _nequal(stack <string> & args)
{
  // eat args
  string right = eat(args);
  string left = eat(args);

  if (isVar(left))
  {
    left = getVar(left).getValue();
  }
  if (isVar(right))
  {
    right = getVar(right).getValue();
  }
  if (!isLiteral(left) || !isLiteral(right))
  {
    throw string("Unknown literal type");
  }
  return (!isEqual(left,right) ? "True":"False");
}

string _less(stack <string> & args)
{
  // eat args
  string right = eat(args);
  string left = eat(args);

  if (isVar(left))
  {
    left = getVar(left).getValue();
  }
  if (isVar(right))
  {
    right = getVar(right).getValue();
  }
  if (!isLiteral(left) || !isLiteral(right))
  {
    throw string("Unknown literal type");
  }
  if (isString(left) || isString(right)) // concat
  {
    throw string("Expected number");
  }
  return (isLess(left,right) ? "True":"False");
}

string _lesse(stack <string> & args)
{
  // eat args
  string right = eat(args);
  string left = eat(args);

  if (isVar(left))
  {
    left = getVar(left).getValue();
  }
  if (isVar(right))
  {
    right = getVar(right).getValue();
  }
  if (!isLiteral(left) || !isLiteral(right))
  {
    throw string("Unknown literal type");
  }
  if (isString(left) || isString(right)) // concat
  {
    throw string("Expected number");
  }
  return (isLess(left,right) || (!isLess(left,right) && !isLess(right,left)) ? "True":"False");
}

string _greater(stack <string> & args)
{
  // eat args
  string right = eat(args);
  string left = eat(args);

  if (isVar(left))
  {
    left = getVar(left).getValue();
  }
  if (isVar(right))
  {
    right = getVar(right).getValue();
  }
  if (!isLiteral(left) || !isLiteral(right))
  {
    throw string("Unknown literal type");
  }
  if (isString(left) || isString(right)) // concat
  {
    throw string("Expected number");
  }
  return (isLess(right,left) ? "True":"False");
}

string _greatere(stack <string> & args)
{
  // eat args
  string right = eat(args);
  string left = eat(args);

  if (isVar(left))
  {
    left = getVar(left).getValue();
  }
  if (isVar(right))
  {
    right = getVar(right).getValue();
  }
  if (!isLiteral(left) || !isLiteral(right))
  {
    throw string("Unknown literal type");
  }
  if (isString(left) || isString(right)) // concat
  {
    throw string("Expected number");
  }
  return (isLess(right,left) || (!isLess(left,right) && !isLess(right,left)) ? "True":"False");
}

string _not(stack <string> & args)
{
  string value = eat(args);
  if (isVar(value))
  {
    value = getVar(value).getValue();
  }
  return (!isTrue(value) ? "True":"False");
}

void _assign(stack <string> & args, int scopeLevel)
{
    // eat args
    string value = eat(args);
    string name = eat(args);

    if (!isVar(name))
    {
      throw string("Cannot change literal");
    }
    Var var;
    try
    {
       var  = getVar(name); // old var
       if (var.getName()[var.getName().size() - 1] == '_')
       {
         throw false;
       }
    }
    catch(bool)
    {
      throw string("Cannot modify const");
    }
    catch(string)
    {

       var.setName(name); // new var
       var.setScopeLevel(scopeLevel);
    }
    if (isLiteral(value))
    {
      var.setValue(value);
      if (isString(value))
      {
        var.setType("String");
      }
      else if (isFloat(value))
      {
        var.setType("Float");
      }
      else if (isInt(value))
      {
        var.setType("Int");
      }
      else if (isBool(value))
      {
        var.setType("Bool");
      }
      else if (isList(value))
      {
        var.setType("List");
      }
    }
    else if (isVar(value))
    {
      Var right = getVar(value);
      var.setValue(right.getValue());
      var.setType(right.getType());
    }
    else
    {
     throw string("Empty or unknown value type");
    }
    if (isupper(var.getName()[0]))
    {
      _globals[var.getName()] = var;
    }
    else
    {
      _vars[_vars.size() - 1][var.getScopeLevel()][var.getName()] = var;
    }
}
#endif
