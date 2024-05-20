#pragma once

#include <string>

#include "builder_recipe.h"
#include "json.hpp"
#include "registry_global.h"
#include "utility/logger.h"

namespace adk {
	class CookingRecipeBuilder : public RecipeBuilder {
	private:
		std::string _result;
		std::string _ingredient;
		std::vector<std::string> _tags;

	public:
		CookingRecipeBuilder cook(std::string result, std::string ingredient,
			std::vector<std::string> tags) {
			std::vector<std::string> key = GetIDs();

			// for (auto const entry : registry_global) {
			//     std::map<std::string, std::variant<Block*, Item*>>
			//     registry_check; registry_check = entry->getRegistrar();

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

			if (!(std::find(key.begin(), key.end(), ingredient) != key.end())) {
				log::error("{} is an invalid item", ingredient);
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

			createRecipe(id, j);

			return j;
		}
	};
}  // namespace adk