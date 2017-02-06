#include <string>
#include <vector>

#ifndef LEXER
#define LEXER
class Lexer
{
   public:
   static std::vector <std::string> tokenize(std::string input)
   {
      std::vector <std::string> tokens;
      std::string token, temp;
      bool unary = false; // marks unary op for function ending
      bool unaryP = false; // especial to handle parenthesis ending
      const char * p = &input[0];
      const char * end = &input[input.size()];

      // ignore carriage returns
      if (*(end - 1) == '\r')
      {
        end--;
      }
      // leading spaces for scope
      while (p < end && isspace(*p))
      {
        token += *p;
        p++;
      }
      if (token.size())
      {
        tokens.push_back(token);
      }

      // input
      while (p < end)
      {
         token = "";

         // literals

         // number
         if (*p >= '0' && *p <= '9')
         {
            token += *p;
            p++;
            while(*p >= '0' && *p <= '9' && p < end)
            {
               token += *p;
               p++;
            }
            if(*p == '.' && *(p+1) >= '0' && *(p+1) <= '9' && p + 1 < end) // float
            {
              token += *p;
              p++;
              while(*p >= '0' && *p <= '9' && p < end) // mantisa
              {
                 token += *p;
                 p++;
              }
            }
         }
         else if(*p == '.' && *(p+1) >= '0' && *(p+1) <= '9' && p + 1 < end) // float
         {
           token += '0'; // prefix 0
           token += *p;
           p++;
           while(*p >= '0' && *p <= '9' && p < end) // mantisa
           {
              token += *p;
              p++;
           }
         }
         // string
         else if (*p == '"')
         {
            do
            {
               // check for escapes
               if (*p == '\\')
               {
                  if (*(p + 1) == 'n') // newline
                  {
                    token += "\n";
                    p++;
                    p++;
                  }
                  else if (*(p + 1) == 't') // tab
                  {
                    token += "\t";
                    p++;
                    p++;
                  }
                  else if (*(p + 1) == 'r') // carriage return
                  {
                    token += "\r";
                    p++;
                    p++;
                  }
                  else if (*(p + 1) == '\\') // backslash
                  {
                    token += "\\";
                    p++;
                    p++;
                  }
                  else if (*(p + 1) == '"') // double quote
                  {
                    token += "\"";
                    p++;
                    p++;
                  }
                  else if (*(p + 1) == '\'') // single quote
                  {
                    token += "'";
                    p++;
                    p++;
                  }
                  else if (p + 1 < end)
                  {
                    token += "\\";
                    p++;
                    token += *p;
                    p++;
                  }
               }
               else
               {
                 token += *p;
                 p++;
               }
            } while(*p != '"' && p < end);
            token += *p;
            p++;
         }
         else if (*p == '\'')
         {
            do
            {
               token += *p;
               p++;
            } while(*p != '\'' && p < end);
            token += *p;
            p++;
         }
         else if (*p == '(' || *p == ')')
         {
            token += *p;
            p++;
         }
         // variable or function
         else if (isalnum(*p))
         {
            while(p < end && (isalnum(*p) || *p == '_'))
            {
               token += *p;
               p++;
               if (*p == '(' || *p == '[')
               {
                  token += *p;
               }
            }
         }
         // whitespace
         else if (isspace(*p))
         {
            p++;
         }
         // double symbols

         // and
         else if (*p == '&' && p + 1 < end && *(p+1) == '&')
         {
           token += *p;
           p++;
           token += *p;
           p++;
         }

         // or
         else if (*p == '|' && p + 1 < end && *(p+1) == '|')
         {
           token += *p;
           p++;
           token += *p;
           p++;
         }

         // equal
         else if (*p == '=' && p + 1 < end && *(p+1) == '=')
         {
           token += *p;
           p++;
           token += *p;
           p++;
         }

         // not equal
         else if (*p == '!' && p + 1 < end && *(p+1) == '=')
         {
           token += *p;
           p++;
           token += *p;
           p++;
         }

         // less equal
         else if (*p == '<' && p + 1 < end && *(p+1) == '=')
         {
           token += *p;
           p++;
           token += *p;
           p++;
         }

         // greater equal
         else if (*p == '>' && p + 1 < end && *(p+1) == '=')
         {
           token += *p;
           p++;
           token += *p;
           p++;
         }

         // comments
         else if (*p == '<' && p + 1 < end && *(p+1) == '<')
         {
           // look for closing comments or end of line
           while (p + 1 < end && !(*p == '>' && *(p+1) == '>'))
           {
             p++;
           }

           // skip over closing comments
           if (*p == '>' && p + 1 < end && *(p+1) == '>')
           {
             p++;
           }
           p++;
         }

         // single symbols
         else if (*p == '[')
         {
            token += *p;
            tokens.push_back(token);
            tokens.push_back("(");
            token = "";
            p++;
         }

         else if (ispunct(*p))
         {
            token += *p;
            p++;
         }
         else
         {
            p++;
         }
         if (token != "")
         {
           tokens.push_back(token);
           if (unary)
           {
             tokens.push_back(")");
             unary = false;
           }
           else if (unaryP)
           {
             if (token == ")")
             {
               tokens.push_back(")");
               unaryP = false;
             }
           }
         }
      }
      return tokens;
   }
   private:
   Lexer() {} // our class is static
};
#endif
