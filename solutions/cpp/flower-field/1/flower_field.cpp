#include "flower_field.h"
#include <ranges>
#include <string>

namespace flower_field {

constexpr char FLOWER = '*';

unsigned count_flowers(const Field& field, unsigned x, unsigned y) {
   unsigned count = 0;
   for(int delta_x : std::ranges::views::iota(-1, 2)) {
      for(int delta_y : std::ranges::views::iota(-1, 2)) {
         unsigned xi = x + delta_x;
         unsigned yi = y + delta_y;
         if(xi < field.size()            //
            && yi < field.front().size() //
            && int(xi) >= 0 && int(yi) >= 0) {
            if(field.at(xi).at(yi) == FLOWER) {
               count++;
            }
         }
      }
   }
   return count;
}

char to_char(unsigned count) {
   if(count == 0) {
      return ' ';
   }
   return std::to_string(count).at(0);
}

char flower_or_count(const Field& field, char tile, unsigned x, unsigned y) {
   if(tile == FLOWER) {
      return FLOWER;
   }
   return to_char(count_flowers(field, x, y));
}

std::vector<std::string> annotate(const Field& field) {
   std::vector<std::string> annotated;
   unsigned x = 0;
   for(const std::string& line : field) {
      annotated.emplace_back();
      unsigned y = 0;
      for(const char tile : line) {
         annotated.back().push_back(flower_or_count(field, tile, x, y));
         y++;
      }
      x++;
   }
   return annotated;
}

} // namespace flower_field
