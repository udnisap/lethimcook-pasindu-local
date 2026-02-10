// natural.hpp - Natural language parsing API
#ifndef LETHIMCOOK_NATURAL_HPP
#define LETHIMCOOK_NATURAL_HPP

#include <string>
#include <optional>

namespace lethimcook {

// Parsed conversion request structure - to be implemented in future tasks
struct ParsedRequest {
    double amount;
    std::string src_unit;
    std::optional<std::string> ingredient_name;
    std::string dst_unit;
};

// Parse natural language input - to be implemented in future tasks
std::optional<ParsedRequest> parse_request(const std::string& input);

// End-to-end natural language conversion - to be implemented in future tasks
std::string convert_natural(const std::string& text);

} // namespace lethimcook

#endif // LETHIMCOOK_NATURAL_HPP
