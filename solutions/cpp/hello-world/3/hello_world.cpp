#include "hello_world.h"
#include <iostream>

namespace hello_world {

std::string hello() {
#ifdef __GNUC__
   std::cout << "GCC version: " << __GNUC__ << '.' << __GNUC_MINOR__ << '.' << __GNUC_PATCHLEVEL__ << std::endl;
#endif

#ifdef __clang__
   std::cout << "Clang version: " << __clang_major__ << '.' << __clang_minor__ << '.'
             << __clang_patchlevel__ << std::endl;
#endif
   std::cout << "pre- C++ standard: " << __cplusplus << "\n";

   return "Hello, World!";
}

} // namespace hello_world