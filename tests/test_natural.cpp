// test_natural.cpp - Tests for the natural language parsing module
#include <gtest/gtest.h>
#include "lethimcook/natural.hpp"
#include <string>
#include <algorithm>
#include <cctype>

namespace lethimcook {
namespace test {

// Helper function to convert string to lowercase
std::string to_lower(const std::string& s) {
    std::string result;
    result.reserve(s.size());
    for (char c : s) {
        result.push_back(static_cast<char>(std::tolower(static_cast<unsigned char>(c))));
    }
    return result;
}

// =============================================================================
// Tests for natural language patterns (mirrors TestNaturalLanguagePatterns in Python)
// =============================================================================

class TestNaturalLanguagePatterns : public ::testing::Test {};

TEST_F(TestNaturalLanguagePatterns, BasicToPattern) {
    std::string result = convert_natural("2 cups to ml");
    std::string lower_result = to_lower(result);
    EXPECT_TRUE(lower_result.find("2 cups") != std::string::npos)
        << "Result should contain '2 cups': " << result;
    EXPECT_TRUE(lower_result.find("ml") != std::string::npos)
        << "Result should contain 'ml': " << result;
    EXPECT_TRUE(result.find("473") != std::string::npos)
        << "Result should contain '473': " << result;
}

TEST_F(TestNaturalLanguagePatterns, ConvertPattern) {
    std::string result = convert_natural("convert 1 pound to grams");
    std::string lower_result = to_lower(result);
    EXPECT_TRUE(lower_result.find("1 pound") != std::string::npos)
        << "Result should contain '1 pound': " << result;
    EXPECT_TRUE(lower_result.find("gram") != std::string::npos)
        << "Result should contain 'gram': " << result;
    EXPECT_TRUE(result.find("453") != std::string::npos)
        << "Result should contain '453': " << result;
}

TEST_F(TestNaturalLanguagePatterns, HowManyPattern) {
    std::string result = convert_natural("how many ml in 3 teaspoons");
    std::string lower_result = to_lower(result);
    EXPECT_TRUE(lower_result.find("3 teaspoon") != std::string::npos)
        << "Result should contain '3 teaspoon': " << result;
    EXPECT_TRUE(lower_result.find("ml") != std::string::npos)
        << "Result should contain 'ml': " << result;
}

TEST_F(TestNaturalLanguagePatterns, DecimalValues) {
    std::string result = convert_natural("1.5 cups to ml");
    EXPECT_TRUE(result.find("1.5") != std::string::npos)
        << "Result should contain '1.5': " << result;
}

TEST_F(TestNaturalLanguagePatterns, TemperatureConversion) {
    std::string result = convert_natural("350 fahrenheit to celsius");
    std::string lower_result = to_lower(result);
    EXPECT_TRUE(result.find("350") != std::string::npos)
        << "Result should contain '350': " << result;
    EXPECT_TRUE(lower_result.find("fahrenheit") != std::string::npos)
        << "Result should contain 'fahrenheit': " << result;
    EXPECT_TRUE(lower_result.find("celsius") != std::string::npos)
        << "Result should contain 'celsius': " << result;
}

TEST_F(TestNaturalLanguagePatterns, CaseInsensitive) {
    std::string result1 = convert_natural("2 CUPS to ML");
    std::string result2 = convert_natural("2 cups to ml");
    // Both should contain the same numeric result
    EXPECT_TRUE(result1.find("473") != std::string::npos)
        << "Result1 should contain '473': " << result1;
    EXPECT_TRUE(result2.find("473") != std::string::npos)
        << "Result2 should contain '473': " << result2;
}

TEST_F(TestNaturalLanguagePatterns, MultiWordUnits) {
    std::string result = convert_natural("5 fluid ounce to ml");
    std::string lower_result = to_lower(result);
    EXPECT_TRUE(lower_result.find("fluid ounce") != std::string::npos)
        << "Result should contain 'fluid ounce': " << result;
    EXPECT_TRUE(lower_result.find("ml") != std::string::npos)
        << "Result should contain 'ml': " << result;
}

// =============================================================================
// Tests for natural language errors (mirrors TestNaturalLanguageErrors in Python)
// =============================================================================

class TestNaturalLanguageErrors : public ::testing::Test {};

TEST_F(TestNaturalLanguageErrors, UnparseableInput) {
    try {
        convert_natural("this is gibberish");
        FAIL() << "Expected std::invalid_argument";
    } catch (const std::invalid_argument& e) {
        std::string msg = e.what();
        EXPECT_TRUE(msg.find("Could not parse") != std::string::npos)
            << "Error message should contain 'Could not parse': " << msg;
    }
}

TEST_F(TestNaturalLanguageErrors, MissingValue) {
    EXPECT_THROW(convert_natural("cups to ml"), std::invalid_argument);
}

TEST_F(TestNaturalLanguageErrors, InvalidUnit) {
    EXPECT_THROW(convert_natural("2 blorg to ml"), std::invalid_argument);
}

// =============================================================================
// Additional tests for parse_request function
// =============================================================================

class TestParseRequest : public ::testing::Test {};

TEST_F(TestParseRequest, BasicPattern) {
    auto result = parse_request("2 cups to ml");
    ASSERT_TRUE(result.has_value());
    EXPECT_DOUBLE_EQ(result->amount, 2.0);
    EXPECT_EQ(result->src_unit, "cups");
    EXPECT_EQ(result->dst_unit, "ml");
}

TEST_F(TestParseRequest, ConvertPattern) {
    auto result = parse_request("convert 1.5 pounds to grams");
    ASSERT_TRUE(result.has_value());
    EXPECT_DOUBLE_EQ(result->amount, 1.5);
    EXPECT_EQ(result->src_unit, "pounds");
    EXPECT_EQ(result->dst_unit, "grams");
}

TEST_F(TestParseRequest, HowManyPattern) {
    auto result = parse_request("how many ml in 3 teaspoons");
    ASSERT_TRUE(result.has_value());
    EXPECT_DOUBLE_EQ(result->amount, 3.0);
    EXPECT_EQ(result->src_unit, "teaspoons");
    EXPECT_EQ(result->dst_unit, "ml");
}

TEST_F(TestParseRequest, UnparseableReturnsNullopt) {
    auto result = parse_request("gibberish");
    EXPECT_FALSE(result.has_value());
}

TEST_F(TestParseRequest, InPatternWorks) {
    auto result = parse_request("5 cups in ml");
    ASSERT_TRUE(result.has_value());
    EXPECT_DOUBLE_EQ(result->amount, 5.0);
    EXPECT_EQ(result->src_unit, "cups");
    EXPECT_EQ(result->dst_unit, "ml");
}

} // namespace test
} // namespace lethimcook
