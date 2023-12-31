#ifndef RECIPEBUILDER_H
#define RECIPEBUILDER_H

#include <filesystem>
#include <fstream>
#include <string>

#include "registry.h"
#include "json.hpp"

namespace fs = std::filesystem;

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
        if (!fs::exists("./BP/recipes/")) fs::create_directory("./BP/recipes/");

        std::ofstream MyJson("./BP/recipes/" + id + ".json");
        MyJson << result.dump();
        MyJson.close();
    }

   public:
    RecipeBuilder(){};
};

#endif