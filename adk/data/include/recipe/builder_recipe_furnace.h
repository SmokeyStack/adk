#pragma once

#include <string>
#include <variant>
#include <vector>

#include "json.hpp"
#include "recipe/builder_recipe.h"
#include "recipe/unlock_context.h"
#include "registry_global.h"
#include "utility/logger.h"

namespace adk {
	class FurnaceRecipeBuilder : public RecipeBuilder {
	public:
		FurnaceRecipeBuilder(std::string id) : RecipeBuilder(id) {}

		FurnaceRecipeBuilder Furnace(std::string result) {
			std::vector<std::string> key = GetIDs();

			if (!(std::find(key.begin(), key.end(), result) != key.end())) {
				log::error("{} is an invalid item", result);

				exit(EXIT_FAILURE);
			}

			this->result_ = result;

			return *this;
		}

		FurnaceRecipeBuilder Input(std::string input) {
			std::vector<std::string> key = GetIDs();

			if (!(std::find(key.begin(), key.end(), input) != key.end())) {
				log::error("{} is an invalid item", input);

				exit(EXIT_FAILURE);
			}

			this->input_ = input;

			return *this;
		}

		FurnaceRecipeBuilder Tags(std::vector<std::string> tags) {
			this->tags_ = tags;

			return *this;
		}

		FurnaceRecipeBuilder Unlock(std::string item) {
			std::vector<std::string> temp{ item };
			this->unlock_ = temp;

			return *this;
		}

		FurnaceRecipeBuilder Unlock(std::vector<std::string> items) {
			this->unlock_ = items;

			return *this;
		}

		FurnaceRecipeBuilder Unlock(RecipeUnlockContext context) {
			this->unlock_ = GetRecipeUnlockContext(context);

			return *this;
		}

		nlohmann::json Build(std::string id) {
			nlohmann::json result;
			result["format_version"] = "1.20.80";
			result["minecraft:recipe_furnace"]["description"]["identifier"] = mod_id + ":" + id;
			result["minecraft:recipe_furnace"]["input"] = input_;
			result["minecraft:recipe_furnace"]["output"] = result_;

			if (tags_.empty()) {
				log::error("No tags are defined for shaped recipe - {}.json", id);

				exit(EXIT_FAILURE);
			}

			result["minecraft:recipe_furnace"]["tags"] = tags_;

			if (std::holds_alternative<std::vector<std::string>>(unlock_))
				for (const auto& item : std::get<std::vector<std::string>>(unlock_))
					result["minecraft:recipe_furnace"]["unlock"].push_back({ {"item", item} });
			else
				result["minecraft:recipe_furnace"]["unlock"]["context"] = std::get<std::string>(unlock_);

			BuildRecipe(id, result);

			return result;
		}
	private:
		std::string result_;
		std::string input_;
		std::vector<std::string> tags_;
		std::variant<std::vector<std::string>, std::string> unlock_;
	};
}  // namespace adk