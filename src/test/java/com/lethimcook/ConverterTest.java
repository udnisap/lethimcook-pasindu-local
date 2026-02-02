package com.lethimcook;

import org.junit.jupiter.api.Nested;
import org.junit.jupiter.api.Test;

import static org.assertj.core.api.Assertions.assertThat;
import static org.assertj.core.api.Assertions.assertThatThrownBy;
import static org.assertj.core.api.Assertions.within;

/**
 * Tests for core conversion functionality.
 * Migrated from test_converter.py.
 */
class ConverterTest {

    /**
     * Standard epsilon for most conversion tests (matching Python tolerance of 0.01).
     */
    private static final double EPSILON = 0.01;

    /**
     * Smaller epsilon for unit variation tests.
     */
    private static final double EPSILON_SMALL = 0.001;

    /**
     * Larger epsilon for temperature tests that use 0.1 in Python.
     */
    private static final double EPSILON_TEMP_LARGE = 0.1;

    @Nested
    class TestVolumeConversions {

        @Test
        void testCupsToMl() {
            double result = Converter.convert(2, "cups", "ml");
            assertThat(result).isCloseTo(473.176, within(EPSILON));
        }

        @Test
        void testTspToTbsp() {
            double result = Converter.convert(3, "tsp", "tbsp");
            assertThat(result).isCloseTo(1, within(EPSILON));
        }

        @Test
        void testGallonToLiter() {
            double result = Converter.convert(1, "gallon", "l");
            assertThat(result).isCloseTo(3.785, within(EPSILON));
        }

        @Test
        void testFlozToMl() {
            double result = Converter.convert(8, "fl oz", "ml");
            assertThat(result).isCloseTo(236.588, within(EPSILON));
        }

        @Test
        void testSameUnit() {
            double result = Converter.convert(5, "cup", "cup");
            assertThat(result).isEqualTo(5);
        }
    }

    @Nested
    class TestWeightConversions {

        @Test
        void testPoundsToGrams() {
            double result = Converter.convert(1, "pound", "g");
            assertThat(result).isCloseTo(453.592, within(EPSILON));
        }

        @Test
        void testOzToGrams() {
            double result = Converter.convert(16, "oz", "g");
            assertThat(result).isCloseTo(453.592, within(EPSILON));
        }

        @Test
        void testKgToLbs() {
            double result = Converter.convert(1, "kg", "lb");
            assertThat(result).isCloseTo(2.205, within(EPSILON));
        }

        @Test
        void testGramsToOunces() {
            double result = Converter.convert(100, "g", "oz");
            assertThat(result).isCloseTo(3.527, within(EPSILON));
        }
    }

    @Nested
    class TestTemperatureConversions {

        @Test
        void testFahrenheitToCelsius() {
            // 32 F = 0 C
            double result1 = Converter.convert(32, "fahrenheit", "celsius");
            assertThat(result1).isCloseTo(0, within(EPSILON));

            // 212 F = 100 C
            double result2 = Converter.convert(212, "f", "c");
            assertThat(result2).isCloseTo(100, within(EPSILON));

            // 350 F = ~176.67 C
            double result3 = Converter.convert(350, "f", "c");
            assertThat(result3).isCloseTo(176.67, within(EPSILON_TEMP_LARGE));
        }

        @Test
        void testCelsiusToFahrenheit() {
            // 0 C = 32 F
            double result1 = Converter.convert(0, "celsius", "fahrenheit");
            assertThat(result1).isCloseTo(32, within(EPSILON));

            // 100 C = 212 F
            double result2 = Converter.convert(100, "c", "f");
            assertThat(result2).isCloseTo(212, within(EPSILON));
        }

        @Test
        void testCelsiusToKelvin() {
            // 0 C = 273.15 K
            double result = Converter.convert(0, "celsius", "kelvin");
            assertThat(result).isCloseTo(273.15, within(EPSILON));
        }

        @Test
        void testKelvinToCelsius() {
            // 273.15 K = 0 C
            double result = Converter.convert(273.15, "kelvin", "celsius");
            assertThat(result).isCloseTo(0, within(EPSILON));
        }
    }

    @Nested
    class TestCountConversions {

        @Test
        void testCountToCount() {
            double result = Converter.convert(5, "count", "item");
            assertThat(result).isEqualTo(5);
        }
    }

    @Nested
    class TestErrorHandling {

        @Test
        void testIncompatibleUnits() {
            assertThatThrownBy(() -> Converter.convert(1, "cups", "grams"))
                    .isInstanceOf(IllegalArgumentException.class)
                    .hasMessageContaining("Cannot convert between");
        }

        @Test
        void testUnknownUnit() {
            assertThatThrownBy(() -> Converter.convert(1, "blorg", "ml"))
                    .isInstanceOf(IllegalArgumentException.class)
                    .hasMessageContaining("Unknown unit");
        }

        @Test
        void testTemperatureWeightMix() {
            assertThatThrownBy(() -> Converter.convert(100, "celsius", "grams"))
                    .isInstanceOf(IllegalArgumentException.class)
                    .hasMessageContaining("Cannot convert between");
        }
    }

    @Nested
    class TestUnitVariations {

        @Test
        void testTeaspoonVariations() {
            double result1 = Converter.convert(1, "tsp", "ml");
            double result2 = Converter.convert(1, "teaspoon", "ml");
            assertThat(result1).isCloseTo(result2, within(EPSILON_SMALL));
        }

        @Test
        void testPoundVariations() {
            double result1 = Converter.convert(1, "lb", "g");
            double result2 = Converter.convert(1, "lbs", "g");
            double result3 = Converter.convert(1, "pound", "g");
            assertThat(result1).isCloseTo(result2, within(EPSILON_SMALL));
            assertThat(result1).isCloseTo(result3, within(EPSILON_SMALL));
        }

        @Test
        void testCaseInsensitive() {
            double result1 = Converter.convert(1, "CUP", "ML");
            double result2 = Converter.convert(1, "cup", "ml");
            assertThat(result1).isCloseTo(result2, within(EPSILON_SMALL));
        }
    }
}
