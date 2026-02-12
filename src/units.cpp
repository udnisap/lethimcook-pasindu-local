#include "lethimcook/units.hpp"

#include <algorithm>
#include <cctype>
#include <stdexcept>

namespace lethimcook {

// ---------------------------------------------------------------------------
// unit_type_to_string
// ---------------------------------------------------------------------------
std::string unit_type_to_string(UnitType type) {
    switch (type) {
        case UnitType::Volume:      return "volume";
        case UnitType::Weight:      return "weight";
        case UnitType::Temperature: return "temperature";
        case UnitType::Count:       return "count";
    }
    return "unknown";
}

// ---------------------------------------------------------------------------
// UNIT_TABLE  –  single map that stores category + conversion factor for every
//                recognized unit string.  Temperature entries use factor 0.0
//                because their conversions are non-linear.
// ---------------------------------------------------------------------------
const std::unordered_map<std::string, UnitInfo> UNIT_TABLE = {
    // ── Volume (factor → milliliters) ──────────────────────────────────────
    {"tsp",           {UnitType::Volume, 4.92892}},
    {"teaspoon",      {UnitType::Volume, 4.92892}},
    {"teaspoons",     {UnitType::Volume, 4.92892}},
    {"tbsp",          {UnitType::Volume, 14.7868}},
    {"tablespoon",    {UnitType::Volume, 14.7868}},
    {"tablespoons",   {UnitType::Volume, 14.7868}},
    {"floz",          {UnitType::Volume, 29.5735}},
    {"fl oz",         {UnitType::Volume, 29.5735}},
    {"fluid ounce",   {UnitType::Volume, 29.5735}},
    {"fluid ounces",  {UnitType::Volume, 29.5735}},
    {"cup",           {UnitType::Volume, 236.588}},
    {"cups",          {UnitType::Volume, 236.588}},
    {"pint",          {UnitType::Volume, 473.176}},
    {"pints",         {UnitType::Volume, 473.176}},
    {"quart",         {UnitType::Volume, 946.353}},
    {"quarts",        {UnitType::Volume, 946.353}},
    {"gallon",        {UnitType::Volume, 3785.41}},
    {"gallons",       {UnitType::Volume, 3785.41}},
    {"ml",            {UnitType::Volume, 1.0}},
    {"milliliter",    {UnitType::Volume, 1.0}},
    {"milliliters",   {UnitType::Volume, 1.0}},
    {"l",             {UnitType::Volume, 1000.0}},
    {"liter",         {UnitType::Volume, 1000.0}},
    {"liters",        {UnitType::Volume, 1000.0}},

    // ── Weight (factor → grams) ────────────────────────────────────────────
    {"oz",            {UnitType::Weight, 28.3495}},
    {"ounce",         {UnitType::Weight, 28.3495}},
    {"ounces",        {UnitType::Weight, 28.3495}},
    {"lb",            {UnitType::Weight, 453.592}},
    {"lbs",           {UnitType::Weight, 453.592}},
    {"pound",         {UnitType::Weight, 453.592}},
    {"pounds",        {UnitType::Weight, 453.592}},
    {"g",             {UnitType::Weight, 1.0}},
    {"gram",          {UnitType::Weight, 1.0}},
    {"grams",         {UnitType::Weight, 1.0}},
    {"kg",            {UnitType::Weight, 1000.0}},
    {"kilogram",      {UnitType::Weight, 1000.0}},
    {"kilograms",     {UnitType::Weight, 1000.0}},

    // ── Temperature (factor is unused; conversion is non-linear) ───────────
    {"fahrenheit",    {UnitType::Temperature, 0.0}},
    {"f",             {UnitType::Temperature, 0.0}},
    {"celsius",       {UnitType::Temperature, 0.0}},
    {"c",             {UnitType::Temperature, 0.0}},
    {"kelvin",        {UnitType::Temperature, 0.0}},
    {"k",             {UnitType::Temperature, 0.0}},

    // ── Count (dimensionless) ──────────────────────────────────────────────
    {"count",         {UnitType::Count, 1.0}},
    {"item",          {UnitType::Count, 1.0}},
    {"items",         {UnitType::Count, 1.0}},
    {"piece",         {UnitType::Count, 1.0}},
    {"pieces",        {UnitType::Count, 1.0}},
    {"whole",         {UnitType::Count, 1.0}},
};

// ---------------------------------------------------------------------------
// normalize_unit  –  lowercase + strip whitespace
// ---------------------------------------------------------------------------
std::string normalize_unit(const std::string& unit) {
    std::string result;
    result.reserve(unit.size());

    // Find first non-space
    auto start = unit.begin();
    while (start != unit.end() && std::isspace(static_cast<unsigned char>(*start))) {
        ++start;
    }
    // Find last non-space
    auto end = unit.end();
    while (end != start && std::isspace(static_cast<unsigned char>(*(end - 1)))) {
        --end;
    }

    for (auto it = start; it != end; ++it) {
        result += static_cast<char>(std::tolower(static_cast<unsigned char>(*it)));
    }
    return result;
}

// ---------------------------------------------------------------------------
// get_unit_type
// ---------------------------------------------------------------------------
UnitType get_unit_type(const std::string& unit) {
    std::string normalized = normalize_unit(unit);
    auto it = UNIT_TABLE.find(normalized);
    if (it == UNIT_TABLE.end()) {
        throw std::invalid_argument("Unknown unit: " + unit);
    }
    return it->second.category;
}

} // namespace lethimcook
