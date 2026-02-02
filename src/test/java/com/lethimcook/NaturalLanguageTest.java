package com.lethimcook;

import org.junit.jupiter.api.Nested;
import org.junit.jupiter.api.Test;

import static org.assertj.core.api.Assertions.assertThat;
import static org.assertj.core.api.Assertions.assertThatThrownBy;

/**
 * Tests for natural language conversion.
 */
class NaturalLanguageTest {

    @Nested
    class NaturalLanguagePatterns {

        @Test
        void testBasicToPattern() {
            String result = NaturalLanguage.convertNatural("2 cups to ml");
            assertThat(result.toLowerCase()).contains("2 cups");
            assertThat(result.toLowerCase()).contains("ml");
            assertThat(result).contains("473");
        }

        @Test
        void testConvertPattern() {
            String result = NaturalLanguage.convertNatural("convert 1 pound to grams");
            assertThat(result.toLowerCase()).contains("1 pound");
            assertThat(result.toLowerCase()).contains("gram");
            assertThat(result).contains("453");
        }

        @Test
        void testHowManyPattern() {
            String result = NaturalLanguage.convertNatural("how many ml in 3 teaspoons");
            assertThat(result.toLowerCase()).contains("3 teaspoon");
            assertThat(result.toLowerCase()).contains("ml");
        }

        @Test
        void testDecimalValues() {
            String result = NaturalLanguage.convertNatural("1.5 cups to ml");
            assertThat(result).contains("1.5");
        }

        @Test
        void testTemperatureConversion() {
            String result = NaturalLanguage.convertNatural("350 fahrenheit to celsius");
            assertThat(result).contains("350");
            assertThat(result.toLowerCase()).contains("fahrenheit");
            assertThat(result.toLowerCase()).contains("celsius");
        }

        @Test
        void testCaseInsensitive() {
            String result1 = NaturalLanguage.convertNatural("2 CUPS to ML");
            String result2 = NaturalLanguage.convertNatural("2 cups to ml");
            // Both should contain the same numeric result
            assertThat(result1).contains("473");
            assertThat(result2).contains("473");
        }

        @Test
        void testMultiWordUnits() {
            String result = NaturalLanguage.convertNatural("5 fluid ounce to ml");
            assertThat(result.toLowerCase()).contains("fluid ounce");
            assertThat(result.toLowerCase()).contains("ml");
        }
    }

    @Nested
    class NaturalLanguageErrors {

        @Test
        void testUnparseableInput() {
            assertThatThrownBy(() -> NaturalLanguage.convertNatural("this is gibberish"))
                    .isInstanceOf(IllegalArgumentException.class)
                    .hasMessageContaining("Could not parse");
        }

        @Test
        void testMissingValue() {
            assertThatThrownBy(() -> NaturalLanguage.convertNatural("cups to ml"))
                    .isInstanceOf(IllegalArgumentException.class);
        }

        @Test
        void testInvalidUnit() {
            assertThatThrownBy(() -> NaturalLanguage.convertNatural("2 blorg to ml"))
                    .isInstanceOf(IllegalArgumentException.class);
        }
    }
}
