#include "lethimcook/converter.hpp"

#include <gtest/gtest.h>
#include <stdexcept>
#include <cmath>

using lethimcook::convert;

// ===========================================================================
// Volume Conversions
// ===========================================================================
class VolumeConversions : public ::testing::Test {};

TEST_F(VolumeConversions, CupsToMl) {
    double result = convert(2, "cups", "ml");
    EXPECT_NEAR(result, 473.176, 0.01);
}

TEST_F(VolumeConversions, TspToTbsp) {
    double result = convert(3, "tsp", "tbsp");
    EXPECT_NEAR(result, 1.0, 0.01);
}

TEST_F(VolumeConversions, GallonToLiter) {
    double result = convert(1, "gallon", "l");
    EXPECT_NEAR(result, 3.785, 0.01);
}

TEST_F(VolumeConversions, FlozToMl) {
    double result = convert(8, "fl oz", "ml");
    EXPECT_NEAR(result, 236.588, 0.01);
}

TEST_F(VolumeConversions, SameUnit) {
    double result = convert(5, "cup", "cup");
    EXPECT_DOUBLE_EQ(result, 5.0);
}

// ===========================================================================
// Weight Conversions
// ===========================================================================
class WeightConversions : public ::testing::Test {};

TEST_F(WeightConversions, PoundsToGrams) {
    double result = convert(1, "pound", "g");
    EXPECT_NEAR(result, 453.592, 0.01);
}

TEST_F(WeightConversions, OzToGrams) {
    double result = convert(16, "oz", "g");
    EXPECT_NEAR(result, 453.592, 0.01);
}

TEST_F(WeightConversions, KgToLbs) {
    double result = convert(1, "kg", "lb");
    EXPECT_NEAR(result, 2.205, 0.01);
}

TEST_F(WeightConversions, GramsToOunces) {
    double result = convert(100, "g", "oz");
    EXPECT_NEAR(result, 3.527, 0.01);
}

// ===========================================================================
// Temperature Conversions
// ===========================================================================
class TemperatureConversions : public ::testing::Test {};

TEST_F(TemperatureConversions, FahrenheitToCelsius) {
    double result1 = convert(32, "fahrenheit", "celsius");
    EXPECT_NEAR(result1, 0.0, 0.01);

    double result2 = convert(212, "f", "c");
    EXPECT_NEAR(result2, 100.0, 0.01);

    double result3 = convert(350, "f", "c");
    EXPECT_NEAR(result3, 176.67, 0.1);
}

TEST_F(TemperatureConversions, CelsiusToFahrenheit) {
    double result1 = convert(0, "celsius", "fahrenheit");
    EXPECT_NEAR(result1, 32.0, 0.01);

    double result2 = convert(100, "c", "f");
    EXPECT_NEAR(result2, 212.0, 0.01);
}

TEST_F(TemperatureConversions, CelsiusToKelvin) {
    double result = convert(0, "celsius", "kelvin");
    EXPECT_NEAR(result, 273.15, 0.01);
}

TEST_F(TemperatureConversions, KelvinToCelsius) {
    double result = convert(273.15, "kelvin", "celsius");
    EXPECT_NEAR(result, 0.0, 0.01);
}

// ===========================================================================
// Count Conversions
// ===========================================================================
class CountConversions : public ::testing::Test {};

TEST_F(CountConversions, CountToCount) {
    double result = convert(5, "count", "item");
    EXPECT_DOUBLE_EQ(result, 5.0);
}

// ===========================================================================
// Error Handling
// ===========================================================================
class ErrorHandling : public ::testing::Test {};

TEST_F(ErrorHandling, IncompatibleUnits) {
    EXPECT_THROW({
        try {
            convert(1, "cups", "grams");
        } catch (const std::invalid_argument& e) {
            std::string msg = e.what();
            EXPECT_NE(msg.find("Cannot convert between"), std::string::npos);
            throw;
        }
    }, std::invalid_argument);
}

TEST_F(ErrorHandling, UnknownUnit) {
    EXPECT_THROW({
        try {
            convert(1, "blorg", "ml");
        } catch (const std::invalid_argument& e) {
            std::string msg = e.what();
            EXPECT_NE(msg.find("Unknown unit"), std::string::npos);
            throw;
        }
    }, std::invalid_argument);
}

TEST_F(ErrorHandling, TemperatureWeightMix) {
    EXPECT_THROW({
        try {
            convert(100, "celsius", "grams");
        } catch (const std::invalid_argument& e) {
            std::string msg = e.what();
            EXPECT_NE(msg.find("Cannot convert between"), std::string::npos);
            throw;
        }
    }, std::invalid_argument);
}

// ===========================================================================
// Unit Variations
// ===========================================================================
class UnitVariations : public ::testing::Test {};

TEST_F(UnitVariations, TeaspoonVariations) {
    double result1 = convert(1, "tsp", "ml");
    double result2 = convert(1, "teaspoon", "ml");
    EXPECT_NEAR(result1, result2, 0.001);
}

TEST_F(UnitVariations, PoundVariations) {
    double result1 = convert(1, "lb", "g");
    double result2 = convert(1, "lbs", "g");
    double result3 = convert(1, "pound", "g");
    EXPECT_NEAR(result1, result2, 0.001);
    EXPECT_NEAR(result1, result3, 0.001);
}

TEST_F(UnitVariations, CaseInsensitive) {
    double result1 = convert(1, "CUP", "ML");
    double result2 = convert(1, "cup", "ml");
    EXPECT_NEAR(result1, result2, 0.001);
}
