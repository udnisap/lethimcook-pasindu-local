// natural.cpp - Natural language parsing implementation
#include "lethimcook/natural.hpp"
#include "lethimcook/converter.hpp"
#include <stdexcept>
#include <regex>
#include <algorithm>
#include <cctype>
#include <sstream>
#include <iomanip>
#include <cmath>

namespace lethimcook {

namespace {

/**
 * Format a number, removing .0 for integers.
 * @param value The number to format
 * @return String representation
 */
std::string format_number(double value) {
    // Check if value is effectively an integer
    if (value == static_cast<int>(value)) {
        return std::to_string(static_cast<int>(value));
    }
    // For non-integers, preserve the decimal part as in the input
    std::ostringstream oss;
    oss << value;
    return oss.str();
}

/**
 * Convert a string to lowercase.
 * @param s The input string
 * @return Lowercase version of the string
 */
std::string to_lower(const std::string& s) {
    std::string result;
    result.reserve(s.size());
    for (char c : s) {
        result.push_back(static_cast<char>(std::tolower(static_cast<unsigned char>(c))));
    }
    return result;
}

/**
 * Trim whitespace from both ends of a string.
 * @param s The input string
 * @return Trimmed string
 */
std::string trim(const std::string& s) {
    auto start = s.begin();
    while (start != s.end() && std::isspace(static_cast<unsigned char>(*start))) {
        ++start;
    }

    auto end = s.end();
    while (end != start && std::isspace(static_cast<unsigned char>(*(end - 1)))) {
        --end;
    }

    return std::string(start, end);
}

} // anonymous namespace

std::optional<ParsedRequest> parse_request(const std::string& input) {
    std::string text = trim(to_lower(input));

    // Static regex patterns - compiled once on first call
    // Pattern 1: "X unit to unit" or "X unit in unit"
    static const std::regex pattern1(R"((\d+\.?\d*)\s+([a-z\s]+?)\s+(?:to|in)\s+([a-z\s]+))");
    // Pattern 2: "convert X unit to unit"
    static const std::regex pattern2(R"(convert\s+(\d+\.?\d*)\s+([a-z\s]+?)\s+to\s+([a-z\s]+))");
    // Pattern 3: "how many unit in X unit"
    static const std::regex pattern3(R"(how\s+many\s+([a-z\s]+?)\s+in\s+(\d+\.?\d*)\s+([a-z\s]+))");

    std::smatch match;

    // Try Pattern 1: "X unit to unit"
    if (std::regex_match(text, match, pattern1)) {
        ParsedRequest req;
        req.amount = std::stod(match[1].str());
        req.src_unit = trim(match[2].str());
        req.dst_unit = trim(match[3].str());
        return req;
    }

    // Try Pattern 2: "convert X unit to unit"
    if (std::regex_match(text, match, pattern2)) {
        ParsedRequest req;
        req.amount = std::stod(match[1].str());
        req.src_unit = trim(match[2].str());
        req.dst_unit = trim(match[3].str());
        return req;
    }

    // Try Pattern 3: "how many unit in X unit"
    if (std::regex_match(text, match, pattern3)) {
        ParsedRequest req;
        req.dst_unit = trim(match[1].str());
        req.amount = std::stod(match[2].str());
        req.src_unit = trim(match[3].str());
        return req;
    }

    return std::nullopt;
}

std::string convert_natural(const std::string& text) {
    auto parsed_opt = parse_request(text);

    if (!parsed_opt) {
        std::string input_text = trim(to_lower(text));
        throw std::invalid_argument(
            "Could not parse conversion request: " + input_text + "\n"
            "Try formats like: '2 cups to ml' or 'convert 1 pound to grams'"
        );
    }

    const ParsedRequest& parsed = *parsed_opt;

    // Perform the conversion
    double result = convert(parsed.amount, parsed.src_unit, parsed.dst_unit);

    // Format output: "{value} {from_unit} = {result:.2f} {to_unit}"
    std::ostringstream oss;
    oss << format_number(parsed.amount) << " " << parsed.src_unit << " = "
        << std::fixed << std::setprecision(2) << result << " " << parsed.dst_unit;

    return oss.str();
}

} // namespace lethimcook
