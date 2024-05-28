#pragma once

#include <filesystem>
#include <fstream>
#include <string>

#include "json.hpp"
#include "registry.h"

namespace adk {
	/**
	 * @brief Builds the recipe
	 */
	class RecipeBuilder {
	public:
		RecipeBuilder() {}

		RecipeBuilder(std::string id) { mod_id = id; }
	protected:
		std::string mod_id;

		/**
		 * @brief Create the recipe
		 *
		 * @param id Recipe Identifier
		 * 
		 * @param result The resulting JSON
		 */
		void BuildRecipe(std::string id, nlohmann::json result) {
			if (!std::filesystem::exists("./BP/recipes/")) std::filesystem::create_directory("./BP/recipes/");

			{
				std::ofstream OutputFile("./BP/recipes/" + id + ".json");
				OutputFile << result.dump();
			}
		}
	};
}