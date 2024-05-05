#pragma once

#include <map>
#include <set>
#include <string>
#include <vector>

#include "builder_recipe.h"
#include "json.hpp"
#include "registry_global.h"
#include "utility/logger.h"

namespace adk {
	class ShapedRecipeBuilder : public RecipeBuilder {
	private:
		std::string _result;
		int _count;
		std::vector<std::string> _rows;
		std::map<char, std::string> _key;

		void ensureValidity(std::string id) {
			if (_rows.empty()) {
				log::error(
					"No pattern is defined for shaped recipe - {}", id);
				exit(EXIT_FAILURE);
			}
			else {
				std::set<char> set;
				for (const auto& [key, value] : _key) set.insert(key);

				for (std::string s : _rows) {
					for (int a = 0; a < s.length(); a++) {
						char c0 = s.at(a);
						if (!_key.count(c0) && c0 != ' ') {
							log::info(
								" Pattern in recipe {} uses undefined symbol '{}' ",
								id, c0);
						}

						set.erase(c0);
					}
				}
			}
		}

	public:
		ShapedRecipeBuilder shaped(std::string result, int count = 1) {
			std::vector<std::string> key = GetIDs();

			// for (auto const entry : registry_global) {
			//     std::map<std::string, std::variant<Block*, Item*>> registry_check;
			//     registry_check = entry->getRegistrar();

			//     for (std::map<std::string, std::variant<Block*, Item*>>::iterator
			//              it = registry_check.begin();
			//          it != registry_check.end(); ++it) {
			//         key.push_back(it->first);
			//     }
			// }

			// for (auto const entry : vanillaRegistry) {
			//     key.push_back(entry);
			// }

			if (!(std::find(key.begin(), key.end(), result) != key.end())) {
				log::error("{} is an invalid item", result);
				exit(EXIT_FAILURE);
			}

			this->_result = result;
			this->_count = count;
			return *this;
		}

		ShapedRecipeBuilder pattern(std::string pattern) {
			if (!_rows.empty() && pattern.length() != _rows.at(0).length()) {
				exit(EXIT_FAILURE);
			}
			else {
				_rows.push_back(pattern);
				return *this;
			}
		}

		ShapedRecipeBuilder define(char symbol, std::string item) {
			std::vector<std::string> key = GetIDs();

			// for (auto const entry : registry_global) {
			//     std::map<std::string, std::variant<Block*, Item*>> registry_check;
			//     registry_check = entry->getRegistrar();

			//     for (std::map<std::string, std::variant<Block*, Item*>>::iterator
			//              it = registry_check.begin();
			//          it != registry_check.end(); ++it) {
			//         key.push_back(it->first);
			//     }
			// }

			// for (auto const entry : vanillaRegistry) {
			//     key.push_back(entry);
			// }

			if (!(std::find(key.begin(), key.end(), item) != key.end())) {
				log::error("{} is an invalid item", item);
				exit(EXIT_FAILURE);
			}

			if (_key.count(symbol)) {
				log::error("{} is already defined", symbol);
				exit(EXIT_FAILURE);
			}
			else if (symbol == ' ') {
				log::error(
					"White space(' ') is reserved and cannot be defined");
				exit(EXIT_FAILURE);
			}
			else {
				_key[symbol] = item;
			}
			return *this;
		}

		nlohmann::json save(std::string id) {
			ensureValidity(id);
			nlohmann::json j;

			j["format_version"] = "1.17";
			j["minecraft:recipe_shaped"]["description"]["identifier"] = id;
			j["minecraft:recipe_shaped"]["pattern"] = _rows;

			for (auto const& [key, value] : _key) {
				std::string str(1, key);
				j["minecraft:recipe_shaped"]["key"][str]["item"] = value;
			}

			j["minecraft:recipe_shaped"]["tags"] = { "crafting_table" };

			j["minecraft:recipe_shaped"]["result"] = { {"item", _result},
													  {"count", _count} };

			createRecipe(id, j);

			return j;
		}
	};
}  // namespace adk