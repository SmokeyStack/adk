#ifndef REGISTRY_H
#define REGISTRY_H

#include <spdlog/spdlog.h>

#include <filesystem>
#include <fstream>
#include <string>

namespace fs = std::filesystem;

/// @brief
/// @tparam T
template <typename T>
class Registry {
   private:
    std::string mod_id;

   public:
    Registry(std::string id) { mod_id = id; };
    /// @brief Generates the json file
    /// @param id The name of the identifier, omit the namespace
    /// @param object Class Objects such as Blocks, items, etc
    void subscribe(std::string id, T* object) {
        spdlog::info("Creating {} - {}:{}",
                     object->getType().substr(0, object->getType().size() - 2),
                     mod_id, id);

        if (!fs::exists("./BP/" + object->getType()))
            fs::create_directory("./BP/" + object->getType());

        std::ofstream MyJson("./BP/" + object->getType() + id + ".json");
        MyJson << object->output(mod_id, id).dump();
        MyJson.close();
    };
};

#endif