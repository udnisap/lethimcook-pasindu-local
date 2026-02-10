// converter.cpp - Unit conversion implementation
#include "lethimcook/converter.hpp"
#include "lethimcook/units.hpp"
#include <stdexcept>
#include <string>

namespace lethimcook {

namespace {

/**
 * Convert temperature between different scales.
 * Uses Celsius as the intermediate value.
 * @param value The temperature value to convert
 * @param from_unit The source temperature unit (normalized)
 * @param to_unit The target temperature unit (normalized)
 * @return The converted temperature value
 * @throws std::invalid_argument If the temperature unit is unknown
 */
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
    // Normalize units
    std::string norm_from = normalize_unit(from_unit);
    std::string norm_to = normalize_unit(to_unit);

    // Get unit types
    UnitType from_type = get_unit_type(norm_from);
    UnitType to_type = get_unit_type(norm_to);

    // Check compatibility
    if (from_type != to_type) {
        // Build a human-readable type name for the error message
        auto type_name = [](UnitType t) -> std::string {
            switch (t) {
                case UnitType::Volume: return "UnitType.VOLUME";
                case UnitType::Weight: return "UnitType.WEIGHT";
                case UnitType::Temperature: return "UnitType.TEMPERATURE";
                case UnitType::Count: return "UnitType.COUNT";
                default: return "unknown";
            }
        };
        throw std::invalid_argument("Cannot convert between " + type_name(from_type) + " and " + type_name(to_type));
    }

    // Handle temperature separately (non-linear conversion)
    if (from_type == UnitType::Temperature) {
        return convert_temperature(value, norm_from, norm_to);
    }

    // Handle count (no conversion needed)
    if (from_type == UnitType::Count) {
        return value;
    }

    // Convert: from_unit -> base_unit -> to_unit
    // For volume: base is ml
    // For weight: base is grams
    double from_factor = get_conversion_factor(norm_from);
    double to_factor = get_conversion_factor(norm_to);

    double base_value = value * from_factor;
    double result = base_value / to_factor;

    return result;
}

} // namespace lethimcook
