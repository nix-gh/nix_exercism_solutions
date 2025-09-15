#pragma once

#include <algorithm>
#include <array>
#include <ranges>
#include <sstream>
#include <stdexcept>
namespace triangle {

enum class flavor {
   equilateral,
   isosceles,
   scalene
};

template <typename T>
class Triangle {

   public:
   Triangle(T a, T b, T c) {

      m_sides = { a, b, c };
      std::ranges::sort(m_sides);

      if(not is_a_triangle()) {
         throw std::domain_error(
         (std::stringstream() << "No triangle possible with {" << a << ", " << b << ", " << c << "}")
         .str());
      }
   }


   flavor kind() {
      if(a() == b() && b() == c()) {
         return flavor::equilateral;
      }
      if(a() == b() || b() == c()) {
         return flavor::isosceles;
      }
      return flavor::scalene;
   }


   private:
   T a() {
      return m_sides[0];
   }

   T b() {
      return m_sides[1];
   }

   T c() {
      return m_sides[2];
   }

   bool is_a_triangle() {
      return c() != 0 && a() + b() >= c();
   }

   std::array<T, 3> m_sides;
};

template <typename T>
flavor kind(T a, T b, T c) {
   return Triangle(a, b, c).kind();
}

} // namespace triangle
