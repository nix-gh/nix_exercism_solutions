#include "binary_search.h"
#include <algorithm>
#include <iterator>
#include <span>
#include <stdexcept>

namespace binary_search {

std::size_t find_std(std::span<const int> container, int data) {
   auto found = std::ranges::find(container, data);
   if(found == container.end()) {
      throw std::domain_error("Not found");
   }
   return std::distance(container.begin(), found);
}

auto binary_find_rec(std::span<const int> span, int data) {
   if(span.size() == 0) {
      throw std::domain_error("Not found");
   }
   auto half = span.begin() + span.size() / 2;
   if(*half == data) {
      return half;
   }
   if(*half < data) {
      return binary_find_rec({ ++half, span.end() }, data);
   }
   return binary_find_rec({ span.begin(), half }, data);
}

auto binary_find_iter(std::span<const int> span, int data) {
   while(span.size() > 0) {
      auto half = span.begin() + span.size() / 2;
      if(*half == data) {
         return half;
      }
      if(*half < data) {
         span = { ++half, span.end() };
      } else {
         span = { span.begin(), half };
      }
   }
   throw std::domain_error("Not found");
}

std::size_t find(std::span<const int> container, int data) {
   auto found = binary_find_iter(container, data);
   return std::distance(container.begin(), found);
}

} // namespace binary_search
