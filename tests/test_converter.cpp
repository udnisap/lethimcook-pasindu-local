/**
 * Tests for core conversion functionality.
 *
 * Ported from Python test_converter.py - mirrors all test classes and cases.
 */

#include <gtest/gtest.h>
#include <cmath>
#include <stdexcept>
#include <string>

#include "lethimcook/converter.hpp"
#include "lethimcook/units.hpp"

// ============================================================
// TestVolumeConversions - Test volume unit conversions.
// ============================================================

TEST(VolumeConversions, CupsToMl) {
    double result = lethimcook::convert(2, "cups", "ml");
    EXPECT_NEAR(result, 473.176, 0.01);
}

TEST(VolumeConversions, TspToTbsp) {
    double result = lethimcook::convert(3, "tsp", "tbsp");
    EXPECT_NEAR(result, 1.0, 0.01);
}

TEST(VolumeConversions, GallonToLiter) {
    double result = lethimcook::convert(1, "gallon", "l");
    EXPECT_NEAR(result, 3.785, 0.01);
}

TEST(VolumeConversions, FlOzToMl) {
    double result = lethimcook::convert(8, "fl oz", "ml");
    EXPECT_NEAR(result, 236.588, 0.01);
}

TEST(VolumeConversions, SameUnit) {
    double result = lethimcook::convert(5, "cup", "cup");
    EXPECT_DOUBLE_EQ(result, 5.0);
}

// ============================================================
// TestWeightConversions - Test weight unit conversions.
// ============================================================

TEST(WeightConversions, PoundsToGrams) {
    double result = lethimcook::convert(1, "pound", "g");
    EXPECT_NEAR(result, 453.592, 0.01);
}

TEST(WeightConversions, OzToGrams) {
    double result = lethimcook::convert(16, "oz", "g");
    EXPECT_NEAR(result, 453.592, 0.01);
}

TEST(WeightConversions, KgToLbs) {
    double result = lethimcook::convert(1, "kg", "lb");
    EXPECT_NEAR(result, 2.205, 0.01);
}

TEST(WeightConversions, GramsToOunces) {
    double result = lethimcook::convert(100, "g", "oz");
    EXPECT_NEAR(result, 3.527, 0.01);
}

// ============================================================
// TestTemperatureConversions - Test temperature unit conversions.
// ============================================================

TEST(TemperatureConversions, FahrenheitToCelsius) {
    double result1 = lethimcook::convert(32, "fahrenheit", "celsius");
    EXPECT_NEAR(result1, 0.0, 0.01);

    double result2 = lethimcook::convert(212, "f", "c");
    EXPECT_NEAR(result2, 100.0, 0.01);

    double result3 = lethimcook::convert(350, "f", "c");
    EXPECT_NEAR(result3, 176.67, 0.1);
}

TEST(TemperatureConversions, CelsiusToFahrenheit) {
    double result1 = lethimcook::convert(0, "celsius", "fahrenheit");
    EXPECT_NEAR(result1, 32.0, 0.01);

    double result2 = lethimcook::convert(100, "c", "f");
    EXPECT_NEAR(result2, 212.0, 0.01);
}

TEST(TemperatureConversions, CelsiusToKelvin) {
    double result = lethimcook::convert(0, "celsius", "kelvin");
    EXPECT_NEAR(result, 273.15, 0.01);
}

TEST(TemperatureConversions, KelvinToCelsius) {
    double result = lethimcook::convert(273.15, "kelvin", "celsius");
    EXPECT_NEAR(result, 0.0, 0.01);
}

// ============================================================
// TestCountConversions - Test count/item conversions.
// ============================================================

TEST(CountConversions, CountToCount) {
    double result = lethimcook::convert(5, "count", "item");
    EXPECT_DOUBLE_EQ(result, 5.0);
}

// ============================================================
// TestErrorHandling - Test error handling.
// ============================================================

TEST(ErrorHandling, IncompatibleUnits) {
    try {
        lethimcook::convert(1, "cups", "grams");
        FAIL() << "Expected std::invalid_argument";
    } catch (const std::invalid_argument& e) {
        std::string msg = e.what();
        EXPECT_NE(msg.find("Cannot convert between"), std::string::npos)
            << "Error message was: " << msg;
    }
}

TEST(ErrorHandling, UnknownUnit) {
    try {
        lethimcook::convert(1, "blorg", "ml");
        FAIL() << "Expected std::invalid_argument";
    } catch (const std::invalid_argument& e) {
        std::string msg = e.what();
        EXPECT_NE(msg.find("Unknown unit"), std::string::npos)
            << "Error message was: " << msg;
    }
}

TEST(ErrorHandling, TemperatureWeightMix) {
    try {
        lethimcook::convert(100, "celsius", "grams");
        FAIL() << "Expected std::invalid_argument";
    } catch (const std::invalid_argument& e) {
        std::string msg = e.what();
        EXPECT_NE(msg.find("Cannot convert between"), std::string::npos)
            << "Error message was: " << msg;
    }
}

// ============================================================
// TestUnitVariations - Test different unit name variations.
// ============================================================

TEST(UnitVariations, TeaspoonVariations) {
    double result1 = lethimcook::convert(1, "tsp", "ml");
    double result2 = lethimcook::convert(1, "teaspoon", "ml");
    EXPECT_NEAR(result1, result2, 0.001);
}

TEST(UnitVariations, PoundVariations) {
    double result1 = lethimcook::convert(1, "lb", "g");
    double result2 = lethimcook::convert(1, "lbs", "g");
    double result3 = lethimcook::convert(1, "pound", "g");
    EXPECT_NEAR(result1, result2, 0.001);
    EXPECT_NEAR(result1, result3, 0.001);
}

TEST(UnitVariations, CaseInsensitive) {
    double result1 = lethimcook::convert(1, "CUP", "ML");
    double result2 = lethimcook::convert(1, "cup", "ml");
    EXPECT_NEAR(result1, result2, 0.001);
}
