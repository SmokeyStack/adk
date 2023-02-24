#ifndef SHAPEDRECIPEBUILDER_H
#define SHAPEDRECIPEBUILDER_H

#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

#include "json.hpp"

namespace fs = std::filesystem;

class ShapedRecipeBuilder {
   private:
    std::string _result;
    int _count;
    std::vector<std::string> _rows;
    std::map<char, std::string> _key;

   public:
    ShapedRecipeBuilder shaped(std::string result, int count) {
        this->_result = result;
        this->_count = count;
        return *this;
    }

    ShapedRecipeBuilder shaped(std::string result) { return shaped(result, 1); }

    ShapedRecipeBuilder pattern(std::string pattern) {
        if (!_rows.empty() && pattern.length() != _rows.at(0).length()) {
            std::cout << "Wtf?\n";
            exit(EXIT_FAILURE);
        } else {
            std::cout << "Yooo\n";
            _rows.push_back(pattern);
            return *this;
        }
    }

    ShapedRecipeBuilder define(char symbol, std::string item) {
        if (_key.count(symbol)) {
            std::cerr << symbol << " is already defined\n";
            exit(EXIT_FAILURE);
        } else if (symbol == ' ') {
            std::cerr << "Whitespace(' ') is reserved and cannot be defined\n";
            exit(EXIT_FAILURE);
        } else {
            _key[symbol] = item;
        }
        return *this;
    }

    void ensureValidity(std::string id) {
        if (_rows.empty()) {
            std::cerr << "No pattern is defined for shaped recipe " + id + '\n';
            exit(EXIT_FAILURE);
        } else {
            std::set<char> set;
            for (const auto& [key, value] : _key) set.insert(key);

            for (std::string s : _rows) {
                for (int a = 0; a < s.length(); a++) {
                    char c0 = s.at(a);
                    if (!_key.count(c0) && c0 != ' ') {
                        std::cout << "Keyval\n";
                    }

                    set.erase(c0);
                }
            }

            if (!set.empty()) std::cout << "Why extra?\n";
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
        j["minecraft:recipe_shaped"]["result"] = {{"item", _result},
                                                  {"count", _count}};

        if (!fs::exists("./BP/recipes/")) fs::create_directory("./BP/recipes/");

        std::ofstream MyJson("./BP/recipes" + id + ".json");
        MyJson << j.dump();
        MyJson.close();

        return j;
    }
};

#endif