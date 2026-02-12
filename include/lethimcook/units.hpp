#ifndef LETHIMCOOK_UNITS_HPP
#define LETHIMCOOK_UNITS_HPP

#include <string>
#include <unordered_map>
#include <stdexcept>

namespace lethimcook {

/// Unit category classification, mirroring Python's UnitType StrEnum.
enum class UnitCategory {
    Volume,
    Weight,
    Temperature,
    Count
};

/// Convert a UnitCategory to its string representation.
/// Matches Python's StrEnum values: "volume", "weight", "temperature", "count".
std::string to_string(UnitCategory category);

/// Information about a unit: its category and conversion factor to the base unit.
/// For Temperature units, to_base_factor is unused (special-case logic applies).
struct UnitInfo {
    UnitCategory category;
    double to_base_factor;
};

/// Map from unit string (lowercase) to conversion factor to base unit.
/// Volume base: ml, Weight base: g, Count base: count.
/// Temperature units are NOT in this map (handled separately).
extern const std::unordered_map<std::string, double> CONVERSIONS;

/// Map from unit string (lowercase) to its UnitCategory.
extern const std::unordered_map<std::string, UnitCategory> UNIT_TYPES;

/// Normalize a unit string: lowercase and strip whitespace.
std::string normalize_unit(const std::string& unit);

/// Get the UnitCategory for a unit string.
/// Throws std::invalid_argument if the unit is unknown.
UnitCategory get_unit_type(const std::string& unit);

} // namespace lethimcook

#endif // LETHIMCOOK_UNITS_HPP
