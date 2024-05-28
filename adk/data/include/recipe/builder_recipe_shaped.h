#pragma once

#include <map>
#include <set>
#include <string>
#include <variant>
#include <vector>

#include "json.hpp"
#include "recipe/builder_recipe.h"
#include "recipe/unlock_context.h"
#include "registry_global.h"
#include "utility/logger.h"

namespace adk {
	class ShapedRecipeBuilder : public RecipeBuilder {
	public:
		ShapedRecipeBuilder(std::string id) : RecipeBuilder(id) {}

		ShapedRecipeBuilder Shaped(std::string result, int count = 1) {
			std::vector<std::string> key = GetIDs();

			if (!(std::find(key.begin(), key.end(), result) != key.end())) {
				log::error("{} is an invalid item", result);

				exit(EXIT_FAILURE);
			}

			this->result_ = result;
			this->count_ = count;

			return *this;
		}

		ShapedRecipeBuilder Pattern(std::string pattern) {
			if (!rows_.empty() && pattern.length() != rows_.at(0).length()) exit(EXIT_FAILURE);

			rows_.push_back(pattern);

			return *this;
		}

		ShapedRecipeBuilder Define(char symbol, std::string item) {
			std::vector<std::string> key = GetIDs();

			if (!(std::find(key.begin(), key.end(), item) != key.end())) {
				log::error("{} is an invalid item", item);

				exit(EXIT_FAILURE);
			}

			if (key_.count(symbol)) {
				log::error("{} is already defined", symbol);

				exit(EXIT_FAILURE);
			}
			if (symbol == ' ') {
				log::error("White space(' ') is reserved and cannot be defined");

				exit(EXIT_FAILURE);
			}

			key_[symbol] = item;

			return *this;
		}

		ShapedRecipeBuilder Tags(std::vector<std::string> tags) {
			tags_ = tags;

			return *this;
		}

		ShapedRecipeBuilder Unlock(std::string item) {
			std::vector<std::string> temp{ item };
			unlock_ = temp;

			return *this;
		}

		ShapedRecipeBuilder Unlock(std::vector<std::string> items) {
			unlock_ = items;

			return *this;
		}

		ShapedRecipeBuilder Unlock(RecipeUnlockContext context) {
			unlock_ = GetRecipeUnlockContext(context);

			return *this;
		}

		nlohmann::json Build(std::string id) {
			ValidateRecipe(id);

			nlohmann::json result;
			result["format_version"] = "1.20.80";
			result["minecraft:recipe_shaped"]["description"]["identifier"] = mod_id + ":" + id;
			result["minecraft:recipe_shaped"]["pattern"] = rows_;

			for (auto const& [key, value] : key_) {
				std::string str{ key };
				result["minecraft:recipe_shaped"]["key"][str]["item"] = value;
			}

			if (tags_.empty()) {
				log::error("No tags are defined for shaped recipe - {}.json", id);

				exit(EXIT_FAILURE);
			}

			result["minecraft:recipe_shaped"]["tags"] = tags_;

			if (std::holds_alternative<std::vector<std::string>>(unlock_))
				for (const auto& item : std::get<std::vector<std::string>>(unlock_))
					result["minecraft:recipe_shaped"]["unlock"].push_back({ {"item", item} });
			else
				result["minecraft:recipe_shaped"]["unlock"]["context"] = std::get<std::string>(unlock_);

			result["minecraft:recipe_shaped"]["result"] = { {"item", result_}, {"count", count_} };

			BuildRecipe(id, result);

			return result;
		}
	private:
		std::string result_;
		int count_;
		std::vector<std::string> rows_;
		std::map<char, std::string> key_;
		std::vector<std::string> tags_;
		std::variant<std::vector<std::string>, std::string> unlock_;

		void ValidateRecipe(std::string id) {
			if (rows_.empty()) {
				log::error("No pattern is defined for shaped recipe - {}", id);

				exit(EXIT_FAILURE);
			}

			std::set<char> key_set;
			for (const auto& [key, value] : key_) key_set.insert(key);
			for (const std::string& row : rows_)
				for (char key : row) {
					if (!key_.count(key) && key != ' ') log::info("Pattern in recipe {} uses undefined symbol '{}'", id, key);

					key_set.erase(key);
				}
		}
	};
}  // namespace adk