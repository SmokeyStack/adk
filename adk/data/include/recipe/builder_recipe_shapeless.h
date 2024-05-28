#pragma once

#include <map>
#include <string>
#include <variant>
#include <vector>

#include "json.hpp"
#include "recipe/builder_recipe.h"
#include "recipe/unlock_context.h"
#include "registry_global.h"
#include "utility/logger.h"

namespace adk {
	class ShapelessRecipeBuilder : public RecipeBuilder {
	public:
		ShapelessRecipeBuilder(std::string id) : RecipeBuilder(id) {}

		ShapelessRecipeBuilder Shapeless(std::string result, int count = 1) {
			std::vector<std::string> key = GetIDs();

			if (!(std::find(key.begin(), key.end(), result) != key.end())) {
				log::error("{} is an invalid item", result);

				exit(EXIT_FAILURE);
			}

			this->result_ = result;
			this->count_ = count;

			return *this;
		}

		ShapelessRecipeBuilder Ingredients(std::string item, int count = 1) {
			std::vector<std::string> key = GetIDs();

			if (!(std::find(key.begin(), key.end(), item) != key.end())) {
				log::error("{} is an invalid item", item);

				exit(EXIT_FAILURE);
			}

			ingredients_.insert({ item, count });

			return *this;
		}

		ShapelessRecipeBuilder Tags(std::vector<std::string> tags) {
			tags_ = tags;

			return *this;
		}

		ShapelessRecipeBuilder Unlock(std::string item) {
			std::vector<std::string> temp{ item };
			unlock_ = temp;

			return *this;
		}

		ShapelessRecipeBuilder Unlock(std::vector<std::string> items) {
			unlock_ = items;

			return *this;
		}

		ShapelessRecipeBuilder Unlock(RecipeUnlockContext context) {
			unlock_ = GetRecipeUnlockContext(context);

			return *this;
		}

		nlohmann::json Build(std::string id) {
			nlohmann::json result;
			result["format_version"] = "1.20.80";
			result["minecraft:recipe_shapeless"]["description"]["identifier"] = id;

			for (const auto& [ingredient, count] : ingredients_)
				result["minecraft:recipe_shapeless"]["ingredients"].push_back({ {"item", ingredient}, {"count", count} });

			if (tags_.empty()) {
				log::error("No tags are defined for shaped recipe - {}.json", id);

				exit(EXIT_FAILURE);
			}

			result["minecraft:recipe_shapeless"]["tags"] = tags_;

			if (std::holds_alternative<std::vector<std::string>>(unlock_))
				for (const auto& item : std::get<std::vector<std::string>>(unlock_))
					result["minecraft:recipe_shapeless"]["unlock"].push_back({ {"item", item} });
			else
				result["minecraft:recipe_shapeless"]["unlock"]["context"] = std::get<std::string>(unlock_);

			result["minecraft:recipe_shapeless"]["result"] = { {"item", result_}, {"count", count_} };

			BuildRecipe(id, result);

			return result;
		}
	private:
		std::string result_;
		int count_;
		std::map<std::string, int> ingredients_;
		std::vector<std::string> tags_;
		std::variant<std::vector<std::string>, std::string> unlock_;
	};
} // namespace adk