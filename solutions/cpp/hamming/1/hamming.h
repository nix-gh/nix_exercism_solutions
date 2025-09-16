#pragma once

#include <stdexcept>
#include <string_view>
namespace hamming {
   
unsigned compute(std::string_view dna_strand, std::string_view other_dna_strand);

}  // namespace hamming
