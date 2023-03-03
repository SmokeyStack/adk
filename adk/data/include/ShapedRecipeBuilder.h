#ifndef SHAPEDRECIPEBUILDER_H
#define SHAPEDRECIPEBUILDER_H

#include <spdlog/spdlog.h>

#include <map>
#include <set>
#include <string>
#include <vector>

#include "RecipeBuilder.h"
#include "json.hpp"

class ShapedRecipeBuilder : public RecipeBuilder {
   private:
    std::string _result;
    int _count;
    std::vector<std::string> _rows;
    std::map<char, std::string> _key;

   public:
    ShapedRecipeBuilder shaped(std::string result, int count = 1) {
        if (!registry_check.count(result)) {
            logger->error("{} is an invalid item", result);
            exit(EXIT_FAILURE);
        }

        this->_result = result;
        this->_count = count;
        return *this;
    }

    ShapedRecipeBuilder pattern(std::string pattern) {
        if (!_rows.empty() && pattern.length() != _rows.at(0).length()) {
            exit(EXIT_FAILURE);
        } else {
            _rows.push_back(pattern);
            return *this;
        }
    }

    ShapedRecipeBuilder define(char symbol, std::string item) {
        if (!registry_check.count(item)) {
            logger->error("{} is an invalid item", item);
            exit(EXIT_FAILURE);
        }

        if (_key.count(symbol)) {
            logger->error("{} is already defined", symbol);
            exit(EXIT_FAILURE);
        } else if (symbol == ' ') {
            logger->error("White space(' ') is reserved and cannot be defined");
            exit(EXIT_FAILURE);
        } else {
            _key[symbol] = item;
        }
        return *this;
    }

    void ensureValidity(std::string id) {
        if (_rows.empty()) {
            logger->error("No pattern is defined for shaped recipe - {}", id);
            exit(EXIT_FAILURE);
        } else {
            std::set<char> set;
            for (const auto& [key, value] : _key) set.insert(key);

            for (std::string s : _rows) {
                for (int a = 0; a < s.length(); a++) {
                    char c0 = s.at(a);
                    if (!_key.count(c0) && c0 != ' ') {
                        spdlog::info(
                            " Pattern in recipe {} uses undefined symbol '{}' ",
                            id, c0);
                    }

                    set.erase(c0);
                }
            }
        }
    }

    nlohmann::json save(std::string id) {
        ensureValidity(id);
        nlohmann::json j;

        j["format_version"] = "1.17";
        j["minecraft:recipe_shaped"]["description"]["identifier"] = id;
        j["minecraft:recipe_shaped"]["pattern"] = _rows;

        for (auto const& [key, value] : _key) {
            const char* test = &key;
            std::string str(test);
            j["minecraft:recipe_shaped"]["key"][test]["item"] = value;
        }

        j["minecraft:recipe_shaped"]["tags"] = {"crafting_table"};

        j["minecraft:recipe_shaped"]["result"] = {{"item", _result},
                                                  {"count", _count}};

        createRecipe(id, j);

        return j;
    }
};

#endif