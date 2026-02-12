#ifndef LETHIMCOOK_UNITS_HPP
#define LETHIMCOOK_UNITS_HPP

#include <string>
#include <unordered_map>

namespace lethimcook {

/// Unit category enumeration mirroring Python's UnitType StrEnum.
enum class UnitType {
    Volume,
    Weight,
    Temperature,
    Count
};

/// Returns a human-readable string for a UnitType (e.g. "volume", "weight").
std::string unit_type_to_string(UnitType type);

/// Information about a single unit: its category and conversion factor to the
/// base unit of that category (ml for volume, g for weight, 1 for count).
/// Temperature units are stored with a factor of 0.0 because temperature
/// conversion is non-linear and handled separately.
struct UnitInfo {
    UnitType category;
    double to_base_factor;
};

/// Combined lookup table mapping every recognized unit string (lowercase) to
/// its UnitInfo.  Includes all aliases (e.g. "cup", "cups", "teaspoon", "tsp").
extern const std::unordered_map<std::string, UnitInfo> UNIT_TABLE;

/// Normalize a unit string: lowercase and strip leading/trailing whitespace.
std::string normalize_unit(const std::string& unit);

/// Look up the UnitType for a (possibly un-normalized) unit string.
/// @throws std::invalid_argument if the unit is not recognized.
UnitType get_unit_type(const std::string& unit);

} // namespace lethimcook

#endif // LETHIMCOOK_UNITS_HPP
