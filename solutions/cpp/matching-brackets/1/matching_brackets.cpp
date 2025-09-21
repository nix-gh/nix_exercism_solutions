#include "matching_brackets.h"
#include <stack>

namespace matching_brackets {

char corresponding_bracket(char bracket) {
   switch(bracket) {
   case '}': return '{';
   case ')': return '(';
   case ']': return '[';
   default: return bracket;
   }
}

bool check(std::string_view str) {
   std::stack<char> opening_brackets;

   for(const char ch : str) {
      switch(ch) {
      case '[':
      case '{':
      case '(': {
         opening_brackets.push(ch);
         break;
      }
      case ']':
      case ')':
      case '}':
         if(opening_brackets.size() == 0 || corresponding_bracket(ch) != opening_brackets.top()) {
            return false;
         }
         opening_brackets.pop();
      }
   }
   return opening_brackets.size() == 0;
}

} // namespace matching_brackets
