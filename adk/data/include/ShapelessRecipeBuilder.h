#ifndef SHAPELESSRECIPEBUILDER_H
#define SHAPELESSRECIPEBUILDER_H

#include <string>

#include "RecipeBuilder.h"
#include "json.hpp"

class ShapelessRecipeBuilder : public RecipeBuilder {
   private:
    std::string _result;
    int _count;
    std::vector<std::string> _ingredients;

   public:
    ShapelessRecipeBuilder shapeless(std::string result, int count = 1) {
        if (!registry_check.count(result)) {
            spdlog::error("{} is an invalid item", result);
            exit(EXIT_FAILURE);
        }

        this->_result = result;
        this->_count = count;
        return *this;
    }

    ShapelessRecipeBuilder
        requires(std::string item, int count = 1)
    {
        if (!registry_check.count(item)) {
            spdlog::error("{} is an invalid item", item);
            exit(EXIT_FAILURE);
        }

        for (int a = 0; a < count; a++) this->_ingredients.push_back(item);

        return *this;
    }

    nlohmann::json save(std::string id) {
        nlohmann::json j;

        j["format_version"] = "1.12";
        j["minecraft:recipe_shapeless"]["description"]["identifier"] = id;

        for (auto const& entry : _ingredients)
            j["minecraft:recipe_shapeless"]["ingredients"].push_back(
                {{"item", entry}});

        j["minecraft:recipe_shapeless"]["tags"] = {"crafting_table"};

        j["minecraft:recipe_shapeless"]["result"] = {{"item", _result},
                                                     {"count", _count}};

        createRecipe(id, j);

        return j;
    }
};

#endif