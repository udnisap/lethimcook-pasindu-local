#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

#include "lethimcook/converter.hpp"

int main(int argc, char* argv[]) {
    if (argc < 4) {
        std::cerr << "LetHimCook - Unit Conversion Library\n"
                  << "\nUsage:\n"
                  << "  lethimcook_cli <value> <from_unit> <to_unit>\n"
                  << "\nExample:\n"
                  << "  lethimcook_cli 2 cups ml\n"
                  << "  lethimcook_cli 350 fahrenheit celsius\n"
                  << "\nSupported units:\n"
                  << "  Volume: tsp, tbsp, fl oz, cup, pint, quart, gallon, ml, liter\n"
                  << "  Weight: oz, pound, gram, kilogram\n"
                  << "  Temperature: fahrenheit, celsius, kelvin\n";
        return 1;
    }

    try {
        double value = std::stod(argv[1]);
        std::string from_unit = argv[2];
        std::string to_unit = argv[3];

        double result = lethimcook::convert(value, from_unit, to_unit);

        std::cout << std::fixed << std::setprecision(2)
                  << value << " " << from_unit << " = "
                  << result << " " << to_unit << "\n";
    } catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << "\n";
        return 1;
    }

    return 0;
}
