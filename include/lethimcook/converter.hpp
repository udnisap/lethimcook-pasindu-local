#ifndef LETHIMCOOK_CONVERTER_HPP
#define LETHIMCOOK_CONVERTER_HPP

#include <string>

namespace lethimcook {

/// Convert a value from one unit to another.
///
/// @param value      The numeric value to convert.
/// @param from_unit  The source unit string (case-insensitive).
/// @param to_unit    The target unit string (case-insensitive).
/// @return           The converted value.
/// @throws std::invalid_argument if units are unknown or incompatible.
double convert(double value, const std::string& from_unit, const std::string& to_unit);

} // namespace lethimcook

#endif // LETHIMCOOK_CONVERTER_HPP
