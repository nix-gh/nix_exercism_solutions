#include "isbn_verifier.h"
#include <cstdlib>
#include <ranges>
#include <regex>
#include <string>

namespace isbn_verifier {

constexpr unsigned ISBN_LEN = 10;
constexpr unsigned ISBN_LAST = ISBN_LEN -1;

unsigned to_isbn_digit(char c) {
   if(c == 'X') {
      return 10;
   }
   return atoi(&c);
}

unsigned weight_of(unsigned index) {
   return ISBN_LEN - index;
}

bool is_valid(const std::string isbn) {
   // use enumerate with cpp 23
   const std::regex isbn_regex("[0-9,X,-]+");
   std::smatch base_match; 
   if(!std::regex_match(isbn, base_match, isbn_regex)){
      return false;  
   }

   unsigned index = 0;
   unsigned sum = 0;
   for(char c : isbn | std::ranges::views::filter([](char c) { return c != '-'; })) {
      if(c == 'X' && index != ISBN_LAST){
         return false;
      }
      sum += to_isbn_digit(c) * weight_of(index);
      index++;
   }
   return index == ISBN_LEN && sum % 11 == 0;
}

} // namespace isbn_verifier
