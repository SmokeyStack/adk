#ifndef COOKINGRECIPEBUILDER_HPP
#define COOKINGRECIPEBUILDER_HPP

#include <filesystem>
#include <string>

#include "json.hpp"

namespace fs = std::filesystem;

class CookingRecipeBuilder {
   private:
    std::string _result;
    std::string _ingredient;
    std::vector<std::string> _tags;

    CookingRecipeBuilder(std::string result, std::string ingredient,
                         std::vector<std::string> tags) {
        _result = result;
        _ingredient = ingredient;
        _tags = tags;
    };

   public:
    CookingRecipeBuilder cook(std::string result, std::string ingredient,
                              std::vector<std::string> tags) {
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

        return j;
    }
};

#endif