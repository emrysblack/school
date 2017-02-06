#include <string>
#include <vector>
#include <stack>
#include <map>

#ifndef PARSER
#define PARSER

static const char NO_ARG = 28; // 28 file separator, ; for testing

class Parser
{
  // to do, this is really ugly, but it works. Think about new ways to refactor and make efficient
  // maybe use that grammer crap and recursion or something
   public:
   static std::vector <std::string> parse(std::vector <std::string> tokens)
   {
      std::string marker;
      marker.push_back(NO_ARG);

      // convert to postfix notation
      enum {ORDER, LAST, LOGICAL1, LOGICAL2, MATH1, MATH2, MATH3, FUNC, DEC};
      std::string token, leading;
      std::stack <std::string> op;
      std::vector <std::string> postfix;
      std::map <std::string,short> priority;
      bool value = false; // differentiate between negative and negation

      // order of ops
      priority["{"] = DEC;
      priority["}"] = DEC;
      priority["("] = ORDER;
      priority[")"] = ORDER;
      priority["["] = ORDER;
      priority["]"] = ORDER;

      // happens last
      priority[marker] = LAST;
      priority[","] = LAST;
      priority["="] = LAST;

      // logical
      priority["&&"] = LOGICAL1;
      priority["||"] = LOGICAL1;
      priority["=="] = LOGICAL2;
      priority["!="] = LOGICAL2;
      priority["<"] = LOGICAL2;
      priority["<="] = LOGICAL2;
      priority[">"] = LOGICAL2;
      priority[">="] = LOGICAL2;

      // mathmatical
      priority["+"] = MATH1;
      priority["-"] = MATH1;
      priority["*"] = MATH2;
      priority["/"] = MATH2;
      priority["%"] = MATH2;
      priority["^"] = MATH3;

      // functions including unary ops
      priority["_NOT"] = FUNC;
      priority["_NEG"] = FUNC;
      priority["_BRACKET"] = FUNC;

      for (int i = 0; i < tokens.size(); i++)
      {
        // check for illegal leading chars
        if (i == 0 && isspace(tokens[i][0]))
        {
          for (int j = 0; j < tokens[i].size(); j++)
          {
            if (tokens[i][j] != ' ')
            {
              throw std::string("Only leading spaces allowed");
            }
          }
          leading = tokens[i];
          continue; // do not store yet
        }
        // convert symbols to functions
        if (tokens[i] == "!")
        {
          tokens[i] = "_NOT";
        }
        if (tokens[i] == "-" && !value)
        {
          tokens[i] = "_NEG"; // change to negation function
        }
        if(tokens[i] == "[")
        {
           tokens[i] = "_BRACKET(";
        }
        if(tokens[i] == "]")
        {
           tokens[i] = ")";
        }
        token = tokens[i];
        if (token.size() > 1 && token[token.size() - 1] == '(')
        {
          priority[token] = FUNC; // is function
        }
        if (priority.count(token)) // not a variable
        {
          if (priority[token] > ORDER && priority[token] < FUNC) // op
          {
            if (value)
              value = false;
            else
              throw "Expected value before " + token;
          }
          else // function
          {
            if (token[0] == '_') // unary op
            {
              if (i >= tokens.size() - 1 || (priority.count(tokens[i + 1]) && priority[tokens[i + 1]] > ORDER && priority[tokens[i + 1]] < FUNC))
              {
                throw "Expected value after " + token;
              }
              else if (i > 0 &&
                  tokens[i - 1][tokens[i - 1].size() - 1] != '(' &&
                  !priority.count(tokens[i - 1]) &&
                  !(priority[tokens[i - 1]] > ORDER && priority[tokens[i - 1]] < FUNC) &&
                  tokens[i - 1][0] != '_')
                throw "Expected operation before " + token;
              value = true;
            }
            else if (token == "(" || token == "{") // special case, must be followed by value and preceeded by op or function open
            {
               if (token == "{" && i)
               {
                  if (i > 1 || !postfix.empty())
                  {
                     throw "Nothing expected before function declaration token " + token;
                  }
               }
               else if (i > 0 &&
                  tokens[i - 1][tokens[i - 1].size() - 1] != '(' &&
                  tokens[i - 1][0] != '_' &&
                  (!priority.count(tokens[i - 1]) ||
                  !(priority[tokens[i - 1]] > ORDER && priority[tokens[i - 1]] < FUNC))
                  )
                throw "Expected operation before " + token;
              else if ((i == 0 ||
                  tokens[i - 1][tokens[i - 1].size() - 1] != '(') &&
                  (i >= tokens.size() - 1 || tokens[i+1] == ")"))
                  throw "Expected value after " + token;
              value = false;
            }
            else if (token == ")" || token == "}") // special case, cannot be preceeded by op
            {
               if (token == "}" && i != tokens.size() - 1)
               {
                  throw "Nothing expected after function declaration token " + token;
               }
              if (i > 0 && (priority.count(tokens[i - 1]) && priority[tokens[i - 1]] > ORDER && priority[tokens[i - 1]] < FUNC))
                throw "Expected value before " + token;
              value = true;
            }
            else if (!value)
              value = true;
            else
            {
                throw "Expected operation before " + token;
            }
          }
          if (token == ")") // finish paren statement
          {
             bool empty = true;
             if(i && tokens[i - 1][0]!= '(')
             {
                empty = false;
             }
            if (op.empty())
            {
              throw std::string("Missing (");
            }
            while (op.top() != "(")
            {
              postfix.push_back(op.top()); // push
              op.pop();
              if (op.empty())
              {
                throw std::string("Missing (");
              }
            }
            op.pop();

            if (empty &&
                priority.count(op.top()))
                {
                   if(priority[op.top()] == FUNC)
                   {
                      postfix.push_back(marker); // first arg for function
                   }
                }
          }
          else if (op.empty() || token == "(" || priority[token] > priority[op.top()]) // in order
          {
            op.push(token); // push
          }
          else // re-order
          {
            while (!op.empty() && priority[op.top()] >= priority[token])
            {
              postfix.push_back(op.top()); // push
              op.pop();
            }
            op.push(token); // push
          }
        }
        else
        {
          if (value && i > 0 &&
              tokens[i - 1][tokens[i - 1].size() - 1] != '(' &&
              tokens[i - 1][0] != '_')
          {
              throw "Expected operation before " + token;
          }
          value = true;
          postfix.push_back(token);
        }
      }
      while (!op.empty())
      {
        if (op.top() == "(")
          throw std::string("Missing )");
        postfix.push_back(op.top()); // push
        op.pop();

      }
      if (!leading.empty())
      {
        postfix.insert(postfix.begin(),leading);
     }
      return postfix;
   }
   private:
   Parser() {} // our class is static
};
#endif
