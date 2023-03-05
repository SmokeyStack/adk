#ifndef RECIPEBUILDER_H
#define RECIPEBUILDER_H

#include <filesystem>
#include <fstream>
#include <string>

#include "Registry.h"
#include "json.hpp"

namespace fs = std::filesystem;

class RecipeBuilder {
   public:
    RecipeBuilder(){};

    void createRecipe(std::string id, nlohmann::json result) {
        if (!fs::exists("./BP/recipes/")) fs::create_directory("./BP/recipes/");

        std::ofstream MyJson("./BP/recipes/" + id + ".json");
        MyJson << result.dump();
        MyJson.close();
    }
};

#endif