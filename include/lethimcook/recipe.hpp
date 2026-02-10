// recipe.hpp - Recipe and Ingredient structs and logic
#ifndef LETHIMCOOK_RECIPE_HPP
#define LETHIMCOOK_RECIPE_HPP

#include <string>
#include <vector>
#include <optional>

namespace lethimcook {

// Ingredient structure - to be implemented in Milestone 2
struct Ingredient {
    std::string name;
    std::optional<double> amount;
    std::optional<std::string> unit;
    std::optional<std::string> note;
};

// Recipe structure - to be implemented in Milestone 2
struct Recipe {
    int servings;
    std::vector<Ingredient> ingredients;
    std::optional<std::string> name;

    static Recipe create(int servings, std::vector<Ingredient> ingredients);
    Recipe scale(int new_servings) const;
};

} // namespace lethimcook

#endif // LETHIMCOOK_RECIPE_HPP
