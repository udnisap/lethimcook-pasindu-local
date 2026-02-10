// converter.hpp - Unit conversion API
#ifndef LETHIMCOOK_CONVERTER_HPP
#define LETHIMCOOK_CONVERTER_HPP

#include <string>

namespace lethimcook {

/**
 * Convert a value from one unit to another.
 *
 * @param value The numeric value to convert
 * @param from_unit The source unit
 * @param to_unit The target unit
 * @return The converted value
 * @throws std::invalid_argument If units are incompatible or unknown
 */
double convert(double value, const std::string& from_unit, const std::string& to_unit);

} // namespace lethimcook

#endif // LETHIMCOOK_CONVERTER_HPP
