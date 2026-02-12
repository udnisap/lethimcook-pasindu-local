#ifndef LETHIMCOOK_CONVERTER_HPP
#define LETHIMCOOK_CONVERTER_HPP

#include <string>

namespace lethimcook {

/// Convert a numeric value from one unit to another.
///
/// Supports volume, weight, temperature, and count conversions.
/// Volume and weight use a two-step conversion through a base unit
/// (milliliters and grams, respectively).  Temperature uses dedicated
/// formulas.  Count units pass through unchanged.
///
/// @param value     The numeric value to convert.
/// @param from_unit The source unit (case-insensitive, aliases accepted).
/// @param to_unit   The target unit (case-insensitive, aliases accepted).
/// @return The converted value.
/// @throws std::invalid_argument if either unit is unknown or the units are
///         of incompatible categories (e.g. volume vs weight).
double convert(double value,
               const std::string& from_unit,
               const std::string& to_unit);

} // namespace lethimcook

#endif // LETHIMCOOK_CONVERTER_HPP
