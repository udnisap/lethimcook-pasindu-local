// units.hpp - Unit definitions, conversion factors, and mappings
#ifndef LETHIMCOOK_UNITS_HPP
#define LETHIMCOOK_UNITS_HPP

#include <string>
#include <unordered_map>
#include <stdexcept>

namespace lethimcook {

/**
 * Unit type enumeration for categorizing different types of units.
 * Corresponds to Python's UnitType(StrEnum).
 */
enum class UnitType {
    Volume,
    Weight,
    Temperature,
    Count
};

/**
 * Struct containing unit information: category and conversion factor.
 * Implements Design Decision #2 - unified data structure.
 * Temperature units have to_base_factor of 0.0 as they require non-linear conversion.
 */
struct UnitInfo {
    UnitType category;
    double to_base_factor;  // Factor to convert to base unit (ml for volume, g for weight, 1.0 for count)
};

/**
 * Global unit lookup table mapping normalized unit strings to their info.
 * Declared here and defined in units.cpp.
 */
extern const std::unordered_map<std::string, UnitInfo> UNIT_TABLE;

/**
 * Normalize a unit string by converting to lowercase and stripping whitespace.
 * @param unit The unit string to normalize
 * @return The normalized unit string
 */
std::string normalize_unit(const std::string& unit);

/**
 * Get the type (category) of a unit.
 * @param unit The unit string to look up
 * @return The UnitType for the given unit
 * @throws std::invalid_argument if the unit is unknown
 */
UnitType get_unit_type(const std::string& unit);

/**
 * Get the conversion factor for a unit to its base unit.
 * Temperature units return 0.0 as they require special handling.
 * @param unit The unit string to look up
 * @return The conversion factor to the base unit
 * @throws std::invalid_argument if the unit is unknown
 */
double get_conversion_factor(const std::string& unit);

} // namespace lethimcook

#endif // LETHIMCOOK_UNITS_HPP
