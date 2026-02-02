package com.lethimcook;

/**
 * Facade class providing a unified API entry point for the lethimcook library.
 * <p>
 * This class provides static convenience methods that delegate to the underlying
 * implementation classes (Converter, NaturalLanguage). It serves as the primary
 * entry point for consumers who want a simple, Python-like API.
 * <p>
 * Example usage:
 * <pre>{@code
 * // Direct unit conversion
 * double ml = Lethimcook.convert(2.0, "cups", "ml");
 *
 * // Natural language conversion
 * String result = Lethimcook.convertNatural("2 cups to ml");
 * }</pre>
 */
public final class Lethimcook {

    private Lethimcook() {
    }

    /**
     * Convert a value from one unit to another.
     *
     * @param value    the numeric value to convert
     * @param fromUnit the source unit
     * @param toUnit   the target unit
     * @return the converted value
     * @throws IllegalArgumentException if units are incompatible or unknown
     */
    public static double convert(double value, String fromUnit, String toUnit) {
        return Converter.convert(value, fromUnit, toUnit);
    }

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
        return NaturalLanguage.convertNatural(text);
    }
}
