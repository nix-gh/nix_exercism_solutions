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

auto binary_find(std::span<const int> span, int data) {
   if(span.size() == 0) {
      throw std::domain_error("Not found");
   }
   auto middle_element = span.begin() + span.size() / 2;
   if(*middle_element == data) {
      return middle_element;
   }
   if(*middle_element < data) {
      return binary_find({ ++middle_element, span.end() }, data);
   }
   return binary_find({ span.begin(), middle_element }, data);
}

std::size_t find(std::span<const int> container, int data) {
   auto found = binary_find(container, data);
   if(found == container.end()) {
      throw std::domain_error("Not found");
   }
   return std::distance(container.begin(), found);
}

} // namespace binary_search
