#include "hamming.h"

namespace hamming {

unsigned compute(std::string_view dna_strand, std::string_view other_dna_strand) {
   if(dna_strand.size() != other_dna_strand.size()) {
      throw std::domain_error("DNA strands should have same length");
   }
   // use zip with c++23
   unsigned count = 0;
   for(unsigned index = 0; index < dna_strand.size(); index++) {
      if(dna_strand[index] != other_dna_strand[index]) {
         count++;
      }
   }
   return count;
}

} // namespace hamming
