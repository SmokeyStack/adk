#ifndef SHAPEDRECIPEBUILDER_H
#define SHAPEDRECIPEBUILDER_H

#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

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

    void save(std::string id) {}
};

#endif