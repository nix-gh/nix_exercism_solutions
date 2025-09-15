#include "triangle.h"

namespace triangle {

class Triangle {

   public:
   Triangle(double side_a, double side_b, double side_c) {

      m_sides = { side_a, side_b, side_c };
      std::ranges::sort(m_sides);

      if(not is_a_triangle()) {
         throw std::domain_error(
         (std::stringstream() << "No triangle possible with {" << side_a << ", " << side_b << ", " << side_c << "}")
         .str());
      }
   }


   flavor kind() {
      if(side_a() == side_b() && side_b() == side_c()) {
         return flavor::equilateral;
      }
      if(side_a() == side_b() || side_b() == side_c()) {
         return flavor::isosceles;
      }
      return flavor::scalene;
   }


   private:
   double side_a() {
      return m_sides[0];
   }

   double side_b() {
      return m_sides[1];
   }

   double side_c() {
      return m_sides[2];
   }

   bool is_a_triangle() {
      return side_a() + side_b() > side_c();
   }

   std::array<double, 3> m_sides;
};

flavor kind(double side_a, double side_b, double side_c) {
   return Triangle(side_a, side_b, side_c).kind();
}

} // namespace triangle
