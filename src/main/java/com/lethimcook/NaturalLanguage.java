package com.lethimcook;

import java.util.regex.Matcher;
import java.util.regex.Pattern;

/**
 * Natural language conversion utility using regex and string matching.
 * Parses natural language input and converts between units.
 */
public final class NaturalLanguage {

    private NaturalLanguage() {
    }

    // Pre-compiled patterns for performance
    // Pattern 1: "X unit to/in unit" - e.g., "2 cups to ml"
    private static final Pattern PATTERN_BASIC = Pattern.compile(
            "(\\d+\\.?\\d*)\\s+([a-z\\s]+?)\\s+(?:to|in)\\s+([a-z\\s]+)",
            Pattern.CASE_INSENSITIVE
    );

    // Pattern 2: "convert X unit to unit" - e.g., "convert 1.5 pounds to grams"
    private static final Pattern PATTERN_CONVERT = Pattern.compile(
            "convert\\s+(\\d+\\.?\\d*)\\s+([a-z\\s]+?)\\s+to\\s+([a-z\\s]+)",
            Pattern.CASE_INSENSITIVE
    );

    // Pattern 3: "how many unit in X unit" - e.g., "how many ml in 3 teaspoons"
    private static final Pattern PATTERN_HOW_MANY = Pattern.compile(
            "how\\s+many\\s+([a-z\\s]+?)\\s+in\\s+(\\d+\\.?\\d*)\\s+([a-z\\s]+)",
            Pattern.CASE_INSENSITIVE
    );

    /**
     * Convert using natural language input.
     * <p>
     * Supports patterns like:
     * <ul>
     *   <li>"2 cups to ml"</li>
     *   <li>"convert 1.5 pounds to grams"</li>
     *   <li>"how many ml in 3 teaspoons"</li>
     *   <li>"5 fahrenheit to celsius"</li>
     * </ul>
     *
     * @param text Natural language conversion request
     * @return Formatted string with conversion result
     * @throws IllegalArgumentException if the input cannot be parsed
     */
    public static String convertNatural(String text) {
        if (text == null) {
            throw new IllegalArgumentException(
                    "Could not parse conversion request: null\n"
                            + "Try formats like: '2 cups to ml' or 'convert 1 pound to grams'"
            );
        }

        String normalizedText = text.toLowerCase().trim();

        // Pattern 1: "X unit to unit" or "X unit in unit"
        Matcher matcher = PATTERN_BASIC.matcher(normalizedText);
        if (matcher.matches()) {
            double value = Double.parseDouble(matcher.group(1));
            String fromUnit = matcher.group(2).trim();
            String toUnit = matcher.group(3).trim();
            double result = Converter.convert(value, fromUnit, toUnit);
            return formatNumber(value) + " " + fromUnit + " = " + String.format("%.2f", result) + " " + toUnit;
        }

        // Pattern 2: "convert X unit to unit"
        matcher = PATTERN_CONVERT.matcher(normalizedText);
        if (matcher.matches()) {
            double value = Double.parseDouble(matcher.group(1));
            String fromUnit = matcher.group(2).trim();
            String toUnit = matcher.group(3).trim();
            double result = Converter.convert(value, fromUnit, toUnit);
            return formatNumber(value) + " " + fromUnit + " = " + String.format("%.2f", result) + " " + toUnit;
        }

        // Pattern 3: "how many unit in X unit"
        matcher = PATTERN_HOW_MANY.matcher(normalizedText);
        if (matcher.matches()) {
            String toUnit = matcher.group(1).trim();
            double value = Double.parseDouble(matcher.group(2));
            String fromUnit = matcher.group(3).trim();
            double result = Converter.convert(value, fromUnit, toUnit);
            return formatNumber(value) + " " + fromUnit + " = " + String.format("%.2f", result) + " " + toUnit;
        }

        throw new IllegalArgumentException(
                "Could not parse conversion request: " + text + "\n"
                        + "Try formats like: '2 cups to ml' or 'convert 1 pound to grams'"
        );
    }

    /**
     * Format a number, removing .0 for integers.
     *
     * @param value the value to format
     * @return the formatted string representation
     */
    private static String formatNumber(double value) {
        if (value == (int) value) {
            return String.valueOf((int) value);
        }
        return String.valueOf(value);
    }
}
