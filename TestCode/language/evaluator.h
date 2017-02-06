#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include "var.h"
using namespace std;

#ifndef EVALUATOR
#define EVALUATOR

void changeScopeLevel(int newScope, int scopeCount)
{
   if (newScope > scopeCount)
   {
      map <string, Var> varList;
      map <string, Function> functionList;

      Function _local_loop;
      _local_loop.name = "_loop_block";

      // define function block
      Var _fun_block;
      _fun_block.setName("_fun_block");
      _fun_block.setValue("False");
      _fun_block.setType("Bool");

      // in loop block
      Var _loop_block;
      _loop_block.setName("_loop_block");
      _loop_block.setValue("False");
      _loop_block.setType("Bool");

      // in if block
      Var _if_block;
      _if_block.setName("_if_block");
      _if_block.setValue("False");
      _if_block.setType("Bool");

    // has executed
    Var _if_exec;
    _if_exec.setName("_if_exec");
    _if_exec.setValue("False");
    _if_exec.setType("Bool");

    // to execute
    Var _if_to_exec;
    _if_to_exec.setName("_if_to_exec");
    _if_to_exec.setValue("False");
    _if_to_exec.setType("Bool");

    while (newScope >= _vars.back().size())
    {
      _loop_block.setScopeLevel(_vars.back().size());
      _if_block.setScopeLevel(_vars.back().size());
      _if_exec.setScopeLevel(_vars.back().size());
      _if_to_exec.setScopeLevel(_vars.back().size());

      varList[_fun_block.getName()] = _fun_block;
      varList[_loop_block.getName()] = _loop_block;
      varList[_if_block.getName()] = _if_block;
      varList[_if_exec.getName()] = _if_exec;
      varList[_if_to_exec.getName()] = _if_to_exec;

      functionList[_loop_block.getName()] = _local_loop;
      _vars.back().push_back(varList);
      _functions.back().push_back(functionList);
    }
  }
  else
  {
    // remove dead scopes
    _vars.back().erase(_vars.back().begin() + newScope + 1,_vars.back().end());
  }
}

void _if(stack <string> & args, int scopeCount)
{
  // eat
  string condition = eat(args);
  if (isVar(condition))
  {
    condition = getVar(condition).getValue();
  }

  if (isTrue(condition))
  {
    Var _if_to_exec = _vars.back()[scopeCount]["_if_to_exec"];
    _if_to_exec.setValue("True");
    _vars.back()[scopeCount][_if_to_exec.getName()] = _if_to_exec;
  }
}

// prototyped so can be called by evaluator and can use evaluator
stack <string> _loop(Function _loop_block);
string _callLindyFunction(stack <string> & args);
string _prompt(stack <string> & args);

void _print(stack <string> & args)
{
   string message = "";
   string value = "";
   stack <string> strings = getArgs(args);

   while (!strings.empty())
   {
      value = eat(strings);

      if (isVar(value))
      {
         Var toPrint = getVar(value);
         value = toPrint.getValue();

         if (toPrint.getType() == "String")
         {
            value = value.substr(1,value.size() - 2);
         }
      }
      else if (isLiteral(value))
      {
         if (value[0] == '\"' || value[0] == '\'')
         {
            value = value.substr(1,value.size() - 2);
         }
      }
      if(isList(value)) // list have special separators that need to be cleaned
      {
         // ready for display
         for(int i = 0; i < value.size(); i++)
         {
            if(value[i] == GROUP_SEPARATE_BEGIN)
            {
               value[i] = '[';
            }
            else if (value[i] == GROUP_SEPARATE_END)
            {
               value[i] = ']';
            }
            else if (value[i] == ITEM_SEPARATE)
            {
               value[i] = ',';
            }
         }
      }
    message += value;
  }
  cout << message;
}

vector <string> decomposeList(string input)
{
   vector <string> tokens;
   if (isList(input))
   {
      // unwrap elements
      input = input.substr(1, input.size() - 2);

      int level = 0;
      for(int i = 0; i < input.size(); i++)
      {
         if(input[i] == GROUP_SEPARATE_BEGIN)
         {
            if (!level)
            {
               input[i] = '[';
            }
            level++;
         }
         else if(input[i] == GROUP_SEPARATE_END)
         {

            level--;
            if (!level)
            {
               input[i] = ']';
            }
         }
      }

      istringstream ss(input);
      string token, piece;

      while(getline(ss,piece,ITEM_SEPARATE))
      {
         if (piece[0] == '[' && !isList(piece)) // incomplete list
         {
            token = piece;
            while( !isList(token) && getline(ss,piece,ITEM_SEPARATE)) // build
            {
               token += ITEM_SEPARATE + piece;
            }
         }
         else
         {
            token = piece;
         }
         tokens.push_back(token);
      }
   }
   return tokens;
}

string composeList(vector <string> tokens)
{
   string list = "";
   for (int i = 0; i < tokens.size(); i++)
   {
      if (isList(tokens[i])) // inner list
      {
         tokens[i][0] = GROUP_SEPARATE_BEGIN;
         tokens[i][tokens[i].size()-1] = GROUP_SEPARATE_END;
      }
      if(i > 0)
      {
         list += ITEM_SEPARATE + tokens[i];
      }
      else
      {
         list = tokens[i];
      }
   }
   return "[" + list + "]";
}

string _listLength(stack <string> & args)
{
   stack <string> strings = getArgs(args, 1);
   string list = eat(strings);
   if (isVar(list))
   {
      list = getVar(list).getValue();
   }
   int size = decomposeList(list).size();
   return toString(size);
}

string _push(stack <string> & args, int scopeCount)
{
   stack <string> strings = getArgs(args, 2);
   string name = eat(strings);
   string value = eat(strings);

   Var list;
   if(isVar(name))
   {
      list = getVar(name); // old var
   }
   string val = list.getValue();
   stack <string> lengthArg;
   lengthArg.push(val);
   // if non empty list
   if( isList(val) && toInt(_listLength(lengthArg)) > 0)
   {
      if(isList(val))
      {
         val[val.size() - 1] = ITEM_SEPARATE;
      }
   }
   else
   {
      val = "[";
   }
   if(isVar(value))
   {
      value = getVar(value).getValue();
   }
   if (isList(value))
   {
     value[0] = GROUP_SEPARATE_BEGIN;
     value[value.size() - 1] = GROUP_SEPARATE_END;
   }
   /*
   stack <string> append_args;
   append_args.push(name);
   append_args.push(val+value+"]");

   _assign(append_args, scopeCount);
   */
   return val+value + "]";
}

string _getType(stack <string> & args)
{
   stack <string> strings = getArgs(args, 1);
   string value = eat(strings);
   string type = "Unknown";

   if (isVar(value))
   {
      value = getVar(value).getValue();
   }

   if(isBool(value))
   {
      type = "Bool";
   }
   else if (isString(value))
   {
      type = "String";
   }
   else if (isInt(value))
   {
      type = "Int";
   }
   else if (isFloat(value))
   {
      type = "Float";
   }
   else if (isList(value))
   {
      type = "List";
   }
   return '"' + type + '"';
}

string _getItem(stack <string> & args)
{
   stack <string> strings = getArgs(args, 2);
   string name = eat(strings);
   string position = eat(strings);
   string input = name;

   if (isVar(input))
   {
      input = getVar(input).getValue();
   }
   if (isVar(position))
   {
      position = getVar(position).getValue();
   }
   int index = toInt(position);

   // decompose list
   vector <string> tokens = decomposeList(input);

   if(index >= tokens.size())
   {
      throw string("Index out of bounds");
   }
   return tokens[index];
}

string _replaceItem(stack <string> & args)
{
   stack <string> strings = getArgs(args, 3);
   string name = eat(strings);
   string position = eat(strings);
   string item = eat(strings);
   string input = name;

   // resolve vars
   if (isVar(input))
   {
      input = getVar(input).getValue();
   }
   if (isVar(position))
   {
      position = getVar(position).getValue();
   }
   if (isVar(item))
   {
      item = getVar(item).getValue();
   }

   int index = toInt(position);

   vector <string> tokens = decomposeList(input);

   if(index >= tokens.size())
   {
      throw string("Index out of bounds");
   }

   // rebuild list
   tokens[index] = item;
   return composeList(tokens);
}

string _insertItem(stack <string> & args)
{
   stack <string> strings = getArgs(args, 3);
   string name = eat(strings);
   string position = eat(strings);
   string item = eat(strings);
   string input = name;

   // resolve vars
   if (isVar(input))
   {
      input = getVar(input).getValue();
   }
   if (isVar(position))
   {
      position = getVar(position).getValue();
   }
   if (isVar(item))
   {
      item = getVar(item).getValue();
   }

   int index = toInt(position);

   vector <string> tokens = decomposeList(input);

   if(index >= tokens.size())
   {
      throw string("Index out of bounds");
   }

   // rebuild list
   tokens.insert(tokens.begin() + index,item);
   return composeList(tokens);
}

string _removeItem(stack <string> & args)
{
   stack <string> strings = getArgs(args, 2);
   string name = eat(strings);
   string position = eat(strings);
   string input = name;

   // resolve vars
   if (isVar(input))
   {
      input = getVar(input).getValue();
   }
   if (isVar(position))
   {
      position = getVar(position).getValue();
   }

   int index = toInt(position);

   vector <string> tokens = decomposeList(input);

   if(index >= tokens.size())
   {
      throw string("Index out of bounds");
   }

   // rebuild list
   tokens.erase(tokens.begin() + index);
   return composeList(tokens);
}

string _bracket(stack <string> & args)
{
  string message, value;
  stack <string> strings = getArgs(args);

  while (!strings.empty())
  {
    value = eat(strings);

    if (isVar(value))
    {
      Var toPrint = getVar(value);
      value = toPrint.getValue();
    }
    if (isList(value))
    {
      value[0] = GROUP_SEPARATE_BEGIN;
      value[value.size() - 1] = GROUP_SEPARATE_END;
    }
    message += ITEM_SEPARATE + value;
  }
  if(!message.empty())
  {
    message[0] = '[';
  }
  else
  {
     message = "[";
  }
  return message + "]";
}

class Evaluator
{
   public:
      static int scopeCount;
      static stack < int > returnScope;
      static bool returnFunction;
      static stack <string> execute(vector <string> postfix)
      {
         bool funDec = false;
         string marker;
         marker.push_back(NO_ARG);
         stack <string> args;
         if (postfix.empty())
         {
           return args;
         }
         int newScope = 0;
         vector <string>::iterator it = postfix.begin();
         if ((*it)[0] == ' ')
         {
           newScope = postfix.begin()->size()/3;
           ++it;
         }
         if (newScope != scopeCount) // scope change
         {

            changeScopeLevel(newScope, scopeCount);

           // test for if and loop
           if(scopeCount < _vars.back().size())
           {
             string _fun_block = _vars.back()[scopeCount]["_fun_block"].getValue();
             string _loop_block = _vars.back()[scopeCount]["_loop_block"].getValue();
             string _if_block = _vars.back()[scopeCount]["_if_block"].getValue();
             string _if_exec = _vars.back()[scopeCount]["_if_exec"].getValue();
             string _if_to_exec = _vars.back()[scopeCount]["_if_to_exec"].getValue();

             if(_fun_block == "True")
             {
                string name = _functions.back()[scopeCount]["_fun_block"].name;
                _functions.back()[scopeCount][name].instructions.push_back(postfix);
                return args;
             }
             else if(_loop_block == "True")
             {
                _functions.back()[scopeCount]["_loop_block"].instructions.push_back(postfix);
                return args;
             }
             else if(_if_block == "True" && (_if_to_exec == "False" || _if_exec == "True"))
             {
               return args;
             }
           }
           else
           {
             // decreased in scope, end any if statements
             _vars.back()[newScope]["_if_exec"].setValue("True");
           }
           scopeCount = newScope;
         }
         else
         {
           string _loop_block = _vars.back()[scopeCount]["_loop_block"].getValue();
           if (_loop_block == "True") // execute loop
           {
             // mark end of loop
             vector<string> end_loop;
             string loop_scope = "   ";
             for (int i = 0; i < scopeCount; i++)
             {
                loop_scope += "   ";
             }
             end_loop.push_back(loop_scope);
             end_loop.push_back("<<");
             _functions.back()[scopeCount]["_loop_block"].instructions.push_back(end_loop);

             // execute
             _vars.back()[scopeCount]["_loop_block"].setValue("False");
             args = _loop(_functions.back()[scopeCount]["_loop_block"]);
             _functions.back()[scopeCount]["_loop_block"].instructions.clear();
             if (returnFunction)
             {
                return args;
             }
           }
           string _fun_block = _vars.back()[scopeCount]["_fun_block"].getValue();
           if (_fun_block == "True")
           {
             _vars.back()[scopeCount]["_fun_block"].setValue("False");
           }
         }

         for (; it != postfix.end(); ++it)
         {
            if (isVar(*it))
            {
              args.push(*it);
            }
            else if (isLiteral(*it))
            {
              args.push(*it);
            }
            else if (*it == "," || *it == marker)
            {
              args.push(*it);
            }
            else
            {
              if (*it == "If(") // if
              {
                // start if block
                Var _if_block = _vars.back()[scopeCount]["_if_block"];
                _if_block.setValue("True");
                _vars.back()[scopeCount]["_if_block"] = _if_block;

                // not executed
                Var _if_exec = _vars.back()[scopeCount]["_if_exec"];
                _if_exec.setValue("False");
                _vars.back()[scopeCount]["_if_exec"] = _if_exec;

                // to execute
                Var _if_to_exec = _vars.back()[scopeCount]["_if_to_exec"];
                _if_to_exec.setValue("False");
                _vars.back()[scopeCount]["_if_to_exec"] = _if_to_exec;

                _if(args, scopeCount);
              }
              else if (*it == "Else(") // else if, else
              {
                if(_vars.back()[scopeCount]["_if_block"].getValue() == "False")
                {
                  throw string("Expected if before else");
                }
                else if(_vars.back()[scopeCount]["_if_exec"].getValue() == "False")
                {
                  _if(args, scopeCount);
                }
              }
              else
              {

                // end if block
                if (postfix.back() != "Else(")
                {
                  Var _if_block = _vars.back()[scopeCount]["_if_block"];
                  _if_block.setValue("False");
                  _vars.back()[scopeCount]["_if_block"] = _if_block;

                }
                // system defined functions
                if (*it == "=")
                {
                    _assign(args, scopeCount);
                }
                else if (*it == "Print(")
                {
                    _print(args);
                }
                else if (*it == "Prompt(")
                {
                    args.push(_prompt(args));
                }
                else if (*it == "GetType(")
                {
                    args.push(_getType(args));
                }
                else if (*it == "Push(")
                {
                   args.push(_push(args, scopeCount));
                }
                else if (*it == "GetItem(")
                {
                   args.push(_getItem(args));
                }
                else if (*it == "ListLength(")
                {
                   args.push(_listLength(args));
                }
                else if (*it == "ReplaceItem(")
                {
                   args.push(_replaceItem(args));
                }
                else if (*it == "InsertItem(")
                {
                   args.push(_insertItem(args));
                }
                else if (*it == "RemoveItem(")
                {
                   args.push(_removeItem(args));
                }
                else if (*it == "_BRACKET(")
                {
                   args.push(_bracket(args));
                }
                else if (*it == "&&")
                {
                    args.push(_and(args));
                }
                else if (*it == "||")
                {
                    args.push(_or(args));
                }
                else if (*it == "==")
                {
                    args.push(_equal(args));
                }
                else if (*it == "!=")
                {
                    args.push(_nequal(args));
                }
                else if (*it == "<")
                {
                    args.push(_less(args));
                }
                else if (*it == "<=")
                {
                    args.push(_lesse(args));
                }
                else if (*it == ">")
                {
                    args.push(_greater(args));
                }
                else if (*it == ">=")
                {
                    args.push(_greatere(args));
                }
                else if (*it == "_NEG")
                {
                    args.push(_neg(args));
                }
                else if (*it == "_NOT")
                {
                    args.push(_not(args));
                }
                else if (*it == "+")
                {
                    args.push(_add(args));
                }
                else if (*it == "-")
                {
                    args.push(_sub(args));
                }
                else if (*it == "*")
                {
                    args.push(_mul(args));
                }
                else if (*it == "/")
                {
                    args.push(_div(args));
                }
                else if (*it == "%")
                {
                    args.push(_mod(args));
                }
                else if (*it == "^")
                {
                    args.push(_pow(args));
                }
                else if (*it == "Return(")
                {
                   if (args.size() > 1)
                   {
                      throw string("Can only return one item");
                   }
                   if (_vars.size() <= 1)
                   {
                      throw string("Can only return from function");
                   }
                   returnFunction = true;
                   return args;
                }
                else if (*it == "Loop(") // while
                {

                  // start loop block
                  Var _loop_block = _vars.back()[scopeCount]["_loop_block"];
                  _loop_block.setValue("True");
                  _vars.back()[scopeCount]["_loop_block"] = _loop_block;

                  // store condition
                  vector <string> condition;

                  for (vector <string>::iterator it1 = postfix.begin(); it1 + 1 != postfix.end(); ++it1)
                  {
                    condition.push_back(*it1);
                  }
                  _functions.back()[scopeCount]["_loop_block"].instructions.push_back(condition);
                }
                // lindy user defined functions must start with letter
                else if (*it == "{")
                {
                   if (postfix[postfix.size() - 2] != "}")
                   {
                      throw string("Expected } token");
                   }
                  // declare funciton block
                  Var _fun_block = _vars.back()[scopeCount]["_fun_block"];
                  _fun_block.setValue("True");
                  _vars.back()[scopeCount]["_fun_block"] = _fun_block;
                  funDec = true;
                }
                else if (*it == "}")
                {
                   if (!funDec)
                   {
                      throw string("Expected { token");
                   }
                }
                else if(isalpha((*it)[0]))
                {
                   // declaration
                   if (_vars.back()[scopeCount]["_fun_block"].getValue() == "True")
                   {
                      // set name and params
                      _functions.back()[scopeCount]["_fun_block"].name = *it;
                      _functions.back()[scopeCount][*it].name = *it;
                      while (!args.empty() && args.top() != marker)
                      {
                        if (args.top() != ",")
                        {
                           if (! isVar(args.top()))
                           {
                              throw string("Expected variable as parameter");
                           }
                           _functions.back()[scopeCount][*it].params.push_back(args.top());
                        }
                        args.pop();
                      }
                   }
                   else // call
                   {
                     args.push(*it); // function name
                     args.push(_callLindyFunction(args));
                   }
                }
                else
                {

                }
              }
            }
         }
         return args;
     }

   private:
     Evaluator() {} // our class is static
};
int Evaluator::scopeCount = -1;
stack < int > Evaluator::returnScope;
bool Evaluator::returnFunction = false;

string stringListToList(string input)
{
   return Evaluator::execute(Parser::parse(Lexer::tokenize(input))).top();
}

string _prompt(stack <string> & args)
{
   stack <string> strings = getArgs(args);
   if(strings.size() > 1)
   {
      throw string("Expected 0 or 1 argument");
   }
   else if(strings.size() == 1)
   {
      string text = eat(strings);
      if(isVar(text))
      {
         text = getVar(text).getValue();
      }
      if(!isString(text))
      {
         throw string("Expected String for prompt");
      }
      cout << toString(text);
   }
   string input;
   getline(cin, input);

   // anything unknown is text
   if (!isLiteral(input))
   {
      input = '"' + input + '"';
   }
   else if (isList(input))
   {
      input = '"' + input + '"';
   }
   return input;
}

void createScope()
{
   vector < map <string, Var> > _local_vars;
   vector < map <string, Function> > _local_functions;
   _vars.push_back(_local_vars);
   _functions.push_back(_local_functions);
   Evaluator::returnScope.push(Evaluator::scopeCount);
   Evaluator::scopeCount = -1;
   changeScopeLevel(0,Evaluator::scopeCount);

   // get base level functions
   if(_functions.size() > 1)
      _functions.back()[0] = _functions[_functions.size() - 2][0];
}

void destroyScope()
{
  _vars.pop_back();
  _functions.pop_back();
  Evaluator::scopeCount = Evaluator::returnScope.top(); // pick up where we left off
  Evaluator::returnScope.pop();
  Evaluator::returnFunction = false;
}

stack <string> _loop(Function _loop_block)
{
   stack <string> results;
  while(isTrue(Evaluator::execute(_loop_block.instructions.front()).top()))
  {
    for(int i = 1; i < _loop_block.instructions.size(); i++)
    {
      results = Evaluator::execute(_loop_block.instructions[i]);
      if(Evaluator::returnFunction)
      {
         return results;
      }
    }
  }
  return results;
}

string _callLindyFunction(stack <string> & args)
{
   // lookup function
   string name = eat(args);

   Function fun = getFunction(name);

   stack <string> p = getArgs(args);
   if(p.size() != fun.params.size())
   {
      ostringstream error;
      error << "Expected " << fun.params.size() << (fun.params.size() == 1 ? " argument" :" arguments");
      throw error.str();
   }
   vector <string> param;
   vector < vector < string > > params;
   string arg;

   // setup param values
   for(int i = fun.params.size() - 1; i >= 0; i--)
   {
      param.push_back(fun.params[i]);
      arg = eat(p);
      if (isVar(arg))
      {
         arg = getVar(arg).getValue();
      }
      param.push_back(arg);
      param.push_back("=");
      params.push_back(param);
      param.clear();
   }

   // setup scope and params
   createScope();

   for (int i = 0; i < params.size(); i++)
   {
      Evaluator::execute(params[i]);
   }
   fun.returnVal = "_"; // null return symbol
   stack <string> results;
   // execute main body
   for (int i = 0; i < fun.instructions.size(); i++)
   {
      results = Evaluator::execute(fun.instructions[i]);
      if(Evaluator::returnFunction)
      {
         if (!results.empty())
         {
            fun.returnVal = results.top();
            results.pop();
         }
         break;
      }
   }

   // ready return
   if (isVar(fun.returnVal))
   {
      fun.returnVal = getVar(fun.returnVal).getValue();
   }

   destroyScope();

   return fun.returnVal; // remove after finished
}

#endif
