package com.lethimcook;

import org.junit.jupiter.api.DisplayName;
import org.junit.jupiter.api.Nested;
import org.junit.jupiter.api.Test;

import java.io.ByteArrayOutputStream;
import java.io.PrintStream;

import static org.assertj.core.api.Assertions.assertThat;

/**
 * Integration tests for the CLI entry point.
 * Tests use the Cli.run() method directly to avoid System.exit() issues.
 */
@DisplayName("CLI Integration Tests")
class CliTest {

    private ByteArrayOutputStream outContent;
    private ByteArrayOutputStream errContent;
    private PrintStream out;
    private PrintStream err;

    private void setUpStreams() {
        outContent = new ByteArrayOutputStream();
        errContent = new ByteArrayOutputStream();
        out = new PrintStream(outContent);
        err = new PrintStream(errContent);
    }

    private int runCli(String... args) {
        setUpStreams();
        return Cli.run(args, out, err);
    }

    @Nested
    @DisplayName("Help Output Tests")
    class HelpOutputTests {

        @Test
        @DisplayName("Prints help when no arguments provided and returns exit code 1")
        void printsHelpWhenNoArgs() {
            int exitCode = runCli();

            String output = outContent.toString();
            assertThat(output).contains("LetHimCook");
            assertThat(output).contains("Unit Conversion Library");
            assertThat(output).contains("Usage:");
            assertThat(exitCode).isEqualTo(1);
        }

        @Test
        @DisplayName("Help contains title")
        void helpContainsTitle() {
            runCli();

            String output = outContent.toString();
            assertThat(output).contains("LetHimCook - Unit Conversion Library");
        }

        @Test
        @DisplayName("Help contains usage examples")
        void helpContainsUsageExamples() {
            runCli();

            String output = outContent.toString();
            assertThat(output).contains("2 cups to ml");
            assertThat(output).contains("convert 1 pound to grams");
            assertThat(output).contains("how many ml in 3 teaspoons");
        }

        @Test
        @DisplayName("Help lists volume units")
        void helpListsVolumeUnits() {
            runCli();

            String output = outContent.toString();
            assertThat(output).contains("Volume:");
            assertThat(output).contains("tsp");
            assertThat(output).contains("tbsp");
            assertThat(output).contains("cup");
            assertThat(output).contains("ml");
            assertThat(output).contains("liter");
        }

        @Test
        @DisplayName("Help lists weight units")
        void helpListsWeightUnits() {
            runCli();

            String output = outContent.toString();
            assertThat(output).contains("Weight:");
            assertThat(output).contains("oz");
            assertThat(output).contains("pound");
            assertThat(output).contains("gram");
            assertThat(output).contains("kilogram");
        }

        @Test
        @DisplayName("Help lists temperature units")
        void helpListsTemperatureUnits() {
            runCli();

            String output = outContent.toString();
            assertThat(output).contains("Temperature:");
            assertThat(output).contains("fahrenheit");
            assertThat(output).contains("celsius");
            assertThat(output).contains("kelvin");
        }
    }

    @Nested
    @DisplayName("Successful Conversion Tests")
    class SuccessfulConversionTests {

        @Test
        @DisplayName("Converts cups to ml with exit code 0")
        void convertsCupsToMl() {
            int exitCode = runCli("2 cups to ml");

            String output = outContent.toString();
            assertThat(output).contains("2");
            assertThat(output).contains("cups");
            assertThat(output).contains("=");
            assertThat(output).contains("473");
            assertThat(output).contains("ml");
            assertThat(exitCode).isEqualTo(0);
        }

        @Test
        @DisplayName("Converts with convert prefix")
        void convertsWithConvertPrefix() {
            int exitCode = runCli("convert 1 pound to grams");

            String output = outContent.toString();
            assertThat(output).contains("1");
            assertThat(output).contains("pound");
            assertThat(output).contains("=");
            assertThat(output).contains("453");
            assertThat(output).contains("gram");
            assertThat(exitCode).isEqualTo(0);
        }

        @Test
        @DisplayName("Converts with how many pattern")
        void convertsWithHowManyPattern() {
            int exitCode = runCli("how many ml in 3 teaspoons");

            String output = outContent.toString();
            assertThat(output).contains("3");
            assertThat(output).contains("teaspoon");
            assertThat(output).contains("=");
            assertThat(output).contains("ml");
            assertThat(exitCode).isEqualTo(0);
        }

        @Test
        @DisplayName("Handles multiple arguments as single query")
        void handlesMultipleArgumentsAsSingleQuery() {
            int exitCode = runCli("2", "cups", "to", "ml");

            String output = outContent.toString();
            assertThat(output).contains("473");
            assertThat(exitCode).isEqualTo(0);
        }

        @Test
        @DisplayName("Converts temperature fahrenheit to celsius")
        void convertsTemperature() {
            int exitCode = runCli("32 fahrenheit to celsius");

            String output = outContent.toString();
            assertThat(output).contains("32");
            assertThat(output).contains("fahrenheit");
            assertThat(output).contains("=");
            assertThat(output).contains("0");
            assertThat(output).contains("celsius");
            assertThat(exitCode).isEqualTo(0);
        }
    }

    @Nested
    @DisplayName("Error Handling Tests")
    class ErrorHandlingTests {

        @Test
        @DisplayName("Prints error for invalid input with exit code 1")
        void printsErrorForInvalidInput() {
            int exitCode = runCli("invalid input that cannot be parsed");

            String errorOutput = errContent.toString();
            assertThat(errorOutput).contains("Error:");
            assertThat(exitCode).isEqualTo(1);
        }

        @Test
        @DisplayName("Error for incompatible units with exit code 1")
        void errorForIncompatibleUnits() {
            int exitCode = runCli("2 cups to grams");

            String errorOutput = errContent.toString();
            assertThat(errorOutput).contains("Error:");
            assertThat(exitCode).isEqualTo(1);
        }
    }

    @Nested
    @DisplayName("Lethimcook Facade Tests")
    class LethimcookFacadeTests {

        @Test
        @DisplayName("Facade convert delegates to Converter")
        void facadeConvertDelegatesToConverter() {
            double result = Lethimcook.convert(2.0, "cups", "ml");
            assertThat(result).isCloseTo(473.18, org.assertj.core.data.Offset.offset(0.01));
        }

        @Test
        @DisplayName("Facade convertNatural delegates to NaturalLanguage")
        void facadeConvertNaturalDelegatesToNaturalLanguage() {
            String result = Lethimcook.convertNatural("2 cups to ml");
            assertThat(result).contains("473");
            assertThat(result).contains("ml");
        }
    }
}
