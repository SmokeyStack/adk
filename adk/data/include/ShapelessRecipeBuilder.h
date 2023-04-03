#ifndef SHAPELESSRECIPEBUILDER_H
#define SHAPELESSRECIPEBUILDER_H

#include <string>

#include "GlobalRegistry.h"
#include "RecipeBuilder.h"
#include "json.hpp"

class ShapelessRecipeBuilder : public RecipeBuilder {
   private:
    std::string _type;
    std::string _result;
    int _count;
    std::vector<std::string> _ingredients;

   public:
    ShapelessRecipeBuilder shapeless(std::string result, int count = 1) {
        this->_type = "crafting_table";

        std::vector<std::string> key;

        for (auto const entry : globalregistry) {
            std::map<std::string, std::variant<Block*, Item*>> registry_check;
            registry_check = entry->getRegistrar();

            for (std::map<std::string, std::variant<Block*, Item*>>::iterator
                     it = registry_check.begin();
                 it != registry_check.end(); ++it) {
                key.push_back(it->first);
            }
        }

        for (auto const entry : vanillaRegistry) {
            key.push_back(entry);
        }

        if (!(std::find(key.begin(), key.end(), result) != key.end())) {
            spdlog::get("Recipe")->error("{} is an invalid item", result);
            exit(EXIT_FAILURE);
        }

        this->_result = result;
        this->_count = count;
        return *this;
    }

    ShapelessRecipeBuilder stonecutter(std::string result, int count = 1) {
        this->_type = "stonecutter";

        std::vector<std::string> key;

        for (auto const entry : globalregistry) {
            std::map<std::string, std::variant<Block*, Item*>> registry_check;
            registry_check = entry->getRegistrar();

            for (std::map<std::string, std::variant<Block*, Item*>>::iterator
                     it = registry_check.begin();
                 it != registry_check.end(); ++it) {
                key.push_back(it->first);
            }
        }

        for (auto const entry : vanillaRegistry) {
            key.push_back(entry);
        }

        if (!(std::find(key.begin(), key.end(), result) != key.end())) {
            spdlog::get("Recipe")->error("{} is an invalid item", result);
            exit(EXIT_FAILURE);
        }

        this->_result = result;
        this->_count = count;
        return *this;
    }

    ShapelessRecipeBuilder
        requires(std::string item, int count = 1)
    {
        std::vector<std::string> key;

        for (auto const entry : globalregistry) {
            std::map<std::string, std::variant<Block*, Item*>> registry_check;
            registry_check = entry->getRegistrar();

            for (std::map<std::string, std::variant<Block*, Item*>>::iterator
                     it = registry_check.begin();
                 it != registry_check.end(); ++it) {
                key.push_back(it->first);
            }
        }

        for (auto const entry : vanillaRegistry) {
            key.push_back(entry);
        }

        if (!(std::find(key.begin(), key.end(), item) != key.end())) {
            spdlog::get("Recipe")->error("{} is an invalid item", item);
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

        j["minecraft:recipe_shapeless"]["tags"] = {_type};

        j["minecraft:recipe_shapeless"]["result"] = {{"item", _result},
                                                     {"count", _count}};

        createRecipe(id, j);

        return j;
    }
};

#endif