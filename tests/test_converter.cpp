// test_converter.cpp - Tests for the units and converter modules
#include <gtest/gtest.h>
#include "lethimcook/units.hpp"
#include "lethimcook/converter.hpp"
#include <cmath>

namespace lethimcook {
namespace test {

// =============================================================================
// Tests for normalize_unit()
// =============================================================================

class NormalizeUnitTest : public ::testing::Test {};

TEST_F(NormalizeUnitTest, LowercasesString) {
    EXPECT_EQ(normalize_unit("CUP"), "cup");
    EXPECT_EQ(normalize_unit("TABLESPOON"), "tablespoon");
    EXPECT_EQ(normalize_unit("Gram"), "gram");
    EXPECT_EQ(normalize_unit("MiLLiLiTeRs"), "milliliters");
}

TEST_F(NormalizeUnitTest, StripsLeadingWhitespace) {
    EXPECT_EQ(normalize_unit("  cup"), "cup");
    EXPECT_EQ(normalize_unit("   tablespoon"), "tablespoon");
    EXPECT_EQ(normalize_unit("\tcup"), "cup");
    EXPECT_EQ(normalize_unit("\n\tcup"), "cup");
}

TEST_F(NormalizeUnitTest, StripsTrailingWhitespace) {
    EXPECT_EQ(normalize_unit("cup  "), "cup");
    EXPECT_EQ(normalize_unit("tablespoon   "), "tablespoon");
    EXPECT_EQ(normalize_unit("cup\t"), "cup");
    EXPECT_EQ(normalize_unit("cup\n"), "cup");
}

TEST_F(NormalizeUnitTest, StripsBothSidesAndLowercases) {
    EXPECT_EQ(normalize_unit("  CUP  "), "cup");
    EXPECT_EQ(normalize_unit(" TABLESPOON "), "tablespoon");
    EXPECT_EQ(normalize_unit("\t Gram \n"), "gram");
}

TEST_F(NormalizeUnitTest, HandlesEmptyAndWhitespaceOnlyStrings) {
    EXPECT_EQ(normalize_unit(""), "");
    EXPECT_EQ(normalize_unit("   "), "");
    EXPECT_EQ(normalize_unit("\t\n "), "");
}

TEST_F(NormalizeUnitTest, PreservesSpacesWithinUnitName) {
    EXPECT_EQ(normalize_unit("fl oz"), "fl oz");
    EXPECT_EQ(normalize_unit("  FL OZ  "), "fl oz");
    EXPECT_EQ(normalize_unit("fluid ounce"), "fluid ounce");
    EXPECT_EQ(normalize_unit("  FLUID OUNCES  "), "fluid ounces");
}

// =============================================================================
// Tests for get_unit_type()
// =============================================================================

class GetUnitTypeTest : public ::testing::Test {};

// Volume units
TEST_F(GetUnitTypeTest, ReturnsVolumeForVolumeUnits) {
    EXPECT_EQ(get_unit_type("cup"), UnitType::Volume);
    EXPECT_EQ(get_unit_type("cups"), UnitType::Volume);
    EXPECT_EQ(get_unit_type("tsp"), UnitType::Volume);
    EXPECT_EQ(get_unit_type("teaspoon"), UnitType::Volume);
    EXPECT_EQ(get_unit_type("teaspoons"), UnitType::Volume);
    EXPECT_EQ(get_unit_type("tbsp"), UnitType::Volume);
    EXPECT_EQ(get_unit_type("tablespoon"), UnitType::Volume);
    EXPECT_EQ(get_unit_type("tablespoons"), UnitType::Volume);
    EXPECT_EQ(get_unit_type("floz"), UnitType::Volume);
    EXPECT_EQ(get_unit_type("fl oz"), UnitType::Volume);
    EXPECT_EQ(get_unit_type("fluid ounce"), UnitType::Volume);
    EXPECT_EQ(get_unit_type("fluid ounces"), UnitType::Volume);
    EXPECT_EQ(get_unit_type("pint"), UnitType::Volume);
    EXPECT_EQ(get_unit_type("pints"), UnitType::Volume);
    EXPECT_EQ(get_unit_type("quart"), UnitType::Volume);
    EXPECT_EQ(get_unit_type("quarts"), UnitType::Volume);
    EXPECT_EQ(get_unit_type("gallon"), UnitType::Volume);
    EXPECT_EQ(get_unit_type("gallons"), UnitType::Volume);
    EXPECT_EQ(get_unit_type("ml"), UnitType::Volume);
    EXPECT_EQ(get_unit_type("milliliter"), UnitType::Volume);
    EXPECT_EQ(get_unit_type("milliliters"), UnitType::Volume);
    EXPECT_EQ(get_unit_type("l"), UnitType::Volume);
    EXPECT_EQ(get_unit_type("liter"), UnitType::Volume);
    EXPECT_EQ(get_unit_type("liters"), UnitType::Volume);
}

// Weight units
TEST_F(GetUnitTypeTest, ReturnsWeightForWeightUnits) {
    EXPECT_EQ(get_unit_type("gram"), UnitType::Weight);
    EXPECT_EQ(get_unit_type("grams"), UnitType::Weight);
    EXPECT_EQ(get_unit_type("g"), UnitType::Weight);
    EXPECT_EQ(get_unit_type("kg"), UnitType::Weight);
    EXPECT_EQ(get_unit_type("kilogram"), UnitType::Weight);
    EXPECT_EQ(get_unit_type("kilograms"), UnitType::Weight);
    EXPECT_EQ(get_unit_type("oz"), UnitType::Weight);
    EXPECT_EQ(get_unit_type("ounce"), UnitType::Weight);
    EXPECT_EQ(get_unit_type("ounces"), UnitType::Weight);
    EXPECT_EQ(get_unit_type("lb"), UnitType::Weight);
    EXPECT_EQ(get_unit_type("lbs"), UnitType::Weight);
    EXPECT_EQ(get_unit_type("pound"), UnitType::Weight);
    EXPECT_EQ(get_unit_type("pounds"), UnitType::Weight);
}

// Temperature units
TEST_F(GetUnitTypeTest, ReturnsTemperatureForTemperatureUnits) {
    EXPECT_EQ(get_unit_type("celsius"), UnitType::Temperature);
    EXPECT_EQ(get_unit_type("c"), UnitType::Temperature);
    EXPECT_EQ(get_unit_type("fahrenheit"), UnitType::Temperature);
    EXPECT_EQ(get_unit_type("f"), UnitType::Temperature);
    EXPECT_EQ(get_unit_type("kelvin"), UnitType::Temperature);
    EXPECT_EQ(get_unit_type("k"), UnitType::Temperature);
}

// Count units
TEST_F(GetUnitTypeTest, ReturnsCountForCountUnits) {
    EXPECT_EQ(get_unit_type("count"), UnitType::Count);
    EXPECT_EQ(get_unit_type("item"), UnitType::Count);
    EXPECT_EQ(get_unit_type("items"), UnitType::Count);
    EXPECT_EQ(get_unit_type("piece"), UnitType::Count);
    EXPECT_EQ(get_unit_type("pieces"), UnitType::Count);
    EXPECT_EQ(get_unit_type("whole"), UnitType::Count);
}

// Case insensitivity
TEST_F(GetUnitTypeTest, HandlesUnitVariationsWithCase) {
    EXPECT_EQ(get_unit_type("Cup"), UnitType::Volume);
    EXPECT_EQ(get_unit_type("CUP"), UnitType::Volume);
    EXPECT_EQ(get_unit_type("GRAM"), UnitType::Weight);
    EXPECT_EQ(get_unit_type("Celsius"), UnitType::Temperature);
}

// Whitespace handling
TEST_F(GetUnitTypeTest, HandlesWhitespaceInInput) {
    EXPECT_EQ(get_unit_type("  cup  "), UnitType::Volume);
    EXPECT_EQ(get_unit_type("\tgram"), UnitType::Weight);
}

// =============================================================================
// Tests for unknown unit error handling
// =============================================================================

class UnknownUnitTest : public ::testing::Test {};

TEST_F(UnknownUnitTest, ThrowsForUnknownUnit) {
    EXPECT_THROW(get_unit_type("blorg"), std::invalid_argument);
    EXPECT_THROW(get_unit_type("unknown"), std::invalid_argument);
    EXPECT_THROW(get_unit_type("xyz"), std::invalid_argument);
}

TEST_F(UnknownUnitTest, ErrorMessageContainsUnknownUnit) {
    try {
        get_unit_type("blorg");
        FAIL() << "Expected std::invalid_argument";
    } catch (const std::invalid_argument& e) {
        std::string msg = e.what();
        EXPECT_TRUE(msg.find("Unknown unit") != std::string::npos)
            << "Error message should contain 'Unknown unit': " << msg;
        EXPECT_TRUE(msg.find("blorg") != std::string::npos)
            << "Error message should contain the unit name 'blorg': " << msg;
    }
}

// =============================================================================
// Tests for get_conversion_factor()
// =============================================================================

class GetConversionFactorTest : public ::testing::Test {};

TEST_F(GetConversionFactorTest, ReturnsCorrectFactorForVolumeUnits) {
    EXPECT_NEAR(get_conversion_factor("tsp"), 4.92892, 0.00001);
    EXPECT_NEAR(get_conversion_factor("tbsp"), 14.7868, 0.00001);
    EXPECT_NEAR(get_conversion_factor("cup"), 236.588, 0.001);
    EXPECT_NEAR(get_conversion_factor("ml"), 1.0, 0.00001);
    EXPECT_NEAR(get_conversion_factor("l"), 1000.0, 0.00001);
}

TEST_F(GetConversionFactorTest, ReturnsCorrectFactorForWeightUnits) {
    EXPECT_NEAR(get_conversion_factor("g"), 1.0, 0.00001);
    EXPECT_NEAR(get_conversion_factor("kg"), 1000.0, 0.00001);
    EXPECT_NEAR(get_conversion_factor("oz"), 28.3495, 0.0001);
    EXPECT_NEAR(get_conversion_factor("lb"), 453.592, 0.001);
}

TEST_F(GetConversionFactorTest, ReturnsZeroForTemperatureUnits) {
    // Temperature units return 0.0 as they require non-linear conversion
    EXPECT_EQ(get_conversion_factor("celsius"), 0.0);
    EXPECT_EQ(get_conversion_factor("fahrenheit"), 0.0);
    EXPECT_EQ(get_conversion_factor("kelvin"), 0.0);
}

TEST_F(GetConversionFactorTest, ReturnsOneForCountUnits) {
    EXPECT_EQ(get_conversion_factor("count"), 1.0);
    EXPECT_EQ(get_conversion_factor("item"), 1.0);
    EXPECT_EQ(get_conversion_factor("piece"), 1.0);
}

TEST_F(GetConversionFactorTest, ThrowsForUnknownUnit) {
    EXPECT_THROW(get_conversion_factor("unknown"), std::invalid_argument);
}

// =============================================================================
// Tests for UNIT_TABLE completeness
// =============================================================================

class UnitTableCompletenessTest : public ::testing::Test {};

TEST_F(UnitTableCompletenessTest, Has24VolumeUnitStrings) {
    std::vector<std::string> volume_units = {
        "tsp", "teaspoon", "teaspoons",
        "tbsp", "tablespoon", "tablespoons",
        "floz", "fl oz", "fluid ounce", "fluid ounces",
        "cup", "cups",
        "pint", "pints",
        "quart", "quarts",
        "gallon", "gallons",
        "ml", "milliliter", "milliliters",
        "l", "liter", "liters"
    };

    for (const auto& unit : volume_units) {
        EXPECT_NO_THROW(get_unit_type(unit)) << "Unit '" << unit << "' should be in UNIT_TABLE";
        EXPECT_EQ(get_unit_type(unit), UnitType::Volume) << "Unit '" << unit << "' should be Volume type";
    }
}

TEST_F(UnitTableCompletenessTest, Has13WeightUnitStrings) {
    std::vector<std::string> weight_units = {
        "oz", "ounce", "ounces",
        "lb", "lbs", "pound", "pounds",
        "g", "gram", "grams",
        "kg", "kilogram", "kilograms"
    };

    for (const auto& unit : weight_units) {
        EXPECT_NO_THROW(get_unit_type(unit)) << "Unit '" << unit << "' should be in UNIT_TABLE";
        EXPECT_EQ(get_unit_type(unit), UnitType::Weight) << "Unit '" << unit << "' should be Weight type";
    }
}

TEST_F(UnitTableCompletenessTest, Has6TemperatureUnitStrings) {
    std::vector<std::string> temp_units = {
        "fahrenheit", "f",
        "celsius", "c",
        "kelvin", "k"
    };

    for (const auto& unit : temp_units) {
        EXPECT_NO_THROW(get_unit_type(unit)) << "Unit '" << unit << "' should be in UNIT_TABLE";
        EXPECT_EQ(get_unit_type(unit), UnitType::Temperature) << "Unit '" << unit << "' should be Temperature type";
    }
}

TEST_F(UnitTableCompletenessTest, Has6CountUnitStrings) {
    std::vector<std::string> count_units = {
        "count", "item", "items", "piece", "pieces", "whole"
    };

    for (const auto& unit : count_units) {
        EXPECT_NO_THROW(get_unit_type(unit)) << "Unit '" << unit << "' should be in UNIT_TABLE";
        EXPECT_EQ(get_unit_type(unit), UnitType::Count) << "Unit '" << unit << "' should be Count type";
    }
}

// =============================================================================
// Tests for volume conversions (mirrors TestVolumeConversions in Python)
// =============================================================================

class TestVolumeConversions : public ::testing::Test {};

TEST_F(TestVolumeConversions, CupsToMl) {
    double result = convert(2, "cups", "ml");
    EXPECT_NEAR(result, 473.176, 0.01);
}

TEST_F(TestVolumeConversions, TspToTbsp) {
    double result = convert(3, "tsp", "tbsp");
    EXPECT_NEAR(result, 1.0, 0.01);
}

TEST_F(TestVolumeConversions, GallonToLiter) {
    double result = convert(1, "gallon", "l");
    EXPECT_NEAR(result, 3.785, 0.01);
}

TEST_F(TestVolumeConversions, FlozToMl) {
    double result = convert(8, "fl oz", "ml");
    EXPECT_NEAR(result, 236.588, 0.01);
}

TEST_F(TestVolumeConversions, SameUnit) {
    double result = convert(5, "cup", "cup");
    EXPECT_EQ(result, 5.0);
}

// =============================================================================
// Tests for weight conversions (mirrors TestWeightConversions in Python)
// =============================================================================

class TestWeightConversions : public ::testing::Test {};

TEST_F(TestWeightConversions, PoundsToGrams) {
    double result = convert(1, "pound", "g");
    EXPECT_NEAR(result, 453.592, 0.01);
}

TEST_F(TestWeightConversions, OzToGrams) {
    double result = convert(16, "oz", "g");
    EXPECT_NEAR(result, 453.592, 0.01);
}

TEST_F(TestWeightConversions, KgToLbs) {
    double result = convert(1, "kg", "lb");
    EXPECT_NEAR(result, 2.205, 0.01);
}

TEST_F(TestWeightConversions, GramsToOunces) {
    double result = convert(100, "g", "oz");
    EXPECT_NEAR(result, 3.527, 0.01);
}

// =============================================================================
// Tests for temperature conversions (mirrors TestTemperatureConversions in Python)
// =============================================================================

class TestTemperatureConversions : public ::testing::Test {};

TEST_F(TestTemperatureConversions, FahrenheitToCelsius) {
    double result = convert(32, "fahrenheit", "celsius");
    EXPECT_NEAR(result, 0.0, 0.01);

    result = convert(212, "f", "c");
    EXPECT_NEAR(result, 100.0, 0.01);

    result = convert(350, "f", "c");
    EXPECT_NEAR(result, 176.67, 0.1);
}

TEST_F(TestTemperatureConversions, CelsiusToFahrenheit) {
    double result = convert(0, "celsius", "fahrenheit");
    EXPECT_NEAR(result, 32.0, 0.01);

    result = convert(100, "c", "f");
    EXPECT_NEAR(result, 212.0, 0.01);
}

TEST_F(TestTemperatureConversions, CelsiusToKelvin) {
    double result = convert(0, "celsius", "kelvin");
    EXPECT_NEAR(result, 273.15, 0.01);
}

TEST_F(TestTemperatureConversions, KelvinToCelsius) {
    double result = convert(273.15, "kelvin", "celsius");
    EXPECT_NEAR(result, 0.0, 0.01);
}

// =============================================================================
// Tests for count conversions (mirrors TestCountConversions in Python)
// =============================================================================

class TestCountConversions : public ::testing::Test {};

TEST_F(TestCountConversions, CountToCount) {
    double result = convert(5, "count", "item");
    EXPECT_EQ(result, 5.0);
}

// =============================================================================
// Tests for error handling (mirrors TestErrorHandling in Python)
// =============================================================================

class TestErrorHandling : public ::testing::Test {};

TEST_F(TestErrorHandling, IncompatibleUnits) {
    try {
        convert(1, "cups", "grams");
        FAIL() << "Expected std::invalid_argument";
    } catch (const std::invalid_argument& e) {
        std::string msg = e.what();
        EXPECT_TRUE(msg.find("Cannot convert between") != std::string::npos)
            << "Error message should contain 'Cannot convert between': " << msg;
    }
}

TEST_F(TestErrorHandling, UnknownUnit) {
    try {
        convert(1, "blorg", "ml");
        FAIL() << "Expected std::invalid_argument";
    } catch (const std::invalid_argument& e) {
        std::string msg = e.what();
        EXPECT_TRUE(msg.find("Unknown unit") != std::string::npos)
            << "Error message should contain 'Unknown unit': " << msg;
    }
}

TEST_F(TestErrorHandling, TemperatureWeightMix) {
    try {
        convert(100, "celsius", "grams");
        FAIL() << "Expected std::invalid_argument";
    } catch (const std::invalid_argument& e) {
        std::string msg = e.what();
        EXPECT_TRUE(msg.find("Cannot convert between") != std::string::npos)
            << "Error message should contain 'Cannot convert between': " << msg;
    }
}

// =============================================================================
// Tests for unit variations (mirrors TestUnitVariations in Python)
// =============================================================================

class TestUnitVariations : public ::testing::Test {};

TEST_F(TestUnitVariations, TeaspoonVariations) {
    double result1 = convert(1, "tsp", "ml");
    double result2 = convert(1, "teaspoon", "ml");
    EXPECT_NEAR(result1, result2, 0.001);
}

TEST_F(TestUnitVariations, PoundVariations) {
    double result1 = convert(1, "lb", "g");
    double result2 = convert(1, "lbs", "g");
    double result3 = convert(1, "pound", "g");
    EXPECT_NEAR(result1, result2, 0.001);
    EXPECT_NEAR(result1, result3, 0.001);
}

TEST_F(TestUnitVariations, CaseInsensitive) {
    double result1 = convert(1, "CUP", "ML");
    double result2 = convert(1, "cup", "ml");
    EXPECT_NEAR(result1, result2, 0.001);
}

} // namespace test
} // namespace lethimcook
