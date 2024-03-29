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

/**
 * @brief Not directly used except for putting Registry<T> into
 * vectors
 *
 */
class Registrar {
   public:
    virtual void subscribe(std::string dummy,
                           std::variant<Block*, Item*> dummy_2) {}
    virtual std::map<std::string, std::variant<Block*, Item*>> getRegistrar() {
        std::map<std::string, std::variant<Block*, Item*>> dummy;
        return dummy;
    }
};

/**
 * @brief Used to register objects into the game
 *
 * @tparam T Object type such as Block or Item
 */
template <typename T>
class Registry : public Registrar {
   private:
    std::string mod_id;
    std::map<std::string, std::variant<Block*, Item*>> _registry;

   public:
    /**
     * @brief Construct a new Registry object
     *
     * @param id namespace identifier
     */
    Registry(std::string id) { mod_id = id; };
    /**
     * @brief Generates the json file
     *
     * @param id The name of the identifier, omit the namespace
     * @param object Class Objects such as Blocks, items, etc
     */
    void subscribe(std::string id, std::variant<Block*, Item*> object) {
        if (!_registry.empty() && _registry.count(id)) {
            spdlog::get("Blocks/Items")
                ->error("{} has already been defined!", id);
            exit(EXIT_FAILURE);
        }

        std::visit(
            [=](auto&& c) {
                spdlog::get("Blocks/Items")
                    ->info("Creating {} - {}:{}", c->getType(), mod_id, id);

                _registry[mod_id + ":" + id] = c;

                if (!fs::exists("./BP/" + c->getType() + "s/"))
                    fs::create_directory("./BP/" + c->getType() + "s/");

                std::ofstream MyJson("./BP/" + c->getType() + "s/" + id +
                                     ".json");
                MyJson << c->output(mod_id, id).dump();
                MyJson.close();
            },
            object);
    };

    /**
     * @brief Get the Registrar object
     *
     * @return std::map<std::string, std::variant<Block*, Item*>>
     */
    std::map<std::string, std::variant<Block*, Item*>> getRegistrar() {
        return _registry;
    };
};

#endif