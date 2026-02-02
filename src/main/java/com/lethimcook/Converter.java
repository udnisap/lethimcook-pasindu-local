package com.lethimcook;

/**
 * Core unit conversion functionality.
 * Provides methods to convert values between different units of the same type.
 */
public final class Converter {

    private Converter() {
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
        String normalizedFrom = Units.normalizeUnit(fromUnit);
        String normalizedTo = Units.normalizeUnit(toUnit);

        // Get unit types
        UnitType fromType = Units.getUnitType(normalizedFrom);
        UnitType toType = Units.getUnitType(normalizedTo);

        // Check compatibility
        if (fromType != toType) {
            throw new IllegalArgumentException(
                    "Cannot convert between " + fromType + " and " + toType
            );
        }

        // Handle temperature separately (non-linear conversion)
        if (fromType == UnitType.TEMPERATURE) {
            return convertTemperature(value, normalizedFrom, normalizedTo);
        }

        // Handle count (no conversion needed)
        if (fromType == UnitType.COUNT) {
            return value;
        }

        // Convert: from_unit -> base_unit -> to_unit
        double baseValue = value * Units.CONVERSIONS.get(normalizedFrom);
        return baseValue / Units.CONVERSIONS.get(normalizedTo);
    }

    /**
     * Convert temperature between different scales.
     * Uses Celsius as the intermediate scale for all conversions.
     *
     * @param value    the temperature value to convert
     * @param fromUnit the source temperature unit (normalized)
     * @param toUnit   the target temperature unit (normalized)
     * @return the converted temperature value
     */
    private static double convertTemperature(double value, String fromUnit, String toUnit) {
        // First convert to Celsius
        double celsius = switch (fromUnit) {
            case "celsius", "c" -> value;
            case "fahrenheit", "f" -> (value - 32) * 5 / 9;
            case "kelvin", "k" -> value - 273.15;
            default -> throw new IllegalArgumentException("Unknown temperature unit: " + fromUnit);
        };

        // Then convert from Celsius to target
        return switch (toUnit) {
            case "celsius", "c" -> celsius;
            case "fahrenheit", "f" -> celsius * 9 / 5 + 32;
            case "kelvin", "k" -> celsius + 273.15;
            default -> throw new IllegalArgumentException("Unknown temperature unit: " + toUnit);
        };
    }
}
