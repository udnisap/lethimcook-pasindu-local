#include "lethimcook/converter.hpp"
#include "lethimcook/units.hpp"

#include <stdexcept>

namespace lethimcook {

// ---------------------------------------------------------------------------
// Internal: temperature conversion via Celsius as intermediate.
// ---------------------------------------------------------------------------
static double convert_temperature(double value,
                                  const std::string& from_unit,
                                  const std::string& to_unit) {
    // Step 1: convert to Celsius
    double celsius = 0.0;
    if (from_unit == "celsius" || from_unit == "c") {
        celsius = value;
    } else if (from_unit == "fahrenheit" || from_unit == "f") {
        celsius = (value - 32.0) * 5.0 / 9.0;
    } else if (from_unit == "kelvin" || from_unit == "k") {
        celsius = value - 273.15;
    } else {
        throw std::invalid_argument("Unknown temperature unit: " + from_unit);
    }

    // Step 2: convert from Celsius to target
    if (to_unit == "celsius" || to_unit == "c") {
        return celsius;
    } else if (to_unit == "fahrenheit" || to_unit == "f") {
        return celsius * 9.0 / 5.0 + 32.0;
    } else if (to_unit == "kelvin" || to_unit == "k") {
        return celsius + 273.15;
    } else {
        throw std::invalid_argument("Unknown temperature unit: " + to_unit);
    }
}

// ---------------------------------------------------------------------------
// convert
// ---------------------------------------------------------------------------
double convert(double value,
               const std::string& from_unit,
               const std::string& to_unit) {
    // Normalize inputs
    std::string from = normalize_unit(from_unit);
    std::string to   = normalize_unit(to_unit);

    // Look up unit types (throws on unknown unit)
    UnitType from_type = get_unit_type(from);
    UnitType to_type   = get_unit_type(to);

    // Check compatibility
    if (from_type != to_type) {
        throw std::invalid_argument(
            "Cannot convert between " + unit_type_to_string(from_type) +
            " and " + unit_type_to_string(to_type));
    }

    // Temperature: non-linear, handled separately
    if (from_type == UnitType::Temperature) {
        return convert_temperature(value, from, to);
    }

    // Count: dimensionless, pass through
    if (from_type == UnitType::Count) {
        return value;
    }

    // Volume / Weight: from_unit → base → to_unit
    double from_factor = UNIT_TABLE.at(from).to_base_factor;
    double to_factor   = UNIT_TABLE.at(to).to_base_factor;
    double base_value  = value * from_factor;
    return base_value / to_factor;
}

} // namespace lethimcook
