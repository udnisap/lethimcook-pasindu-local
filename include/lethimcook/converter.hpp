// converter.hpp - Unit conversion API
#ifndef LETHIMCOOK_CONVERTER_HPP
#define LETHIMCOOK_CONVERTER_HPP

#include <string>

namespace lethimcook {

// Core conversion function - to be implemented in Task 3
double convert(double value, const std::string& from_unit, const std::string& to_unit);

} // namespace lethimcook

#endif // LETHIMCOOK_CONVERTER_HPP
