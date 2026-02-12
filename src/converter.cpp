#include "lethimcook/converter.hpp"
#include "lethimcook/units.hpp"

namespace lethimcook {

namespace {

/// Convert temperature between different scales.
/// All conversions go through Celsius as the intermediate.
double convert_temperature(double value, const std::string& from_unit, const std::string& to_unit) {
    // First convert to Celsius
    double celsius;
    if (from_unit == "celsius" || from_unit == "c") {
        celsius = value;
    } else if (from_unit == "fahrenheit" || from_unit == "f") {
        celsius = (value - 32.0) * 5.0 / 9.0;
    } else if (from_unit == "kelvin" || from_unit == "k") {
        celsius = value - 273.15;
    } else {
        throw std::invalid_argument("Unknown temperature unit: " + from_unit);
    }

    // Then convert from Celsius to target
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

} // anonymous namespace

double convert(double value, const std::string& from_unit, const std::string& to_unit) {
    std::string from_normalized = normalize_unit(from_unit);
    std::string to_normalized = normalize_unit(to_unit);

    // Get unit types (throws if unknown)
    UnitCategory from_type = get_unit_type(from_normalized);
    UnitCategory to_type = get_unit_type(to_normalized);

    // Check compatibility
    if (from_type != to_type) {
        throw std::invalid_argument(
            "Cannot convert between " + to_string(from_type) + " and " + to_string(to_type)
        );
    }

    // Handle temperature separately (non-linear conversion)
    if (from_type == UnitCategory::Temperature) {
        return convert_temperature(value, from_normalized, to_normalized);
    }

    // Handle count (no conversion needed)
    if (from_type == UnitCategory::Count) {
        return value;
    }

    // Convert: from_unit -> base_unit -> to_unit
    double base_value = value * CONVERSIONS.at(from_normalized);
    double result = base_value / CONVERSIONS.at(to_normalized);

    return result;
}

} // namespace lethimcook
