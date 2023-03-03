#ifndef RECIPEBUILDER_H
#define RECIPEBUILDER_H

#include <filesystem>
#include <fstream>
#include <string>

#include "Registry.h"
#include "json.hpp"

namespace fs = std::filesystem;

class RecipeBuilder {
   protected:
    std::map<std::string, std::variant<Block*, Item*>> registry_check;

   public:
    RecipeBuilder(){};

    template <typename T>
    RecipeBuilder checkRegistry(Registry<T> registry) {
        registry_check = registry.getRegistrar();
    }

    void createRecipe(std::string id, nlohmann::json result) {
        if (!fs::exists("./BP/recipes/")) fs::create_directory("./BP/recipes/");

        std::ofstream MyJson("./BP/recipes/" + id + ".json");
        MyJson << result.dump();
        MyJson.close();
    }
};

#endif