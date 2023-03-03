#ifndef REGISTRY_H
#define REGISTRY_H

#include <spdlog/spdlog.h>

#include <filesystem>
#include <fstream>
#include <map>
#include <string>
#include <variant>

#include "Block.h"
#include "Item.h"

namespace fs = std::filesystem;

/// @brief
/// @tparam T
template <typename T>
class Registry {
   private:
    std::string mod_id;
    std::map<std::string, std::variant<Block*, Item*>> _registry;

   public:
    Registry(std::string id) { mod_id = id; };
    /// @brief Generates the json file
    /// @param id The name of the identifier, omit the namespace
    /// @param object Class Objects such as Blocks, items, etc
    void subscribe(std::string id, T* object) {
        if (!_registry.empty() && _registry.count(id)) {
            spdlog::error("{} has already been defined!", id);
            exit(EXIT_FAILURE);
        }

        spdlog::info("Creating {} - {}:{}", object->getType(), mod_id, id);

        _registry[id] = object;

        if (!fs::exists("./BP/" + object->getType() + "s/"))
            fs::create_directory("./BP/" + object->getType() + "s/");

        std::ofstream MyJson("./BP/" + object->getType() + "s/" + id + ".json");
        MyJson << object->output(mod_id, id).dump();
        MyJson.close();
    };

    std::map<std::string, std::variant<Block*, Item*>> getRegistrar() {
        for (auto const& [key, value] : _registry) {
            std::visit(
                [key](auto&& c) {
                    spdlog::info("[{}] - {}", key, typeid(*c).name());
                },
                value);
        }

        return _registry;
    };
};

#endif