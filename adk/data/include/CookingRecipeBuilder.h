#ifndef COOKINGRECIPEBUILDER_H
#define COOKINGRECIPEBUILDER_H

#include <string>

#include "RecipeBuilder.h"
#include "json.hpp"

class CookingRecipeBuilder : public RecipeBuilder {
   private:
    std::string _result;
    std::string _ingredient;
    std::vector<std::string> _tags;

   public:
    CookingRecipeBuilder cook(std::string result, std::string ingredient,
                              std::vector<std::string> tags) {
        if (!registry_check.count(result)) {
            logger->error("{} is an invalid item", result);
            exit(EXIT_FAILURE);
        }

        if (!registry_check.count(ingredient)) {
            logger->error("{} is an invalid item", ingredient);
            exit(EXIT_FAILURE);
        }

        this->_result = result;
        this->_ingredient = ingredient;
        this->_tags = tags;
        return *this;
    }

    nlohmann::json save(std::string id) {
        nlohmann::json j;

        j["format_version"] = "1.17";
        j["minecraft:recipe_furnace"]["description"]["identifier"] = id;

        j["minecraft:recipe_furnace"]["tags"] = _tags;

        j["minecraft:recipe_furnace"]["input"]["item"] = _ingredient;
        j["minecraft:recipe_furnace"]["output"]["item"] = _result;

        createRecipe(_result, j);

        return j;
    }
};

#endif