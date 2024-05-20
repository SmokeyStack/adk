#pragma once

#include <filesystem>
#include <fstream>
#include <string>

#include "json.hpp"
#include "registry.h"

namespace adk {
	/**
	 * @brief Builds the recipe
	 *
	 */
	class RecipeBuilder {
	protected:
		/**
		 * @brief Create the recipe
		 *
		 * @param id Recipe Identifier
		 * @param result The resulting JSON
		 */
		void createRecipe(std::string id, nlohmann::json result) {
			if (!std::filesystem::exists("./BP/recipes/")) std::filesystem::create_directory("./BP/recipes/");

			std::ofstream MyJson("./BP/recipes/" + id + ".json");
			MyJson << result.dump();
			MyJson.close();
		}

	public:
		RecipeBuilder() {};
	};
}