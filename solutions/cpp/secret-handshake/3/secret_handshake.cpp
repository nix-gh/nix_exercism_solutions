#include "secret_handshake.h"
#include <algorithm>
#include <array>
#include <cmath>
#include <iterator>
#include <ranges>
#include <string>
#include <vector>

namespace secret_handshake {

constexpr std::size_t actions_size = 4;

std::string to_action(unsigned id) {
   static const std::array<std::string, 4> actions = { "wink", "double blink", "close your eyes", "jump" };
   return actions.at(id);
}

std::vector<std::string> to_action_vec(auto range) {
   std::vector<std::string> vec;
   std::ranges::transform(range, std::back_inserter(vec), to_action);
   return vec;
}

std::vector<std::string> commands(unsigned code) {

   // use ranges views enumerate && to vector with c++23

   auto secret_handshake_ids = std::views::iota(unsigned(0), actions_size)
   | std::ranges::views::filter([code](unsigned action_id) {
                                  return (code & unsigned(std::pow(2, action_id))) != 0;
                               });

   if((code & 16) != 0) {
      return to_action_vec(secret_handshake_ids | std::ranges::views::reverse);
   }
   return to_action_vec(secret_handshake_ids);
}

} // namespace secret_handshake
