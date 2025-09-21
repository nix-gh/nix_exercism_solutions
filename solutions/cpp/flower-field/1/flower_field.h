#pragma once

#include <span>
#include <string>
#include <vector>

namespace flower_field {

using Field = std::vector<std::string>;
Field annotate(const Field& field);

} // namespace flower_field
