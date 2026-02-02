package com.lethimcook;

import java.io.PrintStream;

/**
 * CLI entry point for the lethimcook library.
 * Provides command-line unit conversion using natural language input.
 */
public final class Cli {

    private Cli() {
    }

    /**
     * Main entry point for the CLI.
     * <p>
     * Usage:
     * <ul>
     *   <li>java -jar lethimcook-all.jar "2 cups to ml"</li>
     *   <li>java -jar lethimcook-all.jar "convert 1 pound to grams"</li>
     *   <li>java -jar lethimcook-all.jar "how many ml in 3 teaspoons"</li>
     * </ul>
     *
     * @param args command line arguments - should be a natural language query
     */
    public static void main(String[] args) {
        int exitCode = run(args, System.out, System.err);
        if (exitCode != 0) {
            System.exit(exitCode);
        }
    }

    /**
     * Run the CLI with the given arguments.
     * This method is separated from main() to make testing easier.
     *
     * @param args command line arguments
     * @param out  standard output stream
     * @param err  standard error stream
     * @return exit code (0 for success, 1 for error)
     */
    static int run(String[] args, PrintStream out, PrintStream err) {
        if (args.length < 1) {
            printHelp(out);
            return 1;
        }

        String query = String.join(" ", args);

        try {
            String result = NaturalLanguage.convertNatural(query);
            out.println(result);
            return 0;
        } catch (IllegalArgumentException e) {
            err.println("Error: " + e.getMessage());
            return 1;
        }
    }

    /**
     * Print help text to the given output stream.
     *
     * @param out the output stream to print to
     */
    private static void printHelp(PrintStream out) {
        out.println("LetHimCook - Unit Conversion Library");
        out.println();
        out.println("Usage:");
        out.println("  java -jar lethimcook-all.jar '2 cups to ml'");
        out.println("  java -jar lethimcook-all.jar 'convert 1 pound to grams'");
        out.println("  java -jar lethimcook-all.jar 'how many ml in 3 teaspoons'");
        out.println();
        out.println("Supported units:");
        out.println("  Volume: tsp, tbsp, fl oz, cup, pint, quart, gallon, ml, liter");
        out.println("  Weight: oz, pound, gram, kilogram");
        out.println("  Temperature: fahrenheit, celsius, kelvin");
    }
}
