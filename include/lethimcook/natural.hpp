// natural.hpp - Natural language parsing API
#ifndef LETHIMCOOK_NATURAL_HPP
#define LETHIMCOOK_NATURAL_HPP

#include <string>
#include <optional>

namespace lethimcook {

/**
 * Parsed conversion request structure.
 * Contains the extracted components from a natural language conversion request.
 */
struct ParsedRequest {
    double amount;
    std::string src_unit;
    std::optional<std::string> ingredient_name;
    std::string dst_unit;
};

/**
 * Parse natural language input into a structured ParsedRequest.
 *
 * @param input The natural language string to parse
 * @return Optional containing ParsedRequest if successful, std::nullopt if parsing fails
 */
std::optional<ParsedRequest> parse_request(const std::string& input);

/**
 * Convert using natural language input.
 *
 * Supports patterns like:
 * - "2 cups to ml"
 * - "convert 1.5 pounds to grams"
 * - "how many ml in 3 teaspoons"
 * - "5 fahrenheit to celsius"
 *
 * @param text Natural language conversion request
 * @return Formatted string with conversion result
 * @throws std::invalid_argument If the input cannot be parsed or units are invalid
 */
std::string convert_natural(const std::string& text);

} // namespace lethimcook

#endif // LETHIMCOOK_NATURAL_HPP
