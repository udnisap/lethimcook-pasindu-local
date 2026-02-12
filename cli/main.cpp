#include "lethimcook/lethimcook.hpp"

#include <iostream>
#include <sstream>
#include <string>

static void print_usage() {
    std::cout << "LetHimCook - Unit Conversion Library\n"
              << "\nUsage:\n"
              << "  lethimcook_cli '<conversion request>'\n"
              << "  lethimcook_cli 2 cups to ml\n"
              << "  lethimcook_cli convert 1 pound to grams\n"
              << "  lethimcook_cli how many ml in 3 teaspoons\n"
              << "\nSupported units:\n"
              << "  Volume: tsp, tbsp, fl oz, cup, pint, quart, gallon, ml, liter\n"
              << "  Weight: oz, pound, gram, kilogram\n"
              << "  Temperature: fahrenheit, celsius, kelvin\n";
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        print_usage();
        return 1;
    }

    // Join all arguments into a single query string
    std::ostringstream oss;
    for (int i = 1; i < argc; ++i) {
        if (i > 1) oss << ' ';
        oss << argv[i];
    }
    std::string query = oss.str();

    // For now, the CLI just prints the query.
    // Natural language parsing will be added in Milestone 2.
    // This placeholder ensures the executable links and runs.
    std::cerr << "Natural language parsing not yet implemented.\n"
              << "Query: " << query << "\n";
    return 1;
}
