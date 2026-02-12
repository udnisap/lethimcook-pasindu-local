#include "lethimcook/units.hpp"

#include <algorithm>
#include <cctype>

namespace lethimcook {

std::string to_string(UnitCategory category) {
    switch (category) {
        case UnitCategory::Volume:      return "volume";
        case UnitCategory::Weight:      return "weight";
        case UnitCategory::Temperature: return "temperature";
        case UnitCategory::Count:       return "count";
    }
    return "unknown";
}

// Conversion factors to base units.
// Volume base unit: ml, Weight base unit: g, Count base unit: count.
// Temperature units are NOT included here (handled with special-case logic).
const std::unordered_map<std::string, double> CONVERSIONS = {
    // Volume (to milliliters)
    {"tsp",           4.92892},
    {"teaspoon",      4.92892},
    {"teaspoons",     4.92892},
    {"tbsp",          14.7868},
    {"tablespoon",    14.7868},
    {"tablespoons",   14.7868},
    {"floz",          29.5735},
    {"fl oz",         29.5735},
    {"fluid ounce",   29.5735},
    {"fluid ounces",  29.5735},
    {"cup",           236.588},
    {"cups",          236.588},
    {"pint",          473.176},
    {"pints",         473.176},
    {"quart",         946.353},
    {"quarts",        946.353},
    {"gallon",        3785.41},
    {"gallons",       3785.41},
    {"ml",            1.0},
    {"milliliter",    1.0},
    {"milliliters",   1.0},
    {"l",             1000.0},
    {"liter",         1000.0},
    {"liters",        1000.0},

    // Weight (to grams)
    {"oz",            28.3495},
    {"ounce",         28.3495},
    {"ounces",        28.3495},
    {"lb",            453.592},
    {"lbs",           453.592},
    {"pound",         453.592},
    {"pounds",        453.592},
    {"g",             1.0},
    {"gram",          1.0},
    {"grams",         1.0},
    {"kg",            1000.0},
    {"kilogram",      1000.0},
    {"kilograms",     1000.0},

    // Count (dimensionless)
    {"count",         1.0},
    {"item",          1.0},
    {"items",         1.0},
    {"piece",         1.0},
    {"pieces",        1.0},
    {"whole",         1.0},
};

// Unit type mapping: unit string -> UnitCategory
const std::unordered_map<std::string, UnitCategory> UNIT_TYPES = {
    // Volume
    {"tsp",           UnitCategory::Volume},
    {"teaspoon",      UnitCategory::Volume},
    {"teaspoons",     UnitCategory::Volume},
    {"tbsp",          UnitCategory::Volume},
    {"tablespoon",    UnitCategory::Volume},
    {"tablespoons",   UnitCategory::Volume},
    {"floz",          UnitCategory::Volume},
    {"fl oz",         UnitCategory::Volume},
    {"fluid ounce",   UnitCategory::Volume},
    {"fluid ounces",  UnitCategory::Volume},
    {"cup",           UnitCategory::Volume},
    {"cups",          UnitCategory::Volume},
    {"pint",          UnitCategory::Volume},
    {"pints",         UnitCategory::Volume},
    {"quart",         UnitCategory::Volume},
    {"quarts",        UnitCategory::Volume},
    {"gallon",        UnitCategory::Volume},
    {"gallons",       UnitCategory::Volume},
    {"ml",            UnitCategory::Volume},
    {"milliliter",    UnitCategory::Volume},
    {"milliliters",   UnitCategory::Volume},
    {"l",             UnitCategory::Volume},
    {"liter",         UnitCategory::Volume},
    {"liters",        UnitCategory::Volume},

    // Weight
    {"oz",            UnitCategory::Weight},
    {"ounce",         UnitCategory::Weight},
    {"ounces",        UnitCategory::Weight},
    {"lb",            UnitCategory::Weight},
    {"lbs",           UnitCategory::Weight},
    {"pound",         UnitCategory::Weight},
    {"pounds",        UnitCategory::Weight},
    {"g",             UnitCategory::Weight},
    {"gram",          UnitCategory::Weight},
    {"grams",         UnitCategory::Weight},
    {"kg",            UnitCategory::Weight},
    {"kilogram",      UnitCategory::Weight},
    {"kilograms",     UnitCategory::Weight},

    // Temperature
    {"fahrenheit",    UnitCategory::Temperature},
    {"f",             UnitCategory::Temperature},
    {"celsius",       UnitCategory::Temperature},
    {"c",             UnitCategory::Temperature},
    {"kelvin",        UnitCategory::Temperature},
    {"k",             UnitCategory::Temperature},

    // Count
    {"count",         UnitCategory::Count},
    {"item",          UnitCategory::Count},
    {"items",         UnitCategory::Count},
    {"piece",         UnitCategory::Count},
    {"pieces",        UnitCategory::Count},
    {"whole",         UnitCategory::Count},
};

std::string normalize_unit(const std::string& unit) {
    std::string result;
    result.reserve(unit.size());

    // Find first non-whitespace
    auto start = unit.begin();
    while (start != unit.end() && std::isspace(static_cast<unsigned char>(*start))) {
        ++start;
    }
    // Find last non-whitespace
    auto end = unit.end();
    while (end != start && std::isspace(static_cast<unsigned char>(*(end - 1)))) {
        --end;
    }

    for (auto it = start; it != end; ++it) {
        result += static_cast<char>(std::tolower(static_cast<unsigned char>(*it)));
    }

    return result;
}

UnitCategory get_unit_type(const std::string& unit) {
    std::string normalized = normalize_unit(unit);
    auto it = UNIT_TYPES.find(normalized);
    if (it == UNIT_TYPES.end()) {
        throw std::invalid_argument("Unknown unit: " + unit);
    }
    return it->second;
}

} // namespace lethimcook
