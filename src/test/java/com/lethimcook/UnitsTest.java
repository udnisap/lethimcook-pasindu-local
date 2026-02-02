package com.lethimcook;

import org.junit.jupiter.api.Nested;
import org.junit.jupiter.api.Test;

import static org.assertj.core.api.Assertions.assertThat;
import static org.assertj.core.api.Assertions.assertThatThrownBy;

/**
 * Tests for the Units utility class and UnitType enum.
 */
class UnitsTest {

    @Nested
    class UnitTypeEnumTest {

        @Test
        void containsAllExpectedValues() {
            assertThat(UnitType.values()).containsExactlyInAnyOrder(
                    UnitType.VOLUME,
                    UnitType.WEIGHT,
                    UnitType.TEMPERATURE,
                    UnitType.COUNT
            );
        }
    }

    @Nested
    class NormalizeUnitTest {

        @Test
        void returnsNullForNullInput() {
            assertThat(Units.normalizeUnit(null)).isNull();
        }

        @Test
        void lowercasesUppercaseInput() {
            assertThat(Units.normalizeUnit("CUP")).isEqualTo("cup");
            assertThat(Units.normalizeUnit("TEASPOON")).isEqualTo("teaspoon");
        }

        @Test
        void trimWhitespace() {
            assertThat(Units.normalizeUnit("  cup  ")).isEqualTo("cup");
            assertThat(Units.normalizeUnit("\ttsp\n")).isEqualTo("tsp");
        }

        @Test
        void handlesLowercaseInput() {
            assertThat(Units.normalizeUnit("gram")).isEqualTo("gram");
        }

        @Test
        void handlesMixedCaseInput() {
            assertThat(Units.normalizeUnit("TableSpoon")).isEqualTo("tablespoon");
        }
    }

    @Nested
    class GetUnitTypeTest {

        @Test
        void returnsVolumeForVolumeUnits() {
            assertThat(Units.getUnitType("cup")).isEqualTo(UnitType.VOLUME);
            assertThat(Units.getUnitType("cups")).isEqualTo(UnitType.VOLUME);
            assertThat(Units.getUnitType("ml")).isEqualTo(UnitType.VOLUME);
            assertThat(Units.getUnitType("milliliter")).isEqualTo(UnitType.VOLUME);
            assertThat(Units.getUnitType("l")).isEqualTo(UnitType.VOLUME);
            assertThat(Units.getUnitType("liter")).isEqualTo(UnitType.VOLUME);
            assertThat(Units.getUnitType("tsp")).isEqualTo(UnitType.VOLUME);
            assertThat(Units.getUnitType("tbsp")).isEqualTo(UnitType.VOLUME);
            assertThat(Units.getUnitType("pint")).isEqualTo(UnitType.VOLUME);
            assertThat(Units.getUnitType("quart")).isEqualTo(UnitType.VOLUME);
            assertThat(Units.getUnitType("gallon")).isEqualTo(UnitType.VOLUME);
            assertThat(Units.getUnitType("floz")).isEqualTo(UnitType.VOLUME);
            assertThat(Units.getUnitType("fl oz")).isEqualTo(UnitType.VOLUME);
        }

        @Test
        void returnsWeightForWeightUnits() {
            assertThat(Units.getUnitType("g")).isEqualTo(UnitType.WEIGHT);
            assertThat(Units.getUnitType("gram")).isEqualTo(UnitType.WEIGHT);
            assertThat(Units.getUnitType("grams")).isEqualTo(UnitType.WEIGHT);
            assertThat(Units.getUnitType("kg")).isEqualTo(UnitType.WEIGHT);
            assertThat(Units.getUnitType("kilogram")).isEqualTo(UnitType.WEIGHT);
            assertThat(Units.getUnitType("oz")).isEqualTo(UnitType.WEIGHT);
            assertThat(Units.getUnitType("ounce")).isEqualTo(UnitType.WEIGHT);
            assertThat(Units.getUnitType("lb")).isEqualTo(UnitType.WEIGHT);
            assertThat(Units.getUnitType("lbs")).isEqualTo(UnitType.WEIGHT);
            assertThat(Units.getUnitType("pound")).isEqualTo(UnitType.WEIGHT);
        }

        @Test
        void returnsTemperatureForTemperatureUnits() {
            assertThat(Units.getUnitType("celsius")).isEqualTo(UnitType.TEMPERATURE);
            assertThat(Units.getUnitType("c")).isEqualTo(UnitType.TEMPERATURE);
            assertThat(Units.getUnitType("fahrenheit")).isEqualTo(UnitType.TEMPERATURE);
            assertThat(Units.getUnitType("f")).isEqualTo(UnitType.TEMPERATURE);
            assertThat(Units.getUnitType("kelvin")).isEqualTo(UnitType.TEMPERATURE);
            assertThat(Units.getUnitType("k")).isEqualTo(UnitType.TEMPERATURE);
        }

        @Test
        void returnsCountForCountUnits() {
            assertThat(Units.getUnitType("count")).isEqualTo(UnitType.COUNT);
            assertThat(Units.getUnitType("item")).isEqualTo(UnitType.COUNT);
            assertThat(Units.getUnitType("items")).isEqualTo(UnitType.COUNT);
            assertThat(Units.getUnitType("piece")).isEqualTo(UnitType.COUNT);
            assertThat(Units.getUnitType("pieces")).isEqualTo(UnitType.COUNT);
            assertThat(Units.getUnitType("whole")).isEqualTo(UnitType.COUNT);
        }

        @Test
        void handlesUppercaseInput() {
            assertThat(Units.getUnitType("CUP")).isEqualTo(UnitType.VOLUME);
            assertThat(Units.getUnitType("GRAM")).isEqualTo(UnitType.WEIGHT);
        }

        @Test
        void handlesInputWithWhitespace() {
            assertThat(Units.getUnitType("  cup  ")).isEqualTo(UnitType.VOLUME);
            assertThat(Units.getUnitType("\tgram\n")).isEqualTo(UnitType.WEIGHT);
        }

        @Test
        void throwsIllegalArgumentExceptionForUnknownUnit() {
            assertThatThrownBy(() -> Units.getUnitType("unknown"))
                    .isInstanceOf(IllegalArgumentException.class)
                    .hasMessageContaining("Unknown unit: unknown");
        }

        @Test
        void throwsIllegalArgumentExceptionWithOriginalUnit() {
            // Verify that the error message contains the original input, not normalized
            assertThatThrownBy(() -> Units.getUnitType("INVALID"))
                    .isInstanceOf(IllegalArgumentException.class)
                    .hasMessageContaining("Unknown unit: INVALID");
        }
    }

    @Nested
    class ConversionsMapTest {

        @Test
        void containsVolumeConversions() {
            assertThat(Units.CONVERSIONS.get("tsp")).isEqualTo(4.92892);
            assertThat(Units.CONVERSIONS.get("tbsp")).isEqualTo(14.7868);
            assertThat(Units.CONVERSIONS.get("cup")).isEqualTo(236.588);
            assertThat(Units.CONVERSIONS.get("ml")).isEqualTo(1.0);
            assertThat(Units.CONVERSIONS.get("l")).isEqualTo(1000.0);
            assertThat(Units.CONVERSIONS.get("floz")).isEqualTo(29.5735);
            assertThat(Units.CONVERSIONS.get("pint")).isEqualTo(473.176);
            assertThat(Units.CONVERSIONS.get("quart")).isEqualTo(946.353);
            assertThat(Units.CONVERSIONS.get("gallon")).isEqualTo(3785.41);
        }

        @Test
        void containsWeightConversions() {
            assertThat(Units.CONVERSIONS.get("g")).isEqualTo(1.0);
            assertThat(Units.CONVERSIONS.get("kg")).isEqualTo(1000.0);
            assertThat(Units.CONVERSIONS.get("oz")).isEqualTo(28.3495);
            assertThat(Units.CONVERSIONS.get("lb")).isEqualTo(453.592);
            assertThat(Units.CONVERSIONS.get("lbs")).isEqualTo(453.592);
        }

        @Test
        void containsCountConversions() {
            assertThat(Units.CONVERSIONS.get("count")).isEqualTo(1.0);
            assertThat(Units.CONVERSIONS.get("item")).isEqualTo(1.0);
            assertThat(Units.CONVERSIONS.get("piece")).isEqualTo(1.0);
            assertThat(Units.CONVERSIONS.get("whole")).isEqualTo(1.0);
        }

        @Test
        void containsUnitAliases() {
            // Singular and plural forms should have same conversion factor
            assertThat(Units.CONVERSIONS.get("cup")).isEqualTo(Units.CONVERSIONS.get("cups"));
            assertThat(Units.CONVERSIONS.get("gram")).isEqualTo(Units.CONVERSIONS.get("grams"));
            assertThat(Units.CONVERSIONS.get("teaspoon")).isEqualTo(Units.CONVERSIONS.get("teaspoons"));
            assertThat(Units.CONVERSIONS.get("tablespoon")).isEqualTo(Units.CONVERSIONS.get("tablespoons"));
            assertThat(Units.CONVERSIONS.get("pound")).isEqualTo(Units.CONVERSIONS.get("pounds"));
            assertThat(Units.CONVERSIONS.get("ounce")).isEqualTo(Units.CONVERSIONS.get("ounces"));
        }
    }

    @Nested
    class UnitTypesMapTest {

        @Test
        void allConversionUnitsHaveTypes() {
            // All units in CONVERSIONS should have a corresponding entry in UNIT_TYPES
            for (String unit : Units.CONVERSIONS.keySet()) {
                assertThat(Units.UNIT_TYPES)
                        .as("Unit '%s' should have a type mapping", unit)
                        .containsKey(unit);
            }
        }

        @Test
        void temperatureUnitsExistInUnitTypes() {
            // Temperature units are in UNIT_TYPES but not in CONVERSIONS
            assertThat(Units.UNIT_TYPES.get("celsius")).isEqualTo(UnitType.TEMPERATURE);
            assertThat(Units.UNIT_TYPES.get("fahrenheit")).isEqualTo(UnitType.TEMPERATURE);
            assertThat(Units.UNIT_TYPES.get("kelvin")).isEqualTo(UnitType.TEMPERATURE);
            assertThat(Units.UNIT_TYPES.get("c")).isEqualTo(UnitType.TEMPERATURE);
            assertThat(Units.UNIT_TYPES.get("f")).isEqualTo(UnitType.TEMPERATURE);
            assertThat(Units.UNIT_TYPES.get("k")).isEqualTo(UnitType.TEMPERATURE);
        }
    }

    @Nested
    class BaseUnitsMapTest {

        @Test
        void containsBaseUnitForVolume() {
            assertThat(Units.BASE_UNITS.get(UnitType.VOLUME)).isEqualTo("ml");
        }

        @Test
        void containsBaseUnitForWeight() {
            assertThat(Units.BASE_UNITS.get(UnitType.WEIGHT)).isEqualTo("g");
        }

        @Test
        void containsBaseUnitForTemperature() {
            assertThat(Units.BASE_UNITS.get(UnitType.TEMPERATURE)).isEqualTo("celsius");
        }

        @Test
        void containsBaseUnitForCount() {
            assertThat(Units.BASE_UNITS.get(UnitType.COUNT)).isEqualTo("count");
        }
    }
}
