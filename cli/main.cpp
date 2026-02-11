// main.cpp - CLI entrypoint for lethimcook
#include "lethimcook/natural.hpp"
#include <iostream>
#include <string>

void print_usage() {
    std::cout << "LetHimCook - Unit Conversion Library\n\n";
    std::cout << "Usage:\n";
    std::cout << "  lethimcook_cli '2 cups to ml'\n";
    std::cout << "  lethimcook_cli 'convert 1 pound to grams'\n";
    std::cout << "  lethimcook_cli 'how many ml in 3 teaspoons'\n\n";
    std::cout << "Supported units:\n";
    std::cout << "  Volume: tsp, tbsp, fl oz, cup, pint, quart, gallon, ml, liter\n";
    std::cout << "  Weight: oz, pound, gram, kilogram\n";
    std::cout << "  Temperature: fahrenheit, celsius, kelvin\n";
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        print_usage();
        return 1;
    }

    // Join all command-line arguments into a single query string
    std::string query;
    for (int i = 1; i < argc; ++i) {
        if (i > 1) {
            query += " ";
        }
        query += argv[i];
    }

    try {
        std::string result = lethimcook::convert_natural(query);
        std::cout << result << "\n";
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
